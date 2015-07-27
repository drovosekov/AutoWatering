#include "main.h"
#include "stm32f10x.h"

void init_tim(){
	/* ���������� �������� � ���������� */
    // ������������ ������� � ����� PWM
    TIM_TimeBaseInitTypeDef TIM_BaseConfig;
    // ������������ ������ �������
    TIM_OCInitTypeDef TIM_OCConfig;

    // ������������� ����� �������, ����� - PWM1
    TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
    // ���������� - ����� �������
    TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
    // ����� ������� 500 ������ => 500/1000 = 50%
    TIM_OCConfig.TIM_Pulse = 500;
    // ���������� => ����� - ��� ������� (+3.3V)
    TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_Low;
    // �������������� 3� ����� ������� �3
    TIM_OC3Init(TIM3, &TIM_OCConfig);

    // ������������� ������ ����� �������
    TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
    // ����� ������� 500 ������ => 500/1000 = 50%
    TIM_OCConfig.TIM_Pulse = 500;
    // ���� ������������, ������ ���������� (����� - 0V).
    TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_Low;
    // �������������� 4� ����� ������� �3
    TIM_OC4Init(TIM3, &TIM_OCConfig);

    // �������� ������
    TIM_Cmd(TIM3, ENABLE);


    /* ������ ��������� �������� ����� ������� */
	//������������� ������� ���������� ���������� �� ������� TIM4
	NVIC_SetPriority(TIM4_IRQn, 2);
	//��������� ��������� ���������� �� ������� TIM4
	NVIC_EnableIRQ(TIM4_IRQn);
    TIM_BaseConfig.TIM_Prescaler = 23999;
    // ������ - 1 ��� � ������
    TIM_BaseConfig.TIM_Period = 60000;
    // �������������� ������ �4
    TIM_TimeBaseInit(TIM4, &TIM_BaseConfig);
    //��������� ��������� ����������
    TIM_ITConfig(TIM4, TIM_DIER_UIE, ENABLE);
    TIM_Cmd(TIM4, DISABLE);


    /* ������������ ����� ��������� ��������� ����-������ */
	//������������� ������� ���������� ���������� �� ������� TIM7
	NVIC_SetPriority(TIM7_IRQn, 1);
	//��������� ��������� ���������� �� ������� TIM7
	NVIC_EnableIRQ(TIM7_IRQn);
    //��������� ��������� ����������
    TIM_ITConfig(TIM7, TIM_DIER_UIE, ENABLE);
    // ��������� ������ �� �������� ������� � 1 kHz
    TIM_BaseConfig.TIM_Prescaler = 23999;
    // ������ - 1000 ������ => 1000/1000 = 1 Hz
    TIM_BaseConfig.TIM_Period = 1000;
    TIM_BaseConfig.TIM_ClockDivision = 0;
    TIM_BaseConfig.TIM_CounterMode = TIM_CounterMode_Up;
    // �������������� ������ �7
    TIM_TimeBaseInit(TIM7, &TIM_BaseConfig);
	// ��������� ���� �������
	TIM_Cmd(TIM7, DISABLE);


	/*��������� ���� �������� � ����, �� ����� �� ����� ��������� �����
	 * ������������� ������ ����������. ���� ����� ����� ��������,
	 * �� ���� �������� ��� �������:
	 * 	TIM6->EGR |= TIM_EGR_UG;
	 *  TIM6->SR &= ~TIM_SR_UIF;
	 *   .*/

	/* ������ ������� �� ���������� ������� ������ ������ */
	//������������� ������� ���������� ���������� �� ������� TIM6
	NVIC_SetPriority(TIM6_DAC_IRQn, 3);
	//��������� ��������� ���������� �� ������� TIM6
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
    // ��������� ������ �� �������� ������� � 1 kHz
    TIM_BaseConfig.TIM_Prescaler = 23999;
    // ������ - 3 ���
    TIM_BaseConfig.TIM_Period = 23999;
    // �������������� ������ �6
    TIM_TimeBaseInit(TIM6, &TIM_BaseConfig);
    //��������� ��������� ���������� ����� ����� ������� �������
	TIM_GenerateEvent(TIM6, TIM_EGR_UG);
	TIM_ClearFlag(TIM6, TIM_SR_UIF);
    //��������� ��������� ����������
    TIM_ITConfig(TIM6, TIM_DIER_UIE, ENABLE);
	// ��������� ���� �������
    TIM_SelectOnePulseMode(TIM6, TIM_CR1_OPM);
    TIM_Cmd(TIM6, DISABLE);
}


//���������� ���������� �� ������� 6
//�������� ����� ����������� ������� ������ ������ - 3���
void TIM6_DAC_IRQHandler(void)
{
	TIM_ClearFlag(TIM6, TIM_SR_UIF);//���������� ���� ����������
	TIM_Cmd(TIM6, DISABLE);
}
