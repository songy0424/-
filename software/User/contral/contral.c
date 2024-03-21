#include "contral.h"
#include "bsp_motor.h"
#include "bsp_usart.h"
#include "bsp_encoder.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "bsp_oled.h"

double SpeedX, SpeedY;

// ������
float Med_Angle = 0;
float
	Vertical_Kp = -125 ,		// -125����
	Vertical_Kd = -1.60; 		//-1.60����
float
	Velocity_Kp = 7.9,			//	8  	   	7.8   	 	7.9	   ���� 
	Velocity_Ki = 0.039; 		//  0.03   	0.036		  0.0039 ����
int Vertical_out, Velocity_out, Turn_out; 
int Encoder_Motor;

////������
float Med_Angle1 = 0;
float
	Vertical_Kp1 = -130*0.6, //-54  -84   	-80		-120
	Vertical_Kd1 = -0.28*0.6;//-0.1  -0.12				-0.27
float
	Velocity_Kp1 = -38,	//-30											-38
	Velocity_Ki1 = -0.19;//-0.15									-0.19
int Vertical_out1, Velocity_out1;
int Encoder_Motor1;

int PWM1, PWM2;

float Pitch, Roll, Yaw;
short aacx, aacy, aacz;
short gyrox, gyroy, gyroz;

int PWM_MAX = 700, PWM_MIN = -700;
int PWM_MAX1 = 800, PWM_MIN1 = -800;

void Core_App_X(void) // ������
{
	Encoder_Motor1 = Read_Encoder_TIM3();
	mpu_dmp_get_data(&Pitch, &Roll, &Yaw);
	MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);
	MPU_Get_Accelerometer(&aacx, &aacy, &aacz);
	gyroy-=15;
	
//	OLED_ShowSignedNum(1,1,gyroy,3);

	Vertical_out1 = Vertical1(Med_Angle1, Pitch, gyroy);
	Velocity_out1 = Velocity1(Encoder_Motor1);
	
//	OLED_ShowSignedNum(2,1,Vertical_out1,5);
//	OLED_ShowSignedNum(2,7,Velocity_out1,5);
	
	PWM2 = Vertical_out1+Velocity_out1;
	Limit1(&PWM2);
	Motor_SetSpeed(PWM2);
	Stop();
}

void Core_App_Y(void) // �Ƕ���
{
	Encoder_Motor = Read_Encoder_TIM4();
	mpu_dmp_get_data(&Pitch, &Roll, &Yaw);
	MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);
	MPU_Get_Accelerometer(&aacx, &aacy, &aacz);
	gyrox += 190;

//	OLED_ShowSignedNum(1, 1, Roll, 4);

	Vertical_out = Vertical(Med_Angle, Roll, gyrox);
	Velocity_out = Velocity(Encoder_Motor);

//	OLED_ShowSignedNum(2, 1, Vertical_out, 4);
//	OLED_ShowSignedNum(2, 7, Velocity_out, 4);

	PWM1 = Vertical_out+ Velocity_out;
	Limit(&PWM1);
	Motor_SetAngle(PWM1);
	Stop();
}

/**
 * @brief �����ֵ�ֱ��������
 * @param {float} Med �� Ŀ��Ƕ�
 * @param {float} Angle	����ǰ�Ƕ�
 * @param {float} gyro_x �����ٶ�
 * @return {*}
 */
int Vertical(float Med, float Angle, float gyro_x)
{
	int PWM_out1;
	PWM_out1 = Vertical_Kp * (Angle - Med) + Vertical_Kd * (gyro_x);
	 Limit(&PWM_out1);
	return PWM_out1;
}

/**
 * @brief �����ֵ��ٶȻ�����
 * @param {int} encoder_motor
 * @return {*}
 */
int Velocity(int encoder_motor) // �����ٶȻ�
{
	static int Encoder_S, EnC_Err_Lowout_last, PWM_out2, Encoder_Err, EnC_Err_Lowout;
	float a = 0.7;

	Encoder_Err = encoder_motor;

	EnC_Err_Lowout = (1 - a) * Encoder_Err + a * EnC_Err_Lowout_last;
	EnC_Err_Lowout_last = EnC_Err_Lowout;

	Encoder_S += EnC_Err_Lowout;
	Encoder_S = Encoder_S > 800 ? 800 : (Encoder_S < (-800) ? (-800) : Encoder_S);

	PWM_out2 = Velocity_Kp * EnC_Err_Lowout + Velocity_Ki * Encoder_S;

	//	OLED_ShowSignedNum(3,1,Encoder_S,5);
	//	OLED_ShowSignedNum(3,7,EnC_Err_Lowout,5);
	Limit(&PWM_out2);
	return PWM_out2;
}

int Vertical1(float Med, float Angle, float gyro_x) // ����ֱ����
{
	int PWM_out1;
	PWM_out1 = Vertical_Kp1 * (Angle - Med) + Vertical_Kd1 * (gyro_x);
	Limit1(&PWM_out1);
	return PWM_out1;
}

int Velocity1(int encoder_motor) // �����ٶȻ�
{
	static int Encoder_S, EnC_Err_Lowout_last, PWM_out2, Encoder_Err, EnC_Err_Lowout;
	float a = 0.7;
	Encoder_Err = encoder_motor;
	EnC_Err_Lowout = (1 - a) * Encoder_Err + a * EnC_Err_Lowout_last;
	EnC_Err_Lowout_last = EnC_Err_Lowout;
	Encoder_S += EnC_Err_Lowout;
	Encoder_S = Encoder_S > 1000 ? 1000 : (Encoder_S < (-1000) ? (-1000) : Encoder_S);
	PWM_out2 = Velocity_Kp1 * EnC_Err_Lowout + Velocity_Ki1 * Encoder_S;
	//	OLED_ShowSignedNum(3,1,Encoder_S,5);
	//	OLED_ShowSignedNum(3,7,EnC_Err_Lowout,5);
	Limit1(&PWM_out2);
	return PWM_out2;
}

void Motor_SetAngle(int pwm) // ���ƶ����ֵ��
{
	if (pwm > 0)
	{
		START(1);
		DIR(0); // ��ת
		TIM_SetCompare4(TIM2, 1000 - pwm);
	}
	else
	{
		START(1);
		DIR(1); // ��ת
	}
	TIM_SetCompare4(TIM2, 1000 - ABS(pwm));
}

void Motor_SetSpeed(int pwm) // �����������
{
	if (pwm > 0) // ��ת
	{
		IN1(High);
		IN2(Low);
		TIM_SetCompare3(TIM2, pwm);
	}
	else // ��ת
	{
		IN1(Low);
		IN2(High);
		TIM_SetCompare3(TIM2, ABS(pwm));
	}
}

/*�޷�����*/
void Limit(int *pwm)
{
	if (*pwm > PWM_MAX)
		*pwm = PWM_MAX;
	if (*pwm < PWM_MIN)
		*pwm = PWM_MIN;
}

void Limit1(int *pwm)
{
	if (*pwm > PWM_MAX1)
		*pwm = PWM_MAX1;
	if (*pwm < PWM_MIN1)
		*pwm = PWM_MIN1;
}

void Stop(void) // �жϽǶ��Ƿ��������Ǿ͹ر��ж�,�����õ��PWMΪ0
{
	if (ABS(Roll) >= 25 || ABS(Pitch) >= 45) //
	{
		START(0);
		TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
		TIM_SetCompare3(TIM2, 0);
		TIM_SetCompare4(TIM2, 1000);
	}
}
