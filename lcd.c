#if 0

void LCD_test();

#include "main.h"


void LCD_test(){
	lcd_set_state(LCD_ENABLE, CURSOR_DISABLE);

	int i=0;
	while(i<0xFF){
		lcd_set_xy(0,0);
		lcd_write_dec_xxx(i);

		lcd_set_xy(0,1);
		lcd_send(i, DATA);
		i++;

		delay_ms(700);
	}

	lcd_set_xy(0, 0);
	//lcd_out("�����Ũ����������");
	lcd_set_xy(0, 1);
	//lcd_out("����������������");
	//lcd_out("����������������");
	//lcd_out("����������������");


	delay_ms(17000);
}

#endif
