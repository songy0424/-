#ifndef __CONTRAL_H
#define __CONTRAL_H

#include "stm32f10x.h"

#define ABS(x) ((x)>=0?(x):-(x))

void Core_App_X(void);																//�����ֿ���
void Core_App_Y(void);				  											//�����ֿ���

void Motor_SetAngle(int pwm);													//�������ٶ�
void Motor_SetSpeed(int pwm);   											//�������ٶ�
void Limit(int *pwm);
void Limit1(int *pwm);
void Stop(void);

int Vertical(float Med,float Angle,float gyro_x);			//����ֱ����
int Velocity (int encoder_motor);											//�����ٶȻ�

int Vertical1(float Med,float Angle,float gyro_x);		//����ֱ����
int Velocity1 (int encoder_motor);										//�����ٶȻ�

#endif /* __CONTRAL_H */
