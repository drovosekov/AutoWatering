#include "main.h"

void init_set_watering_duration();
void display_set_watering_duration_draw();
void btn_enter_pressed_in_set_watering_duration();
void btn_move_in_set_watering_duration(buttons direction);


u8 timeout_menu_count;
u8 cursor_x, cursor_y;
display_regim regim;

u8 watering_duration;

void init_set_watering_duration(){
	cursor_x=M3_VAL_LCD_POS;
	cursor_y=1;

	watering_duration = (u8)BKP_ReadBackupRegister(WATERING_DURATION_BKP);
}

void btn_enter_pressed_in_set_watering_duration(){
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);

	BKP_WriteBackupRegister(WATERING_DURATION_BKP, watering_duration);

	PWR_BackupAccessCmd(DISABLE);

	regim = DISPLAY_REGIM_MENU;		//выходим в меню
	lcd_set_state(LCD_ENABLE, CURSOR_DISABLE);
}

void btn_move_in_set_watering_duration(buttons direction){
	de_in_crement_value(&watering_duration, 5, 30, direction);
	display_set_watering_duration_draw();
}

void display_set_watering_duration_draw(){
	if(timeout_menu_count == 0){
		//верхняя строка на дисплее
		lcd_set_xy(0, 0);
		lcd_out(SET_M3_DURATION1);

		lcd_set_xy(0, 1);
		lcd_out(SET_M3_DURATION2);
		lcd_write_dec_xx(watering_duration);
		lcd_out(SET_M3_SECOND);

		lcd_set_xy(cursor_x, cursor_y);
	}
}
