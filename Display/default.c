#include "main.h"

void display_default_line0_draw(u8 dot_s);
void display_default_line1_draw(u8 dot_s);
static u8 get_time_state();

//интервал измерений заряда аккумулятора в мс * 50
//по умолчанию = 20 - 1 раз в 1 сек
const u8 MAX_PRESCALER=20;

//интервал включения автоматического режима полива, если был выбран ручной
const u16 WATERING_REGIM_MANUAL_INTERVAL=180; //3 минуты

static u8 bat_p;
static float bat_v;
static RTCTIME rtc_clck;
static s8 air_temp=0;
static u8 gnd_hum=0;
static u16 cnt_watering=0;
static u16 watering_time=0;

void init_display_default(){
	//логотип-заставка при загрузке
	lcd_set_xy(0,0);
	lcd_out(LOGO_LINE0);
	lcd_set_xy(0,1);
	lcd_out(LOGO_LINE1);
	delay_ms(LOGO_SHOW_TIME);
	lcd_clear();

    timeout_menu_count=0;
}

void display_default_draw(){
	static u8 prescaler=0;

	if(prescaler==0 || prescaler==10){display_default_line0_draw(prescaler>9);}
	if(prescaler==0 || prescaler==4) {display_default_line1_draw(prescaler>3);}

	prescaler++;

	delay_ms(100);

	if(prescaler == MAX_PRESCALER){
		prescaler = 0;
	}

}

void display_default_line0_draw(u8 dot_s){
	//верхняя строка на дисплее
	lcd_set_xy(0, 0);
	lcd_set_xy(0, 0);

	//температура
	if(air_temp>0) 		{lcd_out("+");}
	else if(air_temp<0)	{lcd_out("-");}

	air_temp = absolute(air_temp);
	if(air_temp>9){
		lcd_write_dec_xx(air_temp);
	}else{
		lcd_write_dec_x(air_temp);
	}
	lcd_send_data(SYMB_DEGREE);
	lcd_out("  ");

	//влажность
	lcd_set_xy(6, 0);
	lcd_send_data(SYMB_DRIB); //капелька
	lcd_write_dec_xx(gnd_hum);
	lcd_out("%");

	//часы
	lcd_set_xy(11, 0);
	lcd_write_dec_xx(rtc_clck.hour);
	lcd_out(dot_s ? T_SEP : " ");
	lcd_write_dec_xx(rtc_clck.min);
}

void display_default_line1_draw(u8 dot_s){
	//нижняя строка на дисплее
	lcd_set_xy(0, 1);

	//время полива
	if(regim == DISPLAY_REGIM_NO_WATER){
		lcd_out(dot_s ? NO_WATER : NO_WATER_SPACE);
	}else if(regim == DISPLAY_REGIM_WATERING ||
			 regim == DISPLAY_REGIM_MANUAL_WATERING){
		lcd_send_data(dot_s ? SYMB_AUTO_REG_EMPTY : SYMB_AUTO_REG_FULL); //пиктограмка активного полива
		lcd_out(WATERING_STATE);
	}else if(get_TIM_state(TIM6)){
		lcd_send_data(SYMB_MANUAL_REG); //пиктограмка режима полива (ручн)
		lcd_out(MANUAL_REGIM);
	}else if(watering_time > 0){
		if(get_TIM_state(TIM4)){//режим отсчета задержки перед поливом
			lcd_send_data(SYMB_AUTO_REG_EMPTY);
		}else{				//режим задржки перед измерением уровня влажности
			lcd_out(SYMB_CHECK_W_SENSOR);
		}
		 //пиктограмка режима полива (авто)

		u8 minutes = watering_time / 60;

		if(minutes > 99){
			lcd_write_dec_xxx(minutes);
		}else{
			lcd_write_dec_xx(minutes);
		}
		lcd_out(":");
		lcd_write_dec_xx(watering_time - minutes * 60);
		lcd_out("  ");
	}else{
		lcd_out(SYMB_CHECK_W_SENSOR);
		lcd_out(NOT_CHEK_TIME);
	}

	lcd_set_xy(10, 1);

	//относительное значение напряжения аккумулятора
	if(bat_p>70){
		lcd_send_data(SYMB_BAT_100_PERC);
	}else if(bat_p>40){
		lcd_send_data(SYMB_BAT_50_PERC);
	}else if(bat_p){
		lcd_send_data(SYMB_BAT_EMPTY);
	}else{
		if(dot_s){
			lcd_send_data(SYMB_BAT_EMPTY);
		}else{
			lcd_out(" ");
		}
	}
	//напряжение аккумулятора
	//абсолютное значение в вольтах
	lcd_write_float(bat_v);
	lcd_out((char *)BAT_VOLT);

}


//обработчик прерывания от таймера 7 один раз в секунду
void TIM7_IRQHandler(void)
{
	TIM_ClearFlag(TIM7, TIM_SR_UIF);//Сбрасываем флаг прерывания

	u16 chk_interval;

	if(regim == DISPLAY_REGIM_WATERING){
		u8 watering_duration = (u8)BKP_ReadBackupRegister(WATERING_DURATION_BKP);//продолжительность полива
		if(cnt_watering > watering_duration){
			//отсчет времени до отключения полива
			PIN_OFF(WATERING_RELAY);	//стоп полива (откл.реле)
			regim = DISPLAY_REGIM_DEFAULT;
			cnt_watering = 0;
		}
	}else{
		//сбор всех данных - 1 раз в секунду
		bat_v =		get_acu_value();
		bat_p =		get_acu_perc_value(bat_v);
		air_temp =	get_temperature_3wire();
		RTC_GetTime(&rtc_clck);

		if(get_TIM_state(TIM6)){return;}//включен ручной режим полива

		//проверка уровня влажности один раз в заданый промежуток (5минут)
		chk_interval = BKP_ReadBackupRegister(CHECK_INTERVAL_BKP);
		chk_interval *= 60;

		if(cnt_watering == chk_interval){
			//отсчет времени до очередной проверки датчика влажности
			//и проверки состояния для полива
			cnt_watering = 0;
		}
		if(cnt_watering == 0){
			if(get_TIM_state(TIM4) == false) {
				watering_time = chk_interval;
			}

			check_humidity_sensor();

			if(get_time_state() == false){
				if(get_TIM_state(TIM4)) {
					TIM_Cmd(TIM4, DISABLE);//допустимое время полива вышло - откл. таймер отсчета до полива
					watering_time = 0;
				}
			}else{
				check_humidity_value();
			}
		}
		if(watering_time > 0) {watering_time--;}
	}
	cnt_watering++;

}

static u8 get_time_state(){
	u16 morning_time, evening_time, now_time;

	morning_time = BKP_ReadBackupRegister(tMORNING_WATERING_TIME_BKP);
	evening_time = BKP_ReadBackupRegister(tEVENING_WATERING_TIME_BKP);

	now_time = set_low_n_height(rtc_clck.hour, rtc_clck.min); //текущее время (часы+минуты)

	if(air_temp > 30){	//оч.жарко - поливаем независимо от времени утро/вечер
		//но в заданный промежуток времени
		return (morning_time < now_time && now_time < evening_time); //с утра до вечера
	}else if(air_temp > 5){		//лето
		return (morning_time < now_time && now_time < 0x0C00); //до полудня
	}else{						//зима
		return (0x0C00 < now_time && now_time < evening_time); //после полудня
	}
}

void check_humidity_value(){
	u16 hum_params = BKP_ReadBackupRegister(HUMYDURTY_BKP);

	if(gnd_hum < get_height(hum_params)){//влажность почвы меньше заданного значения
		if(get_TIM_state(TIM4) == false){//отсчет до полива не был уже запущен ранее
			watering_time = (get_low(hum_params) + 1) * 60;//задержка перед поливом (в секундах)
			TIM_Cmd(TIM4, ENABLE);		//запускаем отсчет
		}
	}else{
		TIM_Cmd(TIM4, DISABLE);//кто-то полил вручную - отключаем таймер отсчета до полива
	}
}

void check_humidity_sensor(){
	PIN_ON(HUMIDITY_SENSOR);//подаем питание на датчик влажности
	delay_for(1500);
	gnd_hum = get_watering_sensor_perc_value();
	PIN_OFF(HUMIDITY_SENSOR);//отключаем питание
}


//обработчик прерывания от таймера 4 один раз в минуту
//задержка перед поливом 60-250мин
void TIM4_IRQHandler(void)
{
	TIM_ClearFlag(TIM4, TIM_SR_UIF);//Сбрасываем флаг прерывания

	if(watering_time == 1){
		TIM_Cmd(TIM4, DISABLE); //отключаем таймер
		regim = DISPLAY_REGIM_WATERING;
		cnt_watering = 0;
		PIN_ON(WATERING_RELAY);
	}
}



