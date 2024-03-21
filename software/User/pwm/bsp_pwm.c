/*
 * @Date: 2023-09-21 16:14:37
 * @LastEditTime: 2023-09-21 17:08:10
 * @Description:
 */
#include "bsp_pwm.h"
#include "init.h"
#include "bsp_motor.h"

void PWM_GPIO_Config(void) // PWM��GPIO��ʼ��
{
	START(0);
	GPIO_INIT(GPIOA, GPIO_Pin_3, GPIO_Mode_AF_PP);
	GPIO_INIT(GPIOA, GPIO_Pin_2, GPIO_Mode_AF_PP);
}

void PWM_TIM_Config(uint16_t arr, uint16_t psc) // ��ʼ��PWM
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitStruct.TIM_Period = arr - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc - 1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
}

void PWM_Channel_Config(void) // ͨ����ʼ��
{
	TIM_OCInitTypeDef TIM_OCInitStruct;

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;			   // ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; // �Ƚ����ʹ��
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;	   // �������:TIM����Ƚϼ��Ը�

	TIM_OC3Init(TIM2, &TIM_OCInitStruct);
	TIM_OC4Init(TIM2, &TIM_OCInitStruct);

	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable); // ʹ��TIM2��CCR3�ϵ�Ԥװ�ؼĴ���

	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable); // ʹ��TIM2��CCR4�ϵ�Ԥװ�ؼĴ���

	TIM_Cmd(TIM2, ENABLE);
}
