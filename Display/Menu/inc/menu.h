
#ifndef AW_MENU
#define AW_MENU


#include "main.h"
#include "localize.h"

#define TIMEOUT_MENU_EXIT	200//таймайт выхода из меню - 10сек (200*50ms задержки цикла)


typedef enum {
	DISPLAY_REGIM_DEFAULT 			= 0,	//начальный режим - дефолтный экран
	DISPLAY_REGIM_MENU 				= 1,	//меню настроек
	DISPLAY_REGIM_SET_TIME_DATE		= 2,	//настройка даты, времени
	DISPLAY_REGIM_SET_WATERING_TIME	= 3,	//настройка интервала времени полива
	DISPLAY_REGIM_SET_HUMIDITY		= 4,	//настройка уровней влажности (мин и макс)
	DISPLAY_REGIM_SET_CHK_INTERVAL	= 5,	//интервал опроса датчика влажности (минут)
	DISPLAY_REGIM_SET_WAERING_DUR	= 6,	//продолжительность полива (секунд)
	DISPLAY_REGIM_SET_WATERING_REG	= 7,	//выбор режима работы полива (автомат. или ручной полив)
	DISPLAY_REGIM_SET_BRIGHT_CONTR	= 12,	//режим настройки контраста и €ркости подстветки
	DISPLAY_REGIM_SET_LIGHT			= 8,	//режим работы подсветки (врем€ со скольки-до скольки и вкл/выкл)
	DISPLAY_REGIM_WATERING			= 9,	//процесс режима полива
	DISPLAY_REGIM_MANUAL_WATERING	= 10,	//режим ручного полива
	DISPLAY_REGIM_NO_WATER			= 11	//когда нет воды в резервуаре
} display_regim;


typedef enum {
	BTN_STATE_RESET	= 0,	//ни одна кнопка не нажата
	BTN_STATE_LEFT	= -1,	//влево
	BTN_STATE_RIGHT	= 1,	//вправо
	BTN_STATE_MENU	= 2,	//вход в меню
	BTN_STATE_START	= 3,	//запуск полива вручную
	BTN_STATE_EXIT	= 4,	//выход из меню
	BTN_STATE_ENTER	= 5,	//ввод
	BTN_STATE_STOP	= 6		//сброс (стоп)
} buttons;


typedef struct {
	char	*Text;		/* текст меню */
	u8		RegimMenu;	/* название режима */
	void	(*Func)();	/* адрес вызываемой из меню функции */
} menu;


typedef struct {
	uint8_t		hour;	/* 0..23 */
	uint8_t		min;	/* 0..59 */
} sTIME;

extern u8 timeout_menu_count;
extern u8 cursor_x, cursor_y;
extern display_regim regim;


//определ€ем в каком режиме находитс€ дисплей
//и провер€ем состо€ни€ кнопок
void get_buttons_state();
void auto_exit_from_menu();

void init_display_default();
void display_default_draw();
void btn_menu_pressed_in_deault();
void check_humidity_sensor();
void check_humidity_value();

void init_menu();
void display_menu_draw();
void btn_enter_pressed_in_menu();
void btn_move_in_menu(buttons *direction);

void init_set_date_time();
void display_set_date_time_draw();
void btn_enter_pressed_in_set_date_time();
void btn_move_in_set_date_time(buttons direction);

void init_set_watering_time();
void display_set_watering_time_draw();
void btn_enter_pressed_in_set_watering_time();
void btn_move_in_set_watering_time(buttons direction);

void init_set_watering_duration();
void display_set_watering_duration_draw();
void btn_enter_pressed_in_set_watering_duration();
void btn_move_in_set_watering_duration(buttons direction);

void init_set_humidity();
void display_set_humidity_draw();
void btn_enter_pressed_in_set_humidity();
void btn_move_in_set_humidity(buttons direction);

void init_set_chk_interval();
void display_set_chk_interval_draw();
void btn_enter_pressed_in_set_chk_interval();
void btn_move_in_set_chk_interval(buttons direction);

void init_set_watering_reg();
void display_set_watering_reg_draw();
void btn_enter_pressed_in_set_watering_reg();
void btn_move_in_set_watering_reg(buttons direction);

void init_set_bright_contrast();
void display_set_bright_contrast_draw();
void btn_enter_pressed_in_set_bright_contrast();
void btn_move_in_set_bright_contrast(buttons direction);

void de_in_crement_value(u8 *val, u8 min_val, u8 max_val, buttons direction);

#endif
