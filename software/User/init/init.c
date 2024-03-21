/*
 * @Date: 2023-09-21 16:14:37
 * @LastEditTime: 2023-09-21 17:26:54
 * @Description:
 */
#include "init.h"
#include "bsp_pwm.h"
#include "bsp_motor.h"
#include "bsp_usart.h"
#include "bsp_oled.h"
#include "bsp_encoder.h"
#include "mpu6050.h"
#include "timer.h"
#include "delay.h"
#include "bsp_adc.h"

void GPIO_INIT(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pinx, GPIOMode_TypeDef GPIO_Modex)
{
	GPIO_InitTypeDef GPIO_InitStructure; // ����GPIO_InitTypeDef�ṹ��

	if (GPIOx == GPIOA)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // ��������ʱ��
	else if (GPIOx == GPIOB)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // ��������ʱ��
	else if (GPIOx == GPIOC)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // ��������ʱ��
	else if (GPIOx == GPIOD)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); // ��������ʱ��
	else if (GPIOx == GPIOE)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); // ��������ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Modex;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void INIT_ALL(void)
{
	Motor_GPIO_Config();		 	// �����GPIO��ʼ��
	PWM_GPIO_Config();		 		// PWM��GPIO��ʼ��
	PWM_TIM_Config(1000, 3); 	// PWM�Ķ�ʱ����ʼ��
	PWM_Channel_Config();	 		// PWM��ͨ����ʼ��
	OLED_Init();			 				// OLED��ʼ��
	USART1_Init();			 			// ����1��ʼ��
	Encoder_Init();			 			// ��������ʼ��
	delay_init();			 				// �ӳٺ�����ʼ��
	//	ADC1_Init();
	MPU_Init();
	delay_ms(700);
	if (mpu_dmp_init() == 0)
	{
	}
	Timer1_Init(10); 					// ��TIM1����Ϊ10ms��ʱ�жϣ����������п����㷨
}
