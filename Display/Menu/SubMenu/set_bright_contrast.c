#include "main.h"

void init_set_bright_contrast();
void display_set_bright_contrast_draw();
void btn_enter_pressed_in_set_bright_contrast();
void btn_move_in_set_bright_contrast(buttons direction);

u8 timeout_menu_count;
u8 cursor_x, cursor_y;
display_regim regim;

static u8 bright, contrast;

void init_set_bright_contrast(){
	cursor_x=M7_VAL_LCD_POS;
	cursor_y=0;

	u16 result = BKP_ReadBackupRegister(BRIGHT_CONTRAST_BKP);
	bright =	get_height(result);
	contrast =	get_low(result);
}

void btn_enter_pressed_in_set_bright_contrast(){
	if(cursor_y == 0){
		cursor_y = 1;	//редактируем макс. контарст
	}else{
		regim = DISPLAY_REGIM_MENU;		//выходим в меню
		lcd_set_state(LCD_ENABLE, CURSOR_DISABLE);

		/* Allow access to BKP Domain */
		PWR_BackupAccessCmd(ENABLE);

		BKP_WriteBackupRegister(BRIGHT_CONTRAST_BKP, set_low_n_height(bright, contrast));

		PWR_BackupAccessCmd(DISABLE);
	}
}

void btn_move_in_set_bright_contrast(buttons direction){
	if(cursor_y == 0){//устновка мин. значения
		de_in_crement_value(&bright, 0, 16, direction);
		TIM_SetCompare3(TIM3, bright * 4095);
	}else{			//установка макс. значения
		de_in_crement_value(&contrast, 10, 16, direction);
		TIM_SetCompare4(TIM3, contrast * 4095);
	}
	display_set_bright_contrast_draw();
}

void display_set_bright_contrast_draw(){
	if(timeout_menu_count == 0){
		//верхняя строка на дисплее
		lcd_set_xy(0, 0);
		lcd_out(SET_M7_BRIGTH);
		lcd_write_dec_xxx(bright);

		//нижняя строка на дисплее
		lcd_set_xy(0, 1);
		lcd_out(SET_M7_CONTRAST);
		lcd_write_dec_xxx(contrast);

		lcd_set_xy(cursor_x, cursor_y);
	}
}
