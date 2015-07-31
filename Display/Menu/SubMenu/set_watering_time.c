#include "main.h"

u8 timeout_menu_count;
u8 cursor_x, cursor_y;
display_regim regim;

static sTIME t_morning, t_evening;

void init_set_watering_time(){
	cursor_x = M1_HOUR_LCD_POS;
	cursor_y = 0;

	u16 result = BKP_ReadBackupRegister(tMORNING_WATERING_TIME_BKP);
	t_morning.hour	=	get_height(result);
	t_morning.min =		get_low(result);

	result = BKP_ReadBackupRegister(tEVENING_WATERING_TIME_BKP);
	t_evening.hour =	get_height(result);
	t_evening.min =		get_low(result);
}

void btn_enter_pressed_in_set_watering_time(){
	if(cursor_y == 0){
		if(cursor_x == M1_MINUTE_LCD_POS){
			cursor_x = M1_HOUR_LCD_POS;	//редактируем часы вечера
			cursor_y = 1;					//редактируем вечер
		}else{
			cursor_x = M1_MINUTE_LCD_POS;//редактируем минуты утра
		}
	}else if(cursor_x == M1_HOUR_LCD_POS){
		cursor_x = M1_MINUTE_LCD_POS;	//редактируем минуты вечера
	}else{
		/* Allow access to BKP Domain */
		PWR_BackupAccessCmd(ENABLE);

		BKP_WriteBackupRegister(tMORNING_WATERING_TIME_BKP, set_low_n_height(t_morning.hour, t_morning.min));
		BKP_WriteBackupRegister(tEVENING_WATERING_TIME_BKP, set_low_n_height(t_evening.hour, t_evening.min));

		PWR_BackupAccessCmd(DISABLE);

		regim = DISPLAY_REGIM_MENU;		//выходим в меню
		lcd_set_state(LCD_ENABLE, CURSOR_DISABLE);
	}
}

void btn_move_in_set_watering_time(buttons direction){
	if(cursor_y == 0){//устновка времени начала утра
		if(cursor_x == M1_HOUR_LCD_POS){
			de_in_crement_value(&(t_morning.hour), 0, 12, direction);
		}else if(cursor_x == M1_MINUTE_LCD_POS){
			de_in_crement_value(&(t_morning.min), 0, 59, direction);
		}
	}else{			//установка времени начала вечера
		if(cursor_x == M1_HOUR_LCD_POS){
			de_in_crement_value(&(t_evening.hour), 13, 23, direction);
		}else if(cursor_x == M1_MINUTE_LCD_POS){
			de_in_crement_value(&(t_evening.min), 0, 59, direction);
		}
	}
	display_set_watering_time_draw();
}

void display_set_watering_time_draw(){
	if(timeout_menu_count == 0){
		//верхняя строка на дисплее
		lcd_set_xy(0, 0);
		lcd_out(SET_M1_W0);
		lcd_write_dec_xx(t_morning.hour);
		lcd_out(T_SEP);
		lcd_write_dec_xx(t_morning.min);

		//нижняя строка на дисплее
		lcd_set_xy(0, 1);
		lcd_out(SET_M1_W1);
		lcd_write_dec_xx(t_evening.hour);
		lcd_out(T_SEP);
		lcd_write_dec_xx(t_evening.min);


		lcd_set_xy(cursor_x, cursor_y);
	}
}
