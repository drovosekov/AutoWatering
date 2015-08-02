#include "main.h"

//Timer Functions
static u16 delay = 0;

// Timer interrupt each 1 ms
void SysTick_Handler(void)
{
	if(delay){delay--;}
}

void delay_ms(u16 ms)
{
	delay = ms;
	while(delay){}
}

//in traps (exti) functions delay_ms not working
//so call this function
void delay_for(u16 del)
{
	u16 i;
	for(i=0; i<del; i++){}
}

u16 absolute(s16 value) {
	if (value < 0) {
		return -value;
	}
	return value;
}

/*
//проверка состояния бита - установлен или нет
u8 CheckBit(int dwNumber, u16 iBit)
{
    return (dwNumber & iBit);
}*/

//состояние таймера - запущен или нет
u8 get_TIM_state(TIM_TypeDef* TIMx){
	return TIMx->CR1 & TIM_CR1_CEN;
}

//младший полубайт
u8 get_low(u16 value){
	return value & 0xFF;
}

//старший полубайт
u8 get_height(u16 value){
	return value >> 8;
}

//склееиваем два байта
u16 set_low_n_height(u8 height, u8 low){
	 return (height << 8) | low;
}
