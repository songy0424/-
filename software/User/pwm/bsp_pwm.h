/*��������
	L_EN ��PA1
	R_EN ��PA2
*/
#ifndef __BSP_PWM_H
#define __BSP_PWM_H

#include "stm32f10x.h"

/*����Ϊͨ��3������ͨ��4*/
 
void PWM_GPIO_Config(void);
void PWM_TIM_Config(uint16_t,uint16_t);
void PWM_Channel_Config(void);														//���ֵ��ٶȵ��ڳ�ʼ��
	 	
#endif /* __BSP_PWM_H */
