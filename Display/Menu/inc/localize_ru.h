
#ifndef MAIN_LOCALIZE
#define MAIN_LOCALIZE

#define LOGO_LINE0		" DROVOSEKOV.NET"
#define LOGO_LINE1		"Автополиватор v1"
#define LOGO_SHOW_TIME	1500	//время показа логотипа в мс

#define MENU_COUNT		7	//количество пунктов меню
#define MENU0 			"Уст.время/дата"
#define MENU1 			"Интервал полива"
#define MENU2 			"Длит. полива"
#define MENU3 			"Уровень влажн."
#define MENU4 			"Интервал опроса"
#define MENU5 			"Режим полива"
#define MENU6			"Досветка"
#define MENU7 			"Подств/контраст"

#define MENU_SEL		0x1D	//знак стрелочки для выбранного пункта меню
#define MENU_UP			0x12	//стрелочка вверх (для прокрутки в меню)
#define MENU_DOWN		0x13	//стрелочка вниз (для прокрутки в меню)

#define SET_M0_DT0			"Время:"
#define SET_M0_DT1			"Дата: "
#define M0_HOUR_LCD_POS		7
#define M0_MINUTE_LCD_POS	10
#define M0_DAY_LCD_POS		7
#define M0_MONTH_LCD_POS	10
#define M0_YEAR_LCD_POS		15

#define SET_M1_W0			"Утро: "
#define SET_M1_W1			"Вечер:"
#define M1_HOUR_LCD_POS		7
#define M1_MINUTE_LCD_POS	10

#define SET_M2_HUM_MIN		"Мин.влажн: "
#define SET_M2_DURATION		"Задержка: "
#define SET_M2_MINUT		"мин "
#define M2_MIN_H_LCD_POS	12
#define M2_DURATION_LCD_POS	9

#define SET_M3_DURATION1	"Длительность"
#define SET_M3_DURATION2	"полива "
#define SET_M3_SECOND		" сек"
#define M3_VAL_LCD_POS		8

#define SET_M4_CHK_INTERVAL	"Опрос дат.влажн."
#define SET_M4_ONE_PER		"Раз в "
#define SET_M4_MINUT		" мин"
#define M4_VAL_LCD_POS		7

#define SET_M5_REGIM		"Режим: "
#define SET_M5_REGIM_AUTO	"Авто  "
#define SET_M5_REGIM_MANUAL	"Ручной"
#define SET_M5_AUTO_OFF		"Откл.через 3 мин"
#define SET_M5_SPACE		"                "
#define M5_VAL_LCD_POS		7

#define SET_M6_LIGHT0		"С:"
#define SET_M6_LIGHT1		" До:"
#define SET_M6_LIGHT2		"Да "
#define SET_M6_LIGHT3		"Нет"
#define SET_M6_LIGHT4		"Активна: "
#define M6_FROM_H_LCD_POS	3
#define M6_FROM_M_LCD_POS	6
#define M6_TO_H_LCD_POS		12
#define M6_TO_M_LCD_POS		15
#define M6_REGIM_SWCH		9

#define SET_M7_BRIGTH		"Яркость: "
#define SET_M7_CONTRAST		"Контраст:"
#define M7_VAL_LCD_POS		10


#define T_SEP			":"
#define D_SEP			"-"
#define FLOAT_POINT		"."
#define BAT_VOLT		"в"
#define WATERING_STATE	"ПОЛИВ"
#define NO_WATER		"Нет ВОДЫ"
#define NO_WATER_SPACE	"          "
#define MANUAL_REGIM	"Ручн."
#define NOT_CHEK_TIME	"--:--"


#define SYMB_DRIB				0
#define SYMB_DEGREE				1
#define SYMB_MANUAL_REG			2
#define SYMB_AUTO_REG_FILL		3
#define SYMB_AUTO_REG_NoFILL	4
#define SYMB_BAT_EMPTY			5
#define SYMB_BAT_50_PERC		6
#define SYMB_BAT_100_PERC		7
#define SYMB_CHECK_W_SENSOR		"@"

#endif
