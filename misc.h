
#ifndef MISC_H_
#define MISC_H_

#define ARRAY_LENGHT(x)  (sizeof(x) / sizeof((x)[0]))

void SysTick_Handler();
void delay_ms(u16 ms);
void delay_for(u16 del);
u16 absolute(s16 value);
u8 get_low(u16 value);
u8 get_height(u16 value);
u16 set_low_n_height(u8 low, u8 height);
u8 get_TIM_state(TIM_TypeDef* TIMx);

#endif
