#include "main.h"

static void init_all(void);
static void init_default_values(void);

//--глобальные переменные--------
display_regim regim;
//-------------------------------

int main(void)
{
	init_all();

	//LCD_test();

    while (1)
    {
    	get_buttons_state();

    	switch(regim){
		case DISPLAY_REGIM_WATERING:
		case DISPLAY_REGIM_MANUAL_WATERING:
    	case DISPLAY_REGIM_DEFAULT:
    	case DISPLAY_REGIM_NO_WATER:
    		display_default_draw();
			break;

    	case DISPLAY_REGIM_MENU:
    		display_menu_draw();
    		break;

    	case DISPLAY_REGIM_SET_TIME_DATE:
    		display_set_date_time_draw();
    		break;

    	case DISPLAY_REGIM_SET_WATERING_TIME:
    		display_set_watering_time_draw();
    		break;

    	case DISPLAY_REGIM_SET_WAERING_DUR:
    		display_set_watering_duration_draw();
    		break;

    	case DISPLAY_REGIM_SET_HUMIDITY:
    		display_set_humidity_draw();
    		break;

    	case DISPLAY_REGIM_SET_CHK_INTERVAL:
    		display_set_chk_interval_draw();
    		break;

    	case DISPLAY_REGIM_SET_WATERING_REG:
    		display_set_watering_reg_draw();
    		break;

    	case DISPLAY_REGIM_SET_LIGHT:
    		//todo
    		break;

    	case DISPLAY_REGIM_SET_BRIGHT_CONTR:
    		display_set_bright_contrast_draw();
    		break;
    	}

    	auto_exit_from_menu();
    }

	return 0;
}

//инициализируем параметры, при первом включении
void init_default_values(void){
	u16 result = BKP_ReadBackupRegister(WATERING_DURATION_BKP);

	if(result==0){
		/* Allow access to BKP Domain */
		PWR_BackupAccessCmd(ENABLE);
		/* Reset Backup Domain */
		BKP_DeInit();

		//продолжительность полива (сек)
		result=5;
		BKP_WriteBackupRegister(WATERING_DURATION_BKP, result);

		//интервал опроса датчиков
		BKP_WriteBackupRegister(CHECK_INTERVAL_BKP, result);

		result = set_low_n_height(10, 60);//мин.влажность (%) и задержка перед поливом (мин)
		BKP_WriteBackupRegister(HUMYDURTY_BKP, result);

		result = set_low_n_height(9, 0);//утро (час, мин)
		BKP_WriteBackupRegister(tMORNING_WATERING_TIME_BKP, result);
		result = set_low_n_height(18, 0);//вечер (час, мин)
		BKP_WriteBackupRegister(tEVENING_WATERING_TIME_BKP, result);

		result = set_low_n_height(16, 16);//подсветка/контраст
		BKP_WriteBackupRegister(BRIGHT_CONTRAST_BKP, result);

		PWR_BackupAccessCmd(DISABLE);
	}
}

void init_all(void){
	SystemInit();

	//configure SysTimer to 1 ms
	while(SysTick_Config(SystemCoreClock / 2400));

	init_periph();

	lcd_init();

	RTC_Init();

	OW_Init();

	//set DS18B20 resolution 9bit
	u8 data[] = {0xCC, 0x4E, 0, 0, DS18B20_9BIT, 0x48};
	OW_Send(OW_SEND_RESET, data, sizeof(data), 0, 0, OW_NO_READ);
    //OW_Send(OW_SEND_RESET, (u8 *)"\xcc\x4e\x0\x0\x1f\x48", 6, 0, 0, OW_NO_READ);

	init_adc();

	init_tim();

	init_default_values();

	init_display_default();
}

