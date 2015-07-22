
#ifndef AW_MENU
#define AW_MENU


#include "main.h"
#include "localize.h"

#define TIMEOUT_MENU_EXIT	200//������� ������ �� ���� - 10��� (200*50ms �������� �����)


typedef enum {
	DISPLAY_REGIM_DEFAULT 			= 0,	//��������� ����� - ��������� �����
	DISPLAY_REGIM_MENU 				= 1,	//���� ��������
	DISPLAY_REGIM_SET_TIME_DATE		= 2,	//��������� ����, �������
	DISPLAY_REGIM_SET_WATERING_TIME	= 3,	//��������� ��������� ������� ������
	DISPLAY_REGIM_SET_HUMIDITY		= 4,	//��������� ������� ��������� (��� � ����)
	DISPLAY_REGIM_SET_CHK_INTERVAL	= 5,	//�������� ������ ������� ��������� (�����)
	DISPLAY_REGIM_SET_WAERING_DUR	= 6,	//����������������� ������ (������)
	DISPLAY_REGIM_SET_WATERING_REG	= 7,	//����� ������ ������ ������ (�������. ��� ������ �����)
	DISPLAY_REGIM_SET_BRIGHT_CONTR	= 12,	//����� ��������� ��������� � ������� ����������
	DISPLAY_REGIM_SET_LIGHT			= 8,	//����� ������ ��������� (����� �� �������-�� ������� � ���/����)
	DISPLAY_REGIM_WATERING			= 9,	//������� ������ ������
	DISPLAY_REGIM_MANUAL_WATERING	= 10,	//����� ������� ������
	DISPLAY_REGIM_NO_WATER			= 11	//����� ��� ���� � ����������
} display_regim;


typedef enum {
	BTN_STATE_RESET	= 0,	//�� ���� ������ �� ������
	BTN_STATE_LEFT	= -1,	//�����
	BTN_STATE_RIGHT	= 1,	//������
	BTN_STATE_MENU	= 2,	//���� � ����
	BTN_STATE_START	= 3,	//������ ������ �������
	BTN_STATE_EXIT	= 4,	//����� �� ����
	BTN_STATE_ENTER	= 5,	//����
	BTN_STATE_STOP	= 6		//����� (����)
} buttons;


typedef struct {
	char	*Text;		/* ����� ���� */
	u8		RegimMenu;	/* �������� ������ */
	void	(*Func)();	/* ����� ���������� �� ���� ������� */
} menu;


typedef struct {
	uint8_t		hour;	/* 0..23 */
	uint8_t		min;	/* 0..59 */
} sTIME;

extern u8 timeout_menu_count;
extern u8 cursor_x, cursor_y;
extern display_regim regim;


//���������� � ����� ������ ��������� �������
//� ��������� ��������� ������
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
