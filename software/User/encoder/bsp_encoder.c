/*
 * @Date: 2023-09-21 16:14:37
 * @LastEditTime: 2023-09-21 17:07:44
 * @Description:
 */
#include "bsp_encoder.h"
#include "init.h"

void Encoder_Init(void) // ������
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct; // ����ṹ��
	TIM_ICInitTypeDef TIM_ICInitStruct;				// ����ṹ��

	GPIO_INIT(GPIOA, GPIO_Pin_6, GPIO_Mode_IN_FLOATING); // GPIO��ʼ��
	GPIO_INIT(GPIOA, GPIO_Pin_7, GPIO_Mode_IN_FLOATING); // GPIO��ʼ��
	GPIO_INIT(GPIOB, GPIO_Pin_6, GPIO_Mode_IN_FLOATING); // GPIO��ʼ��
	GPIO_INIT(GPIOB, GPIO_Pin_7, GPIO_Mode_IN_FLOATING); // GPIO��ʼ��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // ʱ�ӳ�ʼ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // ʱ�ӳ�ʼ��

	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct); // ��ʼ����ʱ��
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);

	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // ���ñ�����ģʽ
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // ���ñ�����ģʽ

	TIM_ICStructInit(&TIM_ICInitStruct); // ��ʼ�����벶��
	TIM_ICInitStruct.TIM_ICFilter = 10;
	TIM_ICInit(TIM3, &TIM_ICInitStruct);
	TIM_ICInit(TIM4, &TIM_ICInitStruct);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // ������������жϱ�־λ
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	TIM_SetCounter(TIM3, 0); // ���㶨ʱ������ֵ
	TIM_SetCounter(TIM4, 0);

	TIM_Cmd(TIM3, ENABLE); // ������ʱ��
	TIM_Cmd(TIM4, ENABLE);
}

/**********************
������
�ٶȶ�ȡ����
��ڲ�������ʱ��
**********************/

int Read_Encoder_TIM3(void)
{
	int Encoder_Value;
	Encoder_Value = TIM_GetCounter(TIM3); // ��ȡ����
	if (Encoder_Value > 0xefff)
		Encoder_Value = Encoder_Value - 0xffff; // ת������ֵΪ�з����ֵ������0��ת��С��0��ת��
												// TIM3->CNT��ΧΪ0-0xffff����ֵΪ0��
	TIM_SetCounter(TIM3, 0);					// ��ȡ����������

	return Encoder_Value; // ����ֵ
}

int Read_Encoder_TIM4(void)
{
	int Encoder_Value;
	Encoder_Value = TIM_GetCounter(TIM4); // ��ȡ����
	if (Encoder_Value > 0xefff)
		Encoder_Value = Encoder_Value - 0xffff; // ת������ֵΪ�з����ֵ������0��ת��С��0��ת��
												// TIM4->CNT��ΧΪ0-0xffff����ֵΪ0��
	TIM_SetCounter(TIM4, 0);					// ��ȡ����������

	return Encoder_Value; // ����ֵ
}

 void TIM3_IRQHandler(void)
 {
 	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=0)
 	{
 		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
 	}
 }
 void TIM4_IRQHandler(void)
 {
 	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=0)
 	{
 		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
 	}
 }
