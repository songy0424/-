/*��������
	���� 	��PA6		  TIM3Ch1
				��PA7		  TIM3Ch2
	
	�Ƕ� 	��PB6			TIM4Ch1
				��PB7			TIM4Ch2
*/

#ifndef  __BSP_ENCODER_H
#define  __BSP_ENCODER_H
#include "stm32f10x.h"

int Read_Encoder_TIM3(void);
int Read_Encoder_TIM4(void);
void Encoder_Init(void);

#endif /*__BSP_ENCODER_H*/

