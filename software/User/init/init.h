#ifndef __INIT_H
#define __INIT_H

#include "stm32f10x.h"			

void GPIO_INIT(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pinx, GPIOMode_TypeDef GPIO_Modex);   	//ֻ�ܳ�ʼ��GPIO
void INIT_ALL(void);  				//���Գ�ʼ������������

#endif /* __INIT_H */
