/*
 *	File:	GPIO.h
 *	Date:	07.01.2011
 */

#ifndef MCU_GPIO_H_
#define MCU_GPIO_H_

void mcu_gpio_deinit();
buttons get_keyboard_state();

/////should be defined by user /////

/* DS18B20 gpio defines */
//#define SENS_2WIRE - not yet tested
#define SENS_3WIRE
#define DS18B20_RESOLUTION	DS18B20_9BIT

#define DS18B20_1WIRE_PORT	A, 9,  HIGH, ALTERNATE_OUTPUT_PUSH_PULL, SPEED_10MHZ //1-wire DS18B20
/* end DS18B20 gpio defines */

/* ADC defines */
#define ADC_CH0				A, 0, HIGH, ANALOG, SPEED_2MHZ //������ ��������� ������
#define ADC_CH1				A, 7, HIGH, ANALOG, SPEED_2MHZ //������� ������ ������������
/* end ADC defines */

/* buttons defines */
#define BUTTONS_PIN_A2		A, 2, HIGH, INPUT_PULL_UP, SPEED_2MHZ
#define BUTTONS_PIN_A3		A, 3, HIGH, INPUT_PULL_UP, SPEED_2MHZ
#define BUTTONS_PIN_A4		A, 4, HIGH, INPUT_PULL_UP, SPEED_2MHZ

#define LIGHT_SENSOR		A, 5, HIGH, INPUT_PULL_DOWN, SPEED_2MHZ //������ ������������
#define WATER_LEVER_SENSOR	A, 10, HIGH, INPUT_PULL_DOWN, SPEED_2MHZ //������ ������ ���� (������)
/* end buttons defines */

/* out pins defines */
#define USER_LED			A, 1, HIGH, ALTERNATE_OUTPUT_PUSH_PULL, SPEED_10MHZ //user LED on STM32F100C8T6 board

#define HUMIDITY_SENSOR		B, 0, HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_2MHZ //������� ������� ��������� ������
//#define BACKLIGHT_PWM		B, 0, HIGH, ALTERNATE_OUTPUT_PUSH_PULL, SPEED_10MHZ //����� TIM3 CH3
#define CONTRAST_PWM		B, 1, HIGH, ALTERNATE_OUTPUT_PUSH_PULL, SPEED_10MHZ //����� TIM3 CH4

#define NO_WATER_LED		B, 2, HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_2MHZ //��������� ���������� ���� � ����
#define WATERING_RELAY		B, 8, HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_2MHZ //���� ������ ������
#define LIGHT_RELAY			B, 9, HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_2MHZ //���� ������� ���������
/* end out pins defines */

/* LCD defines */
#define LCD_RS		15
#define LCD_EN		14
#define LCD_DB4		13
#define LCD_DB5		12
#define LCD_DB6		11
#define LCD_DB7		10

#define LCD_2X16_RS		B, LCD_RS,  HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_10MHZ
#define LCD_2X16_E		B, LCD_EN,  HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_10MHZ
#define LCD_2X16_DB4	B, LCD_DB4, HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_10MHZ
#define LCD_2X16_DB5	B, LCD_DB5, HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_10MHZ
#define LCD_2X16_DB6	B, LCD_DB6, HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_10MHZ
#define LCD_2X16_DB7	B, LCD_DB7, HIGH, GENERAL_OUTPUT_PUSH_PULL, SPEED_10MHZ

#define LCD_PORT	GPIOB
#define LCD_EN_BC  (BIT(LCD_EN+16))
#define LCD_RS_BC  (BIT(LCD_RS+16))
#define LCD_DB4_BC (BIT(LCD_DB4+16))
#define LCD_DB5_BC (BIT(LCD_DB5+16))
#define LCD_DB6_BC (BIT(LCD_DB6+16))
#define LCD_DB7_BC (BIT(LCD_DB7+16))
#define LCD_ALL_DATA_PINS_OFF	(LCD_DB7_BC | LCD_DB6_BC | LCD_DB5_BC | LCD_DB4_BC)
#define LCD_ALL_PINS_OFF 		(LCD_ALL_DATA_PINS_OFF | LCD_RS_BC | LCD_EN_BC)
/* end LCD defines */

/* backup registers defines */
#define tMORNING_WATERING_TIME_BKP	BKP_DR2	//�������� ����� ������ ������������ ��������� ������
#define tEVENING_WATERING_TIME_BKP	BKP_DR3	//�������� ����� ��������� ������������ ��������� ������
#define HUMYDURTY_BKP				BKP_DR4	//����������� � ������������ ������� ��������� ��� ������
#define CHECK_INTERVAL_BKP			BKP_DR5	//�������� �������� ������ ��������� (�����)
#define WATERING_DURATION_BKP		BKP_DR6 //�������� �������� ����� ������� (�����)
#define BRIGHT_CONTRAST_BKP			BKP_DR7 //������ ������� ��������� � ���������
#define tMORNING_LIGHT_TIME_BKP		BKP_DR8	//�������� ����� ��������� ���.���������
#define tEVENING_LIGHT_TIME_BKP		BKP_DR9	//�������� ����� ��������� ���.���������
#define ACTIVE_LIGHT_TIME_BKP		BKP_DR10//������������ ��������
/* end backup registers defines */

///////////////////////////////////

//-----------------------------------------------------------------------------
#define GPIO_PIN_SPEED_2MHZ()	(2UL)
#define GPIO_PIN_SPEED_10MHZ()	(1UL)
#define GPIO_PIN_SPEED_50MHZ()	(3UL)

#define BIT(NUMBER)		(1UL << (NUMBER))

//-----------------------------------------------------------------------------
#define GPIO_PIN0_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRL &= ~(15UL << 0); \
			  GPIO##PORT->CRL |= ((MODE) << 0); }
#define GPIO_PIN1_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRL &= ~(15UL << 4); \
			  GPIO##PORT->CRL |= ((MODE) << 4); }
#define GPIO_PIN2_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRL &= ~(15UL << 8); \
			  GPIO##PORT->CRL |= ((MODE) << 8); }
#define GPIO_PIN3_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRL &= ~(15UL << 12); \
			  GPIO##PORT->CRL |= ((MODE) << 12); }
#define GPIO_PIN4_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRL &= ~(15UL << 16); \
			  GPIO##PORT->CRL |= ((MODE) << 16); }
#define GPIO_PIN5_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRL &= ~(15UL << 20); \
			  GPIO##PORT->CRL |= ((MODE) << 20); }
#define GPIO_PIN6_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRL &= ~(15UL << 24); \
			  GPIO##PORT->CRL |= ((MODE) << 24); }
#define GPIO_PIN7_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRL &= ~(15UL << 28); \
			  GPIO##PORT->CRL |= ((MODE) << 28); }
#define GPIO_PIN8_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRH &= ~(15UL << 0); \
			  GPIO##PORT->CRH |= ((MODE) << 0); }
#define GPIO_PIN9_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRH &= ~(15UL << 4); \
			  GPIO##PORT->CRH |= ((MODE) << 4); }
#define GPIO_PIN10_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRH &= ~(15UL << 8); \
			  GPIO##PORT->CRH |= ((MODE) << 8); }
#define GPIO_PIN11_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRH &= ~(15UL << 12); \
			  GPIO##PORT->CRH |= ((MODE) << 12); }
#define GPIO_PIN12_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRH &= ~(15UL << 16); \
			  GPIO##PORT->CRH |= ((MODE) << 16); }
#define GPIO_PIN13_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRH &= ~(15UL << 20); \
			  GPIO##PORT->CRH |= ((MODE) << 20); }
#define GPIO_PIN14_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRH &= ~(15UL << 24); \
			  GPIO##PORT->CRH |= ((MODE) << 24); }
#define GPIO_PIN15_CONFIGURATION(PORT, MODE) \
			{ GPIO##PORT->CRH &= ~(15UL << 28); \
			  GPIO##PORT->CRH |= ((MODE) << 28); }

//-----------------------------------------------------------------------------
#define GPIO_PIN_CONFIGURATION_ANALOG(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO_PIN##PIN##_CONFIGURATION(PORT, 0UL) }

#define GPIO_PIN_CONFIGURATION_INPUT_FLOATING(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO_PIN##PIN##_CONFIGURATION(PORT, 4UL) }

#define GPIO_PIN_CONFIGURATION_INPUT_PULL_DOWN(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO_PIN##PIN##_CONFIGURATION(PORT, 8UL); \
			  GPIO##PORT->BSRR |= (1UL << PIN) << 16; }

#define GPIO_PIN_CONFIGURATION_INPUT_PULL_UP(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO_PIN##PIN##_CONFIGURATION(PORT, 8UL);  \
	          GPIO##PORT->BSRR |= (1UL << PIN); }

#define GPIO_PIN_CONFIGURATION_GENERAL_OUTPUT_PUSH_PULL(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO_PIN##PIN##_CONFIGURATION(PORT, 0UL | GPIO_PIN_##SPEED()) }

#define GPIO_PIN_CONFIGURATION_GENERAL_OUTPUT_OPEN_DRAIN(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO_PIN##PIN##_CONFIGURATION(PORT, 4UL | GPIO_PIN_##SPEED()) }

#define GPIO_PIN_CONFIGURATION_ALTERNATE_OUTPUT_PUSH_PULL(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO_PIN##PIN##_CONFIGURATION(PORT, 8UL | GPIO_PIN_##SPEED()) }

#define GPIO_PIN_CONFIGURATION_ALTERNATE_OUTPUT_OPEN_DRAIN(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO_PIN##PIN##_CONFIGURATION(PORT, 12UL | GPIO_PIN_##SPEED()) }

//-----------------------------------------------------------------------------
#define GPIO_PIN_CONFIGURATION(PORT, PIN, LEVEL, MODE, SPEED) \
			{ \
			  if((RCC->APB2ENR & RCC_APB2ENR_IOP##PORT##EN) != RCC_APB2ENR_IOP##PORT##EN) \
				{ \
			  	  RCC->APB2ENR |= RCC_APB2ENR_IOP##PORT##EN; \
				} \
			  GPIO_PIN_CONFIGURATION_##MODE(PORT, PIN, LEVEL, MODE, SPEED); \
			}

//-----------------------------------------------------------------------------
#define GPIO_PIN_ON_HIGH(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO##PORT->BSRR |= (1UL << PIN); }

#define GPIO_PIN_ON_LOW(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO##PORT->BSRR |= (1UL << PIN) << 16; }

#define GPIO_PIN_OFF_HIGH(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO##PORT->BSRR |= (1UL << PIN) << 16; }

#define GPIO_PIN_OFF_LOW(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO##PORT->BSRR |= (1UL << PIN); }

//-----------------------------------------------------------------------------
#define GPIO_PIN_ON(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO_PIN_ON_##LEVEL(PORT, PIN, LEVEL, MODE, SPEED) }

#define GPIO_PIN_OFF(PORT, PIN, LEVEL, MODE, SPEED) \
			{ GPIO_PIN_OFF_##LEVEL(PORT, PIN, LEVEL, MODE, SPEED) }

//-----------------------------------------------------------------------------
#define GPIO_PIN_SIGNAL_HIGH(PORT, PIN, LEVEL, MODE, SPEED) \
			( (GPIO##PORT->IDR & (1UL << PIN)) == (1UL << PIN) )

#define GPIO_PIN_SIGNAL_LOW(PORT, PIN, LEVEL, MODE, SPEED) \
		( (GPIO##PORT->IDR & (1UL << PIN)) != (1UL << PIN) )

#define GPIO_PIN_SIGNAL(PORT, PIN, LEVEL, MODE, SPEED) \
			( GPIO_PIN_SIGNAL_##LEVEL(PORT, PIN, LEVEL, MODE, SPEED) )

//-----------------------------------------------------------------------------
#define PIN_CONFIGURATION(PIN_DESCRIPTION) GPIO_PIN_CONFIGURATION(PIN_DESCRIPTION)
#define PIN_ON(PIN_DESCRIPTION) GPIO_PIN_ON(PIN_DESCRIPTION)
#define PIN_OFF(PIN_DESCRIPTION) GPIO_PIN_OFF(PIN_DESCRIPTION)
#define PIN_STATE(PIN_DESCRIPTION) GPIO_PIN_SIGNAL(PIN_DESCRIPTION)

#endif /* MCU_GPIO_H_ */
