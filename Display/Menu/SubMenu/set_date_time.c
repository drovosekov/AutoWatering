#include "main.h"

void init_set_date_time();
void display_set_date_time_draw();
void btn_enter_pressed_in_set_date_time();
void btn_move_in_set_date_time(buttons direction);


u8 timeout_menu_count;
u8 cursor_x, cursor_y;
display_regim regim;

static RTCTIME rtc_clck;

void init_set_date_time(){
	RTC_GetTime(&rtc_clck);
	cursor_x = M0_HOUR_LCD_POS;
	cursor_y = 0;
}

void btn_enter_pressed_in_set_date_time(){
	if(cursor_y == 0){
		if(cursor_x == M0_MINUTE_LCD_POS){
			cursor_x = M0_DAY_LCD_POS;	//редактируем день
			cursor_y = 1;					//редактируем дату
		}else{
			cursor_x = M0_MINUTE_LCD_POS;	//редактируем минуты
		}
	}else if(cursor_x == M0_DAY_LCD_POS){
		cursor_x = M0_MONTH_LCD_POS;		//редактируем месяц
	}else if(cursor_x == M0_MONTH_LCD_POS){
		cursor_x = M0_YEAR_LCD_POS;		//редактируем год
	}else{
		RTC_SetTime(&rtc_clck);			//запоминаем измененное время и дату

		regim = DISPLAY_REGIM_MENU;		//выходим в меню
		lcd_set_state(LCD_ENABLE, CURSOR_DISABLE);
	}
}

void btn_move_in_set_date_time(buttons direction){
	if(cursor_y == 0){//устновка часов и минут
		if(cursor_x == M0_HOUR_LCD_POS){
			de_in_crement_value(&(rtc_clck.hour), 0, 23, direction);
		}else if(cursor_x == M0_MINUTE_LCD_POS){
			de_in_crement_value(&(rtc_clck.min), 0, 59, direction);
		}
	}else{			//установка даты
		if(cursor_x == M0_DAY_LCD_POS){
			de_in_crement_value(&(rtc_clck.mday), 1, RTC_DaysInMonth(rtc_clck.year, rtc_clck.month), direction);
		}else if(cursor_x == M0_MONTH_LCD_POS){
			de_in_crement_value(&(rtc_clck.month), 1, 12, direction);
		}else if(cursor_x == M0_YEAR_LCD_POS){
			rtc_clck.year += direction;
		}
	}
	display_set_date_time_draw();
}

void display_set_date_time_draw(){
	if(timeout_menu_count == 0){
		//верхняя строка на дисплее
		lcd_set_xy(0, 0);
		lcd_out(SET_M0_DT0);
		lcd_write_dec_xx(rtc_clck.hour);
		lcd_out(T_SEP);
		lcd_write_dec_xx(rtc_clck.min);

		//нижняя строка на дисплее
		lcd_set_xy(0, 1);
		lcd_out(SET_M0_DT1);
		lcd_write_dec_xx(rtc_clck.mday);
		lcd_out(D_SEP);
		lcd_write_dec_xx(rtc_clck.month);
		lcd_out(D_SEP);
		lcd_write_dec_xxxx(rtc_clck.year);

		lcd_set_xy(cursor_x, cursor_y);
	}
}
