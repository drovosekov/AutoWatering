#include "main.h"

void init_set_humidity();
void display_set_humidity_draw();
void btn_enter_pressed_in_set_humidity();
void btn_move_in_set_humidity(buttons direction);


u8 timeout_menu_count;
u8 cursor_x, cursor_y;
display_regim regim;

static u8 min_H, duration;

void init_set_humidity(){
	cursor_x=M2_MIN_H_LCD_POS;
	cursor_y=0;

	u16 result = BKP_ReadBackupRegister(HUMYDURTY_BKP);
	min_H =		get_height(result);
	duration =	get_low(result);
}

void btn_enter_pressed_in_set_humidity(){
	if(cursor_y==0){
		cursor_y=1;	//редактируем макс. значение
	}else{
		regim = DISPLAY_REGIM_MENU;		//выходим в меню
		lcd_set_state(LCD_ENABLE, CURSOR_DISABLE);

		/* Allow access to BKP Domain */
		PWR_BackupAccessCmd(ENABLE);

		BKP_WriteBackupRegister(HUMYDURTY_BKP, set_low_n_height(min_H, duration));

		PWR_BackupAccessCmd(DISABLE);
	}
}

void btn_move_in_set_humidity(buttons direction){
	if(cursor_y==0){//устновка мин. значения
		de_in_crement_value(&min_H, 10, 70, direction);
	}else{			//установка макс. значения
		de_in_crement_value(&duration, 30, 250, direction);
	}
	display_set_humidity_draw();
}

void display_set_humidity_draw(){
	if(timeout_menu_count == 0){
		//верхняя строка на дисплее
		lcd_set_xy(0, 0);
		lcd_out(SET_M2_HUM_MIN);
		lcd_write_dec_xx(min_H);
		lcd_out("%");

		//нижняя строка на дисплее
		lcd_set_xy(0, 1);
		lcd_out(SET_M2_DURATION);
		if(duration<100)	{lcd_write_dec_xx(duration);}
		else 				{lcd_write_dec_xxx(duration);}
		lcd_out(SET_M2_MINUT);

		lcd_set_xy(cursor_x, cursor_y);
	}
}
