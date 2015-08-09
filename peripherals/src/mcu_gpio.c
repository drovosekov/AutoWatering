/*
 *	File:	mcu_gpio.c
 *	Date:	07.01.2011
 */

#include "main.h"

//-----------------------------------------------------------------------------
void mcu_gpio_deinit()
{
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	//разрешаем тактирование таймеров
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ШИМ для подсветки и контраста экрана
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //задержка перед поливом
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //задержка перед отключением ручного режима
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //секундный таймер для инфо экрана

	//разрешаем тактирование портов
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

	//настрока выводов МК
	PIN_CONFIGURATION(ADC_CH0); //датчик влажности грунта
	PIN_CONFIGURATION(ADC_CH1); //уровень напряжения аккумулятора

	PIN_CONFIGURATION(DS18B20_1WIRE_PORT);

	PIN_CONFIGURATION(BACKLIGHT_PWM);
	PIN_CONFIGURATION(CONTRAST_PWM);
	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);//альтернативные выходы для таймера (PC8, PC9)

	PIN_CONFIGURATION(NO_WATER_LED);
	PIN_CONFIGURATION(WATERING_RELAY);
	PIN_CONFIGURATION(HUMIDITY_SENSOR);
	PIN_CONFIGURATION(WATER_LEVER_SENSOR);
	PIN_CONFIGURATION(LIGHT_RELAY);
	PIN_CONFIGURATION(LIGHT_SENSOR);

	PIN_CONFIGURATION(BUTTONS_PIN_A2);
	PIN_CONFIGURATION(BUTTONS_PIN_A3);
	PIN_CONFIGURATION(BUTTONS_PIN_A4);

	PIN_CONFIGURATION(LCD_2X16_RS);
	PIN_CONFIGURATION(LCD_2X16_E);
	PIN_CONFIGURATION(LCD_2X16_DB4);
	PIN_CONFIGURATION(LCD_2X16_DB5);
	PIN_CONFIGURATION(LCD_2X16_DB6);
	PIN_CONFIGURATION(LCD_2X16_DB7);
}



buttons get_keyboard_state(){
	u8 buttons_state = 0;

	if(!PIN_STATE(BUTTONS_PIN_A2)) {buttons_state |= 0b00000001;}
	if(!PIN_STATE(BUTTONS_PIN_A3)) {buttons_state |= 0b00000010;}
	if(!PIN_STATE(BUTTONS_PIN_A4)) {buttons_state |= 0b00000100;}

	switch(buttons_state){
		case 1:		return BTN_STATE_MENU;
		case 2:		return BTN_STATE_STOP;
		case 3:		return BTN_STATE_ENTER;
		case 4:		return BTN_STATE_START;
		case 5:		return BTN_STATE_LEFT;
		case 6:		return BTN_STATE_EXIT;
		case 7:		return BTN_STATE_RIGHT;
		default:	return BTN_STATE_RESET;
	}
}
