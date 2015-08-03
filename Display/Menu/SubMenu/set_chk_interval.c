#include "main.h"

void init_set_chk_interval();
void display_set_chk_interval_draw();
void btn_enter_pressed_in_set_chk_interval();
void btn_move_in_set_chk_interval(buttons direction);


u8 timeout_menu_count;
u8 cursor_x, cursor_y;
display_regim regim;

static u8 chk_int;

void init_set_chk_interval(){
	cursor_x=M4_VAL_LCD_POS;
	cursor_y=1;

	chk_int = (u8)BKP_ReadBackupRegister(CHECK_INTERVAL_BKP);
}

void btn_enter_pressed_in_set_chk_interval(){
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);

	BKP_WriteBackupRegister(CHECK_INTERVAL_BKP, chk_int);

	PWR_BackupAccessCmd(DISABLE);

	regim = DISPLAY_REGIM_MENU;		//выходим в меню
	lcd_set_state(LCD_ENABLE, CURSOR_DISABLE);
}

void btn_move_in_set_chk_interval(buttons direction){
	de_in_crement_value(&chk_int, 1, 99, direction);
	display_set_chk_interval_draw();
}

void display_set_chk_interval_draw(){
	if(timeout_menu_count == 0){
		//верхн€€ строка на дисплее
		lcd_set_xy(0, 0);
		lcd_out(SET_M4_CHK_INTERVAL);

		//нижн€€ строка на дисплее
		lcd_set_xy(0, 1);
		lcd_out(SET_M4_ONE_PER);
		lcd_write_dec_xx(chk_int);
		lcd_out(SET_M4_MINUT);

		lcd_set_xy(cursor_x, cursor_y);
	}
}
