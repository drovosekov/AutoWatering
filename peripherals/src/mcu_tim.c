#include "main.h"
#include "stm32f10x.h"

void init_tim(){
	/* управление яркостью и контрастом */
    // Конфигурация таймера в режим PWM
    TIM_TimeBaseInitTypeDef TIM_BaseConfig;
    // Конфигурация выхода таймера
    TIM_OCInitTypeDef TIM_OCConfig;

    // Конфигурируем выход таймера, режим - PWM1
    TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
    // Собственно - выход включен
    TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
    // Пульс длинной 500 тактов => 500/1000 = 50%
    TIM_OCConfig.TIM_Pulse = 500;
    // Полярность => пульс - это единица (+3.3V)
    TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_Low;
    // Инициализируем 3й выход таймера №3
    TIM_OC3Init(TIM3, &TIM_OCConfig);

    // Конфигурируем второй выход таймера
    TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
    // Пульс длинной 500 тактов => 500/1000 = 50%
    TIM_OCConfig.TIM_Pulse = 500;
    // Ради эксперемента, меняем полярность (пульс - 0V).
    TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_Low;
    // Инициализируем 4й выход таймера №3
    TIM_OC4Init(TIM3, &TIM_OCConfig);

    // Включаем таймер
    TIM_Cmd(TIM3, ENABLE);


    /* отсчет интервала задержки перед поливом */
	//устанавливаем уровень приоритета прерывания от таймера TIM4
	NVIC_SetPriority(TIM4_IRQn, 2);
	//разрешаем обработку прерывания от таймера TIM4
	NVIC_EnableIRQ(TIM4_IRQn);
    TIM_BaseConfig.TIM_Prescaler = 23999;
    // Период - 1 раз в минуту
    TIM_BaseConfig.TIM_Period = 60000;
    // Инициализируем таймер №4
    TIM_TimeBaseInit(TIM4, &TIM_BaseConfig);
    //разрешаем генерацию прерывания
    TIM_ITConfig(TIM4, TIM_DIER_UIE, ENABLE);
    TIM_Cmd(TIM4, DISABLE);


    /* ежесекундный вызов процедуры отрисовки инфо-экрана */
	//устанавливаем уровень приоритета прерывания от таймера TIM7
	NVIC_SetPriority(TIM7_IRQn, 1);
	//разрешаем обработку прерывания от таймера TIM7
	NVIC_EnableIRQ(TIM7_IRQn);
    //разрешаем генерацию прерывания
    TIM_ITConfig(TIM7, TIM_DIER_UIE, ENABLE);
    // Запускаем таймер на тактовой частоте в 1 kHz
    TIM_BaseConfig.TIM_Prescaler = 23999;
    // Период - 1000 тактов => 1000/1000 = 1 Hz
    TIM_BaseConfig.TIM_Period = 1000;
    TIM_BaseConfig.TIM_ClockDivision = 0;
    TIM_BaseConfig.TIM_CounterMode = TIM_CounterMode_Up;
    // Инициализируем таймер №7
    TIM_TimeBaseInit(TIM7, &TIM_BaseConfig);
	// запускаем счет таймера
	TIM_Cmd(TIM7, DISABLE);


	/*Поскольку счет начнется с нуля, то сразу же после включения счета
	 * сгенерируется первое прерывание. Если нужно этого избежать,
	 * то надо добавить две строчки:
	 * 	TIM6->EGR |= TIM_EGR_UG;
	 *  TIM6->SR &= ~TIM_SR_UIF;
	 *   .*/

	/* отсчет времени до отключения ручного режима полива */
	//устанавливаем уровень приоритета прерывания от таймера TIM6
	NVIC_SetPriority(TIM6_DAC_IRQn, 3);
	//разрешаем обработку прерывания от таймера TIM6
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
    // Запускаем таймер на тактовой частоте в 1 kHz
    TIM_BaseConfig.TIM_Prescaler = 23999;
    // Период - 3 мин
    TIM_BaseConfig.TIM_Period = 23999;
    // Инициализируем таймер №6
    TIM_TimeBaseInit(TIM6, &TIM_BaseConfig);
    //отключаем генирацию прерывания сразу после запуска таймера
	TIM_GenerateEvent(TIM6, TIM_EGR_UG);
	TIM_ClearFlag(TIM6, TIM_SR_UIF);
    //разрешаем генерацию прерывания
    TIM_ITConfig(TIM6, TIM_DIER_UIE, ENABLE);
	// запускаем счет таймера
    TIM_SelectOnePulseMode(TIM6, TIM_CR1_OPM);
    TIM_Cmd(TIM6, DISABLE);
}


//обработчик прерывания от таймера 6
//задержка перед отключением ручного режима полива - 3мин
void TIM6_DAC_IRQHandler(void)
{
	TIM_ClearFlag(TIM6, TIM_SR_UIF);//Сбрасываем флаг прерывания
	TIM_Cmd(TIM6, DISABLE);
}
