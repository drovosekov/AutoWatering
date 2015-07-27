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

	//��������� ������������ �������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //��� ��� ��������� � ��������� ������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //�������� ����� �������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //�������� ����� ����������� ������� ������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //��������� ������ ��� ���� ������

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

	PIN_CONFIGURATION(ADC_CH0); //������ ��������� ������
	PIN_CONFIGURATION(ADC_CH1); //������� ���������� ������������

	PIN_CONFIGURATION(DS18B20_1WIRE_PORT);

	PIN_CONFIGURATION(BACKLIGHT_PWM);
	PIN_CONFIGURATION(CONTRAST_PWM);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);//�������������� ������ ��� ������� (PC8, PC9)

	PIN_CONFIGURATION(NO_WATER_LED);
	PIN_CONFIGURATION(WATERING_RELAY);
	PIN_CONFIGURATION(HUMIDITY_SENSOR);
	PIN_CONFIGURATION(WATER_LEVER_SENSOR);

	PIN_CONFIGURATION(BUTTON_SART);
	PIN_CONFIGURATION(BUTTON_LEFT);
	PIN_CONFIGURATION(BUTTON_RIGHT);
	PIN_CONFIGURATION(BUTTON_EXIT);
	PIN_CONFIGURATION(BUTTON_MENU);
	PIN_CONFIGURATION(BUTTON_RESET);
	PIN_CONFIGURATION(BUTTON_ENTER);

	PIN_CONFIGURATION(LCD_2X16_RS);
	PIN_CONFIGURATION(LCD_2X16_E);
	PIN_CONFIGURATION(LCD_2X16_DB4);
	PIN_CONFIGURATION(LCD_2X16_DB5);
	PIN_CONFIGURATION(LCD_2X16_DB6);
	PIN_CONFIGURATION(LCD_2X16_DB7);
}
