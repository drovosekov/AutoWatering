
#ifndef MISC_H_
#define MISC_H_
/////should be defined by user /////

//#define SENS_2WIRE - not yet tested
#define SENS_3WIRE
#define DS18B20_RESOLUTION		DS18B20_9BIT

/* ADC defines */
#define ADC_CH0				A, 0, HIGH, ANALOG, SPEED_2MHZ
#define ADC_CH1				A, 1, HIGH, ANALOG, SPEED_2MHZ
/* end ADC defines */

/* buttons defines */
#define BUTTON_EXIT			A, 2, HIGH, INPUT_PULL_DOWN, SPEED_2MHZ
#define BUTTON_MENU			A, 3, HIGH, INPUT_PULL_DOWN, SPEED_2MHZ
#define BUTTON_LEFT			A, 4, HIGH, INPUT_PULL_DOWN, SPEED_2MHZ
#define BUTTON_RIGHT		A, 5, HIGH, INPUT_PULL_DOWN, SPEED_2MHZ
#define BUTTON_SART			A, 6, HIGH, INPUT_PULL_DOWN, SPEED_2MHZ
#define BUTTON_RESET		A, 7, HIGH, INPUT_PULL_DOWN, SPEED_2MHZ
#define BUTTON_ENTER		A, 8, HIGH, INPUT_PULL_DOWN, SPEED_2MHZ
#define WATER_LEVER_SENSOR	A, 10, HIGH, INPUT_PULL_DOWN, SPEED_2MHZ
/* end buttons defines */

/* out pins defines */
#define DS18B20_1WIRE_PORT	A, 9,  HIGH, ALTERNATE_OUTPUT_PUSH_PULL, SPEED_50MHZ //1-wire DS18B20

#define HUMIDITY_SENSOR		B, 8,  HIGH, GENERAL_OUTPUT_PUSH_PULL,   SPEED_2MHZ //blue led on the discovery board
#define WATERING_RELAY		B, 9,  HIGH, GENERAL_OUTPUT_PUSH_PULL,   SPEED_2MHZ //green led on the discovery board
#define NO_WATER_LED		B, 10, HIGH, GENERAL_OUTPUT_PUSH_PULL,   SPEED_2MHZ

#define BACKLIGHT_PWM		C, 8,  HIGH, ALTERNATE_OUTPUT_PUSH_PULL, SPEED_10MHZ //альтернативный выход TIM3 CH3
#define CONTRAST_PWM		C, 9,  HIGH, ALTERNATE_OUTPUT_PUSH_PULL, SPEED_10MHZ //альтернативный выход TIM3 CH4
/* end out pins defines */

/* LCD defines */
#define LCD_PORT	GPIOC
#define LCD_RS		0
#define LCD_EN		1
#define LCD_DB4		2
#define LCD_DB5		3
#define LCD_DB6		4
#define LCD_DB7		5

#define LCD_2X16_RS		C, LCD_RS,  HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_10MHZ
#define LCD_2X16_E		C, LCD_EN,  HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_10MHZ
#define LCD_2X16_DB4	C, LCD_DB4, HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_10MHZ
#define LCD_2X16_DB5	C, LCD_DB5, HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_10MHZ
#define LCD_2X16_DB6	C, LCD_DB6, HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_10MHZ
#define LCD_2X16_DB7	C, LCD_DB7, HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_10MHZ

#define LCD_EN_BC  (BIT(LCD_EN+16))
#define LCD_RS_BC  (BIT(LCD_RS+16))
#define LCD_DB4_BC (BIT(LCD_DB4+16))
#define LCD_DB5_BC (BIT(LCD_DB5+16))
#define LCD_DB6_BC (BIT(LCD_DB6+16))
#define LCD_DB7_BC (BIT(LCD_DB7+16))
#define LCD_ALL_PINS_OFF 		(LCD_DB7_BC | LCD_DB6_BC | LCD_DB5_BC | LCD_DB4_BC | LCD_RS_BC | LCD_EN_BC)
#define LCD_ALL_DATA_PINS_OFF	(LCD_DB7_BC | LCD_DB6_BC | LCD_DB5_BC | LCD_DB4_BC)
/* end LCD defines */

#define tMORNING_WATERING_TIME_BKP	BKP_DR2	//утреннее время начала разрешенного интервала полива
#define tEVENING_WATERING_TIME_BKP	BKP_DR3	//вечернее время окончания разрешенного интервала полива
#define HUMYDURTY_BKP				BKP_DR4	//минимальный и максимальный уровень влажности для полива
#define CHECK_INTERVAL_BKP			BKP_DR5	//интервал проверки уровня влажности (минут)
#define WATERING_DURATION_BKP		BKP_DR6 //интервал задержки перед поливом (минут)
#define BRIGHT_CONTRAST_BKP			BKP_DR7 //уровни яркости подсветки и контраста

///////////////////////////////////

#define BIT(NUMBER)            		(1UL << (NUMBER))


void SysTick_Handler();
void delay_ms(u16 ms);
void delay_for(u16 del);
u16 absolute(s16 value);
u8 CheckBit(int dwNumber, u16 iBit);
u8 get_low(u16 value);
u8 get_height(u16 value);
u16 set_low_n_height(u8 low, u8 height);
u8 get_TIM_state(TIM_TypeDef* TIMx);

#endif
