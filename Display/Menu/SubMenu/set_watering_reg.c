#include "main.h"

u8 timeout_menu_count;
u8 cursor_x, cursor_y;
display_regim regim;
u8 watering_reg;

void init_set_watering_reg(){
	cursor_x=M4_VAL_LCD_POS;
	cursor_y=0;
}

void btn_enter_pressed_in_set_watering_reg(){
	if(watering_reg){
		//запускаем таймер отключени€ ручного режима
		TIM6->CR1 |= TIM_CR1_CEN;
	}
	regim = DISPLAY_REGIM_MENU;		//выходим в меню
	lcd_set_state(LCD_ENABLE, CURSOR_DISABLE);
}

void btn_move_in_set_watering_reg(buttons direction){
	watering_reg = !watering_reg;
	display_set_watering_reg_draw();
	delay_ms(200);
}

void display_set_watering_reg_draw(){
	if(timeout_menu_count == 0){
		//верхн€€ строка на дисплее
		lcd_set_xy(0, 0);
		lcd_out(SET_M5_REGIM);
		lcd_out(watering_reg ? SET_M5_REGIM_MANUAL : SET_M5_REGIM_AUTO);

		//нижн€€ строка на дисплее
		lcd_set_xy(0, 1);
		lcd_out(watering_reg ? SET_M5_AUTO_OFF : SET_M5_SPACE);

		lcd_set_xy(cursor_x, cursor_y);
	}
}
