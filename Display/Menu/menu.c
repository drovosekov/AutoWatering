#include "main.h"

static void AddMenu(u8 idx, char *text, u8 regim, void *func);
static void print_selected_menu(u8 marker, u8 line, char *menu_text);


static menu Menu[MENU_COUNT+1];	//массив описаний меню
static u8 scr;	//используется для отсчета паузы до показа стрелочек прокрутки (500мс)
static s8 dir;
static s8 cursor_menu;	//выбранное положение в меню

void init_menu(){
	cursor_menu = 0;

	if(Menu[0].RegimMenu != 0)//если меню уже инициализированно - выходим
		{return;}

	AddMenu(0, MENU0, DISPLAY_REGIM_SET_TIME_DATE, 		&init_set_date_time);
	AddMenu(1, MENU1, DISPLAY_REGIM_SET_WATERING_TIME,	&init_set_watering_time);
	AddMenu(2, MENU2, DISPLAY_REGIM_SET_WAERING_DUR, 	&init_set_watering_duration);
	AddMenu(3, MENU3, DISPLAY_REGIM_SET_HUMIDITY, 		&init_set_humidity);
	AddMenu(4, MENU4, DISPLAY_REGIM_SET_CHK_INTERVAL, 	&init_set_chk_interval);
	AddMenu(5, MENU5, DISPLAY_REGIM_SET_WATERING_REG, 	&init_set_watering_reg);
	AddMenu(6, MENU6, DISPLAY_REGIM_SET_LIGHT,			&init_set_light_time);
	AddMenu(7, MENU7, DISPLAY_REGIM_SET_BRIGHT_CONTR, 	&init_set_bright_contrast);
}

void AddMenu(u8 idx, char *text, u8 regim, void *func){
	Menu[idx].Text = text;
	Menu[idx].RegimMenu = regim;
	Menu[idx].Func = func;
}

void btn_enter_pressed_in_menu(){
	Menu[cursor_menu].Func();
	regim = Menu[cursor_menu].RegimMenu;
	lcd_set_state(LCD_ENABLE, CURSOR_ENABLE);
}

void btn_move_in_menu(buttons *direction){
	dir = *direction;
	cursor_menu += *direction;
	if(cursor_menu == MENU_COUNT + 1){cursor_menu = MENU_COUNT;}
	if(cursor_menu == -1) {cursor_menu = 0;}
	scr = 0;
}

void display_menu_draw(){
	if(cursor_menu == 0 || dir == -1){
		print_selected_menu(true, 0,  Menu[cursor_menu].Text);
		print_selected_menu(false, 1, Menu[cursor_menu+1].Text);
	}else{
		print_selected_menu(false, 0, Menu[cursor_menu-1].Text);
		print_selected_menu(true,  1, Menu[cursor_menu].Text);
	}

	//отрисовка стрелочек вверх/вниз (прокрутка)
	//с задержкой 500мс
	if(scr == 10){
		if(cursor_menu == 0){
			lcd_set_xy(15, 1);
			lcd_send_data(MENU_DOWN);
		}else if(cursor_menu == MENU_COUNT){
			lcd_set_xy(15, 0);
			lcd_send_data(MENU_UP);
		}else{
			lcd_set_xy(15, 1);
			lcd_send_data(MENU_DOWN);
			lcd_set_xy(15, 0);
			lcd_send_data(MENU_UP);
		}
	}else{
		scr++;
	}
}

void print_selected_menu(u8 marker, u8 line, char *menu_text){
	static u8 cur_m=0;

	if(cursor_menu == cur_m && timeout_menu_count > 1){return;}
	cur_m = cursor_menu;

	lcd_set_xy(0, line);
	if(marker) {
		lcd_send_data(MENU_SEL);
	}else{
		lcd_out(" ");
	}
	lcd_out(menu_text);
	//чтоб не очищать экран целиком - забиваем лишнее пробелами
	lcd_out("         ");
}
