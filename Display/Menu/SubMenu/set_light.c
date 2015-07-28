#include "main.h"

u8 timeout_menu_count;
u8 cursor_x, cursor_y;
display_regim regim;

static sTIME t_morning, t_evening;
static u8 light_regim;

void init_set_light_time(){
	cursor_x = M6_FROM_H_LCD_POS;
	cursor_y = 0;

	u16 result = BKP_ReadBackupRegister(tMORNING_LIGHT_TIME_BKP);
	t_morning.hour=	result >> 8;
	t_morning.min=	result & 0xFF;

	result = BKP_ReadBackupRegister(tEVENING_LIGHT_TIME_BKP);
	t_evening.hour=	result >> 8;
	t_evening.min=	result & 0xFF;

	light_regim = BKP_ReadBackupRegister(ACTIVE_LIGHT_TIME_BKP);
}

void btn_enter_pressed_in_set_light_time(){
	if(cursor_y == 0){
		if(cursor_x == M6_FROM_H_LCD_POS){
			cursor_x = M6_FROM_M_LCD_POS;
		}else if(cursor_x == M6_FROM_M_LCD_POS){
			cursor_x = M6_TO_H_LCD_POS;
		}else if(cursor_x == M6_TO_H_LCD_POS){
			cursor_x = M6_TO_M_LCD_POS;
		}else if(cursor_x == M6_TO_M_LCD_POS){
			cursor_x = M6_REGIM_SWCH;
			cursor_y = 1;
		}
	}else{
		/* Allow access to BKP Domain */
		PWR_BackupAccessCmd(ENABLE);

		u16 result = (t_morning.hour << 8) | t_morning.min;
		BKP_WriteBackupRegister(tMORNING_LIGHT_TIME_BKP, result);

		result = (t_evening.hour << 8) | t_evening.min;
		BKP_WriteBackupRegister(tEVENING_LIGHT_TIME_BKP, result);

		BKP_WriteBackupRegister(ACTIVE_LIGHT_TIME_BKP, light_regim);

		PWR_BackupAccessCmd(DISABLE);

		regim = DISPLAY_REGIM_MENU;		//выходим в меню
		lcd_set_state(LCD_ENABLE, CURSOR_DISABLE);
	}
}

void btn_move_in_set_light_time(buttons direction){
	if(cursor_y == 0){//устновка часов и минут
		if(cursor_x == M6_FROM_H_LCD_POS){
			de_in_crement_value(&(t_morning.hour), 0, 11, direction);
		}else if(cursor_x == M6_FROM_M_LCD_POS){
			de_in_crement_value(&(t_morning.min), 0, 59, direction);
		}else if(cursor_x == M6_TO_H_LCD_POS){
			de_in_crement_value(&(t_evening.hour), 14, 23, direction);
		}else if(cursor_x == M6_TO_M_LCD_POS){
			de_in_crement_value(&(t_evening.min), 0, 59, direction);
		}
	}else{
		light_regim = !light_regim;
	}
	display_set_light_time_draw();
}

void display_set_light_time_draw(){
	if(timeout_menu_count == 0){
		//верхняя строка на дисплее
		lcd_set_xy(0, 0);
		lcd_out(SET_M6_LIGHT0);
		lcd_write_dec_xx(t_morning.hour);
		lcd_out(T_SEP);
		lcd_write_dec_xx(t_morning.min);
		lcd_out(SET_M6_LIGHT1);
		lcd_write_dec_xx(t_evening.hour);
		lcd_out(T_SEP);
		lcd_write_dec_xx(t_evening.min);

		//нижняя строка на дисплее
		lcd_set_xy(0, 1);
		lcd_out(SET_M6_LIGHT4);
		lcd_out(light_regim ? SET_M6_LIGHT2 : SET_M6_LIGHT3);

		lcd_set_xy(cursor_x, cursor_y);
	}
}
