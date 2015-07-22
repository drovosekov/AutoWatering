#include "main.h"

void init_periph(void){

	PIN_CONFIGURATION(ADC_CH0);
	PIN_CONFIGURATION(ADC_CH1);

	PIN_CONFIGURATION(BACKLIGHT_PWM);
	PIN_CONFIGURATION(CONTRAST_PWM);

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

}
