/*
 *	File:	GPIO.h
 *	Date:	07.01.2011
 */

#ifndef MCU_GPIO_H_
#define MCU_GPIO_H_

//-----------------------------------------------------------------------------
#define GPIO_PIN_SPEED_2MHZ()	(2UL)
#define GPIO_PIN_SPEED_10MHZ()	(1UL)
#define GPIO_PIN_SPEED_50MHZ()	(3UL)

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
#define PIN_SIGNAL(PIN_DESCRIPTION) GPIO_PIN_SIGNAL(PIN_DESCRIPTION)

#endif /* MCU_GPIO_H_ */