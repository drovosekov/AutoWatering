#include "main.h"

static void move_by_menu_LR(buttons direction);
//защитка от дребезга
static u8 save_pressed_buton(buttons btn, u8 clr);


u8 timeout_menu_count;

static buttons btn_pressed=0;

void get_buttons_state(){
	if (PIN_STATE(BUTTON_ENTER)) {
		if(save_pressed_buton(BTN_STATE_ENTER, true))
			{return;}//если кнопка все еще нажата - выходим

		//PIN_ON(LED_GREEN);
		switch(regim){
		case DISPLAY_REGIM_DEFAULT:
		case DISPLAY_REGIM_WATERING:
		case DISPLAY_REGIM_MANUAL_WATERING:
		case DISPLAY_REGIM_NO_WATER:
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

	}else if (PIN_STATE(BUTTON_MENU)) {
		if(save_pressed_buton(BTN_STATE_MENU, false))
			{return;}//если кнопка все еще нажата - выходим

		regim = DISPLAY_REGIM_MENU;
		lcd_set_state(LCD_ENABLE, CURSOR_DISABLE);
		init_menu();

	}else if(PIN_STATE(BUTTON_START)) {
		if(save_pressed_buton(BTN_STATE_START, false))
			{return;}

		if(get_TIM_state(TIM6) && regim != DISPLAY_REGIM_NO_WATER){
			PIN_ON(WATERING_RELAY);					//запуск полива (вкл.реле)
			regim = DISPLAY_REGIM_MANUAL_WATERING;
		}

	}else if(PIN_STATE(BUTTON_EXIT)) {
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

	}else if (PIN_STATE(BUTTON_LEFT)) {
		move_by_menu_LR(BTN_STATE_LEFT);

	}else if (PIN_STATE(BUTTON_RIGHT)) {
		move_by_menu_LR(BTN_STATE_RIGHT);

	}else if(PIN_STATE(BUTTON_RESET)) {
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

	}else if (PIN_STATE(WATER_LEVER_SENSOR)) {
		regim = DISPLAY_REGIM_NO_WATER;
		PIN_ON(NO_WATER_LED);

	}else if(regim == DISPLAY_REGIM_MANUAL_WATERING) {
		PIN_OFF(WATERING_RELAY);		//стоп полива (откл.реле)
		regim = DISPLAY_REGIM_DEFAULT;

	}else{
		btn_pressed = BTN_STATE_RESET;

	}
}

void auto_exit_from_menu(){
	if(regim != DISPLAY_REGIM_DEFAULT &&
	   regim != DISPLAY_REGIM_MANUAL_WATERING &&
	   regim != DISPLAY_REGIM_WATERING &&
	   regim != DISPLAY_REGIM_NO_WATER){
		//проверяем истечение времени по таймауту выхода из меню
		if(timeout_menu_count > TIMEOUT_MENU_EXIT) {
			save_pressed_buton(BTN_STATE_RESET, true);
			lcd_clear();
			lcd_set_state(LCD_ENABLE, CURSOR_DISABLE);
			regim = DISPLAY_REGIM_DEFAULT;
    		TIM_Cmd(TIM7, ENABLE);
		}else{
			timeout_menu_count++;
			delay_ms(50);
		}
	}
}

void auto_bright_off(){
	static u8 bright_off_count = 0;

	if(regim == DISPLAY_REGIM_DEFAULT ||
	   regim == DISPLAY_REGIM_NO_WATER) {
		if(bright_off_count > TIMEOUT_MENU_EXIT){
			//отключаем подсветку
			TIM_SetCompare3(TIM3, 0);
			bright_off_count = 0;
		}else{
			bright_off_count++;
		}
	}else{
		init_bright_contrast();
		bright_off_count = 0;
	}
}

void move_by_menu_LR(buttons direction){
	timeout_menu_count=0;

	switch(regim){
	case DISPLAY_REGIM_MANUAL_WATERING:
	case DISPLAY_REGIM_WATERING:
	case DISPLAY_REGIM_DEFAULT:
	case DISPLAY_REGIM_NO_WATER:
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






