/*
 * @Date: 2023-09-21 16:14:37
 * @LastEditTime: 2023-09-21 17:05:43
 * @Description:
 */
#include "timer.h"

void Timer1_Init(uint16_t Period) // ms
{
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_BaseInitStructure.TIM_Period = (Period * 10) - 1;
	TIM_BaseInitStructure.TIM_Prescaler = 7200 - 1;
	TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);
	TIM_ClearFlag(TIM1, TIM_FLAG_Update); // ���жϱ�־λ

	TIM_ITConfig(						// ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM1,							// TIM1
		TIM_IT_Update | TIM_IT_Trigger, // TIM �����ж�Դ
		ENABLE							// ʹ��
	);

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM1, ENABLE);
}
