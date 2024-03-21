#include "bsp_usart.h"
#include "init.h"
#include <string.h>

u8 Fore,Back,Left,Right;

void USART1_Init(void)
{
	USART_InitTypeDef USART_InitStructure;   																					//���ڲ������ýṹ�����
	
	//�����ж����ýṹ�����
	GPIO_INIT(GPIOA,GPIO_Pin_9,GPIO_Mode_AF_PP);
	GPIO_INIT(GPIOA,GPIO_Pin_10,GPIO_Mode_IN_FLOATING);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);		                          								

	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate 						= 115200;                 					//���ڲ�����Ϊ115200
	USART_InitStructure.USART_WordLength 					= USART_WordLength_8b;  						//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits 						= USART_StopBits_1;        					//һ��ֹͣλ
	USART_InitStructure.USART_Parity 							= USART_Parity_No;           				//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  	//��Ӳ������������
	USART_InitStructure.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;	  //�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure);                     										//��ʼ������1

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 																		//ʹ���ж�
	USART_Cmd(USART1, ENABLE);                     																		//ʹ�ܴ���1
	USART_ClearFlag(USART1, USART_FLAG_TC);        																		//�崮��1���ͱ�־
}
