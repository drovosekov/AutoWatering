#include "main.h"

static void move_by_menu_LR(buttons direction);
//защитка от дребезга кнопок
static u8 save_pressed_buton(buttons btn, u8 clr);


u8 timeout_menu_count;

static buttons btn_pressed=0;
static u8 bright_off_count = 0;


void get_buttons_state(){

	switch(get_keyboard_state()){
	case BTN_STATE_ENTER:
		if(save_pressed_buton(BTN_STATE_ENTER, true))
			{return;}//если кнопка все еще нажата - выходим

		switch(regim){
		case DISPLAY_REGIM_DEFAULT:
		case DISPLAY_REGIM_WATERING:
		case DISPLAY_REGIM_MANUAL_WATERING:
		case DISPLAY_REGIM_NO_WATER:
			init_bright_contrast();
			bright_off_count = 0;
			return;

		case DISPLAY_REGIM_MENU:
			btn_enter_pressed_in_menu();
			break;

		case DISPLAY_REGIM_SET_TIME_DATE:
			btn_enter_pressed_in_set_date_time();
			break;

		case DISPLAY_REGIM_SET_WATERING_TIME:
			btn_enter_pressed_in_set_watering_time();
			break;

		case DISPLAY_REGIM_SET_WAERING_DUR:
			btn_enter_pressed_in_set_watering_duration();
			break;

    	case DISPLAY_REGIM_SET_HUMIDITY:
    		btn_enter_pressed_in_set_humidity();
    		break;

    	case DISPLAY_REGIM_SET_CHK_INTERVAL:
    		btn_enter_pressed_in_set_chk_interval();
    		break;

    	case DISPLAY_REGIM_SET_WATERING_REG:
    		btn_enter_pressed_in_set_watering_reg();
    		break;

    	case DISPLAY_REGIM_SET_LIGHT:
    		btn_enter_pressed_in_set_light_time();
    		break;

		case DISPLAY_REGIM_SET_BRIGHT_CONTR:
    		btn_enter_pressed_in_set_bright_contrast();
			break;
		}

		break;

	case BTN_STATE_MENU:
		if(save_pressed_buton(BTN_STATE_MENU, false))
			{return;}//если кнопка все еще нажата - выходим

		regim = DISPLAY_REGIM_MENU;
		lcd_set_state(LCD_ENABLE, CURSOR_DISABLE);
		init_menu();
		break;

	case BTN_STATE_START:
		if(save_pressed_buton(BTN_STATE_START, false))
			{return;}

		if(get_TIM_state(TIM6) && regim != DISPLAY_REGIM_NO_WATER){
			PIN_ON(WATERING_RELAY);					//запуск полива (вкл.реле)
			regim = DISPLAY_REGIM_MANUAL_WATERING;
		}
		break;

	case BTN_STATE_EXIT:
		if(save_pressed_buton(BTN_STATE_EXIT, true))
			{return;}

		switch(regim){
			case DISPLAY_REGIM_WATERING:
			case DISPLAY_REGIM_MANUAL_WATERING:
			case DISPLAY_REGIM_DEFAULT:
			case DISPLAY_REGIM_NO_WATER:
				break;

			case DISPLAY_REGIM_MENU:

				regim = DISPLAY_REGIM_DEFAULT;
	    		TIM_Cmd(TIM7, ENABLE);
				break;

			case DISPLAY_REGIM_SET_TIME_DATE:
			case DISPLAY_REGIM_SET_WATERING_TIME:
			case DISPLAY_REGIM_SET_WAERING_DUR:
			case DISPLAY_REGIM_SET_HUMIDITY:
			case DISPLAY_REGIM_SET_CHK_INTERVAL:
			case DISPLAY_REGIM_SET_WATERING_REG:
			case DISPLAY_REGIM_SET_LIGHT:
			case DISPLAY_REGIM_SET_BRIGHT_CONTR:
				lcd_set_state(LCD_ENABLE, CURSOR_DISABLE);

				regim = DISPLAY_REGIM_MENU;
				break;
		}
		break;

	case BTN_STATE_LEFT:
		move_by_menu_LR(BTN_STATE_LEFT);
		break;

	case BTN_STATE_RIGHT:
		move_by_menu_LR(BTN_STATE_RIGHT);
		break;

	case BTN_STATE_STOP:
		switch(regim){
			case DISPLAY_REGIM_WATERING:
			case DISPLAY_REGIM_MANUAL_WATERING:
			case DISPLAY_REGIM_DEFAULT:
			case DISPLAY_REGIM_NO_WATER:
				if(save_pressed_buton(BTN_STATE_STOP, false))
					{return;}

				PIN_OFF(WATERING_RELAY);		//стоп полива (откл.реле)
				PIN_OFF(NO_WATER_LED);
				regim = DISPLAY_REGIM_DEFAULT;

				check_humidity_sensor();
				//если влажность ниже заданной - полив запуститься не зависимо от времени суток!
				check_humidity_value();
	    		TIM_Cmd(TIM7, ENABLE);

	    		init_bright_contrast();
	    		bright_off_count = 0;
				break;

			case DISPLAY_REGIM_MENU:
			case DISPLAY_REGIM_SET_TIME_DATE:
			case DISPLAY_REGIM_SET_WATERING_TIME:
			case DISPLAY_REGIM_SET_WAERING_DUR:
			case DISPLAY_REGIM_SET_HUMIDITY:
			case DISPLAY_REGIM_SET_CHK_INTERVAL:
			case DISPLAY_REGIM_SET_WATERING_REG:
			case DISPLAY_REGIM_SET_LIGHT:
			case DISPLAY_REGIM_SET_BRIGHT_CONTR:
				break;
		}
		break;

	default:
		btn_pressed = BTN_STATE_RESET;
		break;

	}
}

buttons get_keyboard_state(){
	u8 buttons_state = 0;
	if(!PIN_STATE(BUTTONS_PIN_A2)) {buttons_state |= 0b00000001;}
	if(!PIN_STATE(BUTTONS_PIN_A3)) {buttons_state |= 0b00000010;}
	if(!PIN_STATE(BUTTONS_PIN_A4)) {buttons_state |= 0b00000100;}

	switch(buttons_state){
		case 1:		return BTN_STATE_MENU;
		case 2:		return BTN_STATE_STOP;
		case 3:		return BTN_STATE_ENTER;
		case 4:		return BTN_STATE_START;
		case 5:		return BTN_STATE_LEFT;
		case 6:		return BTN_STATE_EXIT;
		case 7:		return BTN_STATE_RIGHT;
		default:	return BTN_STATE_RESET;
	}
}

void get_sensors_state(){
	if(PIN_STATE(WATER_LEVER_SENSOR)) {
		if(regim == DISPLAY_REGIM_DEFAULT)
			{regim = DISPLAY_REGIM_NO_WATER;}
		PIN_ON(NO_WATER_LED);
		PIN_OFF(WATERING_RELAY);
	}else{
		if(PIN_STATE(NO_WATER_LED)) {PIN_OFF(NO_WATER_LED);}
	}

	if(PIN_STATE(LIGHT_SENSOR)) {
		//датчик естественного света - выключаем досветку
		if(PIN_STATE(LIGHT_RELAY)) {PIN_OFF(LIGHT_RELAY);}
	}else{
		//текущее время в разрешенном диапазоне использования досветки
		RTCTIME rtc_clock;
		RTC_GetTime(&rtc_clock);

		u16 now_time = set_low_n_height(rtc_clock.hour, rtc_clock.min); //текущее время (часы+минуты)

		//но в заданный промежуток времени
		if (BKP_ReadBackupRegister(tMORNING_LIGHT_TIME_BKP) < now_time &&
			now_time < BKP_ReadBackupRegister(tEVENING_LIGHT_TIME_BKP)) //с утра до вечера
		{
			PIN_ON(LIGHT_RELAY);
		}
	}
}


void auto_bright_off(){
	static u8 already_set = 0;

	if(regim == DISPLAY_REGIM_DEFAULT ||
	   regim == DISPLAY_REGIM_NO_WATER) {
		if(bright_off_count > TIMEOUT_MENU_EXIT){
			//отключаем подсветку
			TIM_SetCompare3(TIM3, 0);
			bright_off_count = 0;
		}else{
			bright_off_count++;
		}
		already_set = 0;
	}else if(already_set == 0 && regim != DISPLAY_REGIM_SET_BRIGHT_CONTR){
		init_bright_contrast();
		bright_off_count = 0;
		already_set = 1;
	}
}

void move_by_menu_LR(buttons direction){
	timeout_menu_count=0;

	switch(regim){
	case DISPLAY_REGIM_MANUAL_WATERING:
	case DISPLAY_REGIM_WATERING:
	case DISPLAY_REGIM_DEFAULT:
	case DISPLAY_REGIM_NO_WATER:
		init_bright_contrast();
		bright_off_count = 0;
		break;

	case DISPLAY_REGIM_MENU:
		if(save_pressed_buton(direction, false))
			{return;}
		btn_move_in_menu(&direction);
		return;

	case DISPLAY_REGIM_SET_TIME_DATE:
		btn_move_in_set_date_time(direction);
		break;

	case DISPLAY_REGIM_SET_WATERING_TIME:
		btn_move_in_set_watering_time(direction);
		break;

	case DISPLAY_REGIM_SET_WAERING_DUR:
		btn_move_in_set_watering_duration(direction);
		break;

	case DISPLAY_REGIM_SET_HUMIDITY:
		btn_move_in_set_humidity(direction);
		break;

	case DISPLAY_REGIM_SET_CHK_INTERVAL:
		btn_move_in_set_chk_interval(direction);
		break;

	case DISPLAY_REGIM_SET_WATERING_REG:
		btn_move_in_set_watering_reg(direction);
		break;

	case DISPLAY_REGIM_SET_LIGHT:
		btn_move_in_set_light_time(direction);
		break;

	case DISPLAY_REGIM_SET_BRIGHT_CONTR:
		btn_move_in_set_bright_contrast(direction);
		break;

	}
	delay_ms(500);//задержка для не очень быстрого изменения значений
}

u8 save_pressed_buton(buttons btn, u8 clr){
	timeout_menu_count=0;
	if(btn_pressed == btn) {
		//кнопка все еще нажата
		//защита от повторного вызова
		return true;
	}
	btn_pressed=btn;
	if(clr) {lcd_clear();}
	delay_ms(200);//задержка от дребезга контактов
	return false;
}






