///////////////////////////////////////////////////////////////////////////////
//	File:	main.h
//	Date:	2015-07-19
///////////////////////////////////////////////////////////////////////////////

#ifndef MAIN_H_
#define MAIN_H_


#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"

#include <stdio.h>
#include <stdbool.h>

//всякие вспомогательный ф-ии
#include "misc.h"

//меню
#include "Display/Menu/inc/localize_ru.h"
#include "Display/Menu/inc/menu.h"

//перефирия
#include "peripherals/inc/mcu_rtc.h"
#include "peripherals/inc/mcu_gpio.h"
//#include "peripherals/inc/mcu_rcc.h"
#include "peripherals/inc/mcu_rtc.h"
#include "peripherals/inc/mcu_pwr.h"
#include "peripherals/inc/mcu_adc.h"
#include "peripherals/inc/mcu_onewire.h"
#include "peripherals/inc/mcu_tim.h"
#include "peripherals/inc/mcu_lcd16x2.h"
#include "peripherals/inc/mcu_thermo_sensor.h"


void init_bright_contrast(void);

#endif /* MAIN_H_ */
