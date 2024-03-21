///*
// * @Date: 2023-07-14 13:48:43
// * @LastEditTime: 2023-07-17 17:18:17
// * @Description: ����ȫ�����Ƶ���˶��ĺ���
// */
//#include "control.h"
//#include "init.h"
//#include "bsp_encoder.h"
//#include "data_pid.h"
//#include "Fire_protocol.h"

//unsigned char location_control_count = 0; // ִ��Ƶ�ʲ���Ҫ��ô�ߵ�������¼������������ж���

//float MotorPWM = 0.0, Motor2PWM = 0.0;

//float speed_Outval, location_Outval;
//float speed2_Outval, location2_Outval;
//float Line_Outval = 0;
//int Turn_val;

//u8 Line_flag;
//u8 Spin_start_flag, Spin_succeed_flag, Stop_Flag;
//u8 stop_count, spin_count;

//u8 is_motor_en = 1; // ���ʹ��״̬

//float g_fTargetJourney = 0;				   // ���С������������Ҫ�ߵ�·�̺ͣ���λcm
//float Motor_journey_cm, Motor2_journey_cm; // ��ŵ�ǰ�����߹���·�̣���λcm

///**
// * @brief ��ʱ��7�жϴ�������ͬʱΪPID���ƺ���
// * @return
// */
//void TIM7_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
//	{
//		GetMotorPulse();
//		Motor_journey_cm = (g_lMotorPulseSigma / (30 * 11 * 4)) * (6.5 * 3.14);
//		Motor2_journey_cm = (g_lMotor2PulseSigma / (30 * 11 * 4)) * (6.5 * 3.14);

//		/*****��λ��pid�����ٶȻ���,ʵ������ʱע�͵�*****/

//		// if (is_motor_en == 1)
//		// {
//		// 	MotorPWM = speed_pid_control();
//		// 	Motor2PWM = speed2_pid_control();
//		// }
//		// MotorOutput(MotorPWM, Motor2PWM);
//		/******/

//		/******��λ������λ���ٶȴ���PIDʱ�ã�ʵ��ʹ��ʱע�͵�******/

//		// if (is_motor_en == 1)
//		// {
//		// Location_Speed_control();
//		// 	MotorPWM = speed_Outval;
//		// 	Motor2PWM = speed2_Outval;
//		// 	MotorOutput(MotorPWM, Motor2PWM);
//		// }
//		/************/

//		if (Line_flag == 1) // ��ֱ��ʱ
//		{
//			// if ((Motor_journey_cm <= (g_fTargetJourney + 25)) && (Motor_journey_cm >= (g_fTargetJourney - 25)))
//			// {
//			// 	stop_count++;		   // stop_count���ܳ���256
//			// 	if (stop_count >= 100) // 100 * 20 = 2s  ����ҲҪ������Ŀ��λ��ͣ��1s  //����ʱ���жϷų��㣬�Ա�ɲ��ͣ��
//			// 	{
//			// 		Line_flag = 0;
//			// 		Stop_Flag = 1; // �����־λ���������ж��Ƿ�ִ����һ�׶�����
//			// 		stop_count = 0;

//			// 		set_motor_disable();
//			// 		set_motor2_disable();
//			// 	}
//			// }
//			// else
//			// {
//			// 	Stop_Flag = 0;
//			// 	stop_count = 0;
//			// }

//			if (is_motor_en == 1) // �����ʹ��״̬�²Ž��п��ƴ���
//			{
//				Location_Speed_control(); // λ�û��ٶȻ�����PID��������ٶȻ������PWMֵ

//				// if (Line_Num == 0) // ÿ�λص�������Ҫ������ʱ�򣬶�������������ۼ�������ȡƽ��ֵ�����Ҳ������ת�������ص����ϵ�Ч��
//				// {
//				// 	long Pulse;

//				// 	Pulse = (g_lMotorPulseSigma + g_lMotor2PulseSigma) / 2;

//				// 	g_lMotorPulseSigma = Pulse; // ������ʱ��������ϸ����������
//				// 	g_lMotor2PulseSigma = Pulse;
//				// }

//				// // ����ǻҶȴ�������Ѳ�߲���
//				// Line_Outval = Line_Num; // lineNum����PWM����װ��ֵһ�����ҲŻ������Ե�Ч��
//				MotorPWM = speed_Outval + Line_Outval;
//				Motor2PWM = speed2_Outval - Line_Outval;

//				MotorOutput(MotorPWM, Motor2PWM);
//			}
//		}

//		// 		if (Spin_start_flag == 1) // ת��ʱ
//		// 		{
//		// 			if (is_motor_en == 1) // �����ʹ��״̬�²Ž��п��ƴ���
//		// 			{
//		// 				Location_Speed_control(); // λ�û��ٶȻ�����PID��������ٶȻ������PWMֵ

//		// 				MotorPWM = speed_Outval;
//		// 				Motor2PWM = speed2_Outval;

//		// 				spin_count++;
//		// 				if (spin_count >= 100) // 20ms����һ��   100*20 = 2s�����ܹ�����ɵ�תʱ��Ϊ���ޣ�Ӧ���Ѿ���ת�����
//		// 				{
//		// 					Spin_start_flag = 0;
//		// 					spin_count = 0;

//		// 					// ת���е����⣬ת��֮��һֱת,��ʱ������������
//		// 					MotorPWM = 0;
//		// 					Motor2PWM = 0;
//		// 				}

//		// 				MotorOutput(MotorPWM, Motor2PWM);
//		// 			}
//		// 		}

//		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
//	}
//}

//void Car_go(int32_t location_cm) // ֱ�ߺ���
//{
//	float Car_location;

//	//	if(location_cm < 0)
//	//	{
//	//		LineNumToggleFlag = 1;
//	//	}
//	//	else LineNumToggleFlag = 0;

//	Motor_journey_cm = 0;
//	Motor2_journey_cm = 0;

//	g_fTargetJourney = location_cm; // ��ֹ��ʱ��PID������

//	// ���Ѳ��Ч�����þͽ�3.142�Ӵ�
//	Car_location = (location_cm / (6.5 * 3.14)) * (30 * 4 * 11); // Car_location ��  location_cm ת��Ϊ��Ӧ��������   g_fTargetJourney = Ҫת����Ȧ * 1Ȧ��������
//	// С��λ��ֱ����һ��������������ۻ��ͺã�ת��ʱ����������ʼһ��λ��ǰֱ�����㡣
//	// �򻬵���һ���ֱ���һ����תλ�ò�һ��զ��,�á�Ѳ�߻����ֲ��ͺã�ת����á�ת�򻷡�

//	set_pid_target(&pid_location, Car_location);
//	set_pid_target(&pid_location2, Car_location);

//	set_motor_enable(); // ʹ�ܵ������PWM���

//	g_lMotorPulseSigma = 0;
//	g_lMotor2PulseSigma = 0;
//}

///******ת�����ʱ�Զ���  Spin_start_flag == 0 �� Spin_succeed_flag == 1  ********/
///*ת������ת90����ת90����ת180���������*/

//void spin_Turn(spin_dir_t zhuanxiang) // ����С�����־�(mm) 175mm  //��ʵת�򻷲�����Ҫ�ܾ�׼��ת���ֱ����ֱ��ʱ��Ѳ�ߺ�����������ͺ�
//{

//	float spin90_val;
//	float Car_Turn_val;

//	Motor_journey_cm = 0;
//	Motor2_journey_cm = 0;

//	spin90_val = 0.25 * 3.1416 * LUN_JU;

//	/****ת���ѭ�߿��Ե�ת��ϵ��**********/
//	if (zhuanxiang == left_90) // openmvʶ����Ҫ����߲�����
//	{
//		Car_Turn_val = (spin90_val / (6.5 * 3.142)) * (56 * 4 * 11);
//		Car_Turn_val = 0.95 * Car_Turn_val; // 90*0.94 = 84.6   //����Ӱ�죬����ת��������趨�Ķࡣֱ����90�Ƚ�������Ѳ�߾�Ѱ��������
//	}
//	else if (zhuanxiang == right_90) // openmvʶ����Ҫ���ұ߲�����
//	{
//		Car_Turn_val = -(spin90_val / (6.5 * 3.142)) * (56 * 4 * 11);
//		Car_Turn_val = 0.98 * Car_Turn_val; // 90*0.96 = 86.4    //����Ӱ�죬����ת��������趨�Ķࡣ ��������Ѳ�߿��ܾ�Ѱ��������
//	}
//	else if (zhuanxiang == back_180)
//	{
//		Car_Turn_val = -(spin90_val / (6.5 * 3.142)) * (56 * 4 * 11);
//		Car_Turn_val = 0.98 * Car_Turn_val; // ͬ��
//		Car_Turn_val = 2 * Car_Turn_val;	// 0.96*180 = 175.5
//	}

//	set_pid_target(&pid_location, -Car_Turn_val);
//	set_pid_target(&pid_location2, Car_Turn_val);

//	g_lMotorPulseSigma = 0;
//	g_lMotor2PulseSigma = 0;

//	set_motor_enable(); // ʹ�ܵ������PWM���
//}

///*********************��PID**********************/
///****�ٶȻ�λ�û�����PID����*****/

///**
// * @brief �ٶȻ�λ�û�����PID����
// * @return
// */
//void Location_Speed_control(void) // ԭ��ת�����ֱ�� �������
//{
//	// mpu_dmp_get_data�������Ӱ�쵽����������Ļ�ȡ��
//	if (is_motor_en == 1) // �����ʹ��״̬�²Ž��п��ƴ���
//	{
//		location_control_count++;
//		if (location_control_count >= 2)
//		{
//			location_control_count = 0;

//			location_Outval = location_pid_control();
//			location2_Outval = location2_pid_control();
//		}

//		set_pid_target(&pid_speed, location_Outval);   // ÿ�ζ�������λ�û���ֵ     //�����ٶȻ�PIDʱȡ��������
//		set_pid_target(&pid_speed2, location2_Outval); // ÿ�ζ�������λ�û���ֵ

//		speed_Outval = speed_pid_control(); // Ҫ�ǵ��ת�򲻷���Ԥ�ڣ�������������ȡ����ֵ
//		speed2_Outval = speed2_pid_control();
//	}
//}

///**
// * @brief ���1λ�û�PID����
// * @return PID������PWM
// */
//float location_pid_control(void)
//{
//	float cont_val = 0.0;
//	int32_t actual_location;

//	actual_location = g_lMotorPulseSigma; // 1Ȧ = 2464������ = 56*11*4  //����λ����Ȧ�����档

//	cont_val = location_pid_realize(&pid_location, actual_location);

//	// ��û�Ӵ���pID֮ǰ��λ�û���cont_val��ӦPWM�� �ĳɴ���PID��λ�û���cont_val��ӦĿ���ٶ�

//	/* Ŀ���ٶ����޴��� */
//	if (cont_val > TARGET_SPEED_MAX)
//	{
//		cont_val = TARGET_SPEED_MAX;
//	}
//	else if (cont_val < -TARGET_SPEED_MAX)
//	{
//		cont_val = -TARGET_SPEED_MAX;
//	}

//	// #if defined(PID_ASSISTANT_EN)
//	// 	set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_location, 1); // ��ͨ�� 1 ����ʵ��ֵ
//	// 																		// BlueSignal_Toggle;  //���Խ���
//	// #endif
//	return cont_val;
//}

///**
// * @brief ���1�ٶȻ�PID����
// * @return PID�������ٶ�
// */
//float speed_pid_control(void)
//{
//	float cont_val = 0.0; // ��ǰ����ֵ
//	int32_t actual_speed;

//	actual_speed = ((float)g_nMotorPulse * 1000.0 * 60.0) / (ENCODER_TOTAL_RESOLUTION * REDUCTION_RATIO * SPEED_PID_PERIOD);

//	cont_val = speed_pid_realize(&pid_speed, actual_speed); // ����PID����

//	// #if defined(PID_ASSISTANT_EN)
//	// 	set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_speed, 1); // ��ͨ��1����ʵ��ֵ
//	// #endif

//	return cont_val;
//}

///**
// * @brief ���2λ�û�PID����
// * @return PID������PWM
// */
//float location2_pid_control(void)
//{
//	float cont_val = 0.0;
//	int32_t actual_location;

//	actual_location = g_lMotor2PulseSigma; // 1Ȧ = 2464������ = 56*11*4  //����λ����Ȧ�����档

//	cont_val = location_pid_realize(&pid_location2, actual_location);

//	// �ĳɴ���PID��λ�û���cont_val��ӦĿ���ٶ�

//	// Ŀ���ٶ��޷�
//	/* Ŀ���ٶ����޴��� */
//	if (cont_val > TARGET_SPEED_MAX)
//	{
//		cont_val = TARGET_SPEED_MAX;
//	}
//	else if (cont_val < -TARGET_SPEED_MAX)
//	{
//		cont_val = -TARGET_SPEED_MAX;
//	}

//	//	  #if defined(PID_ASSISTANT_EN)
//	//    set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_location, 1);                // ��ͨ�� 1 ����ʵ��ֵ
//	//		//set_computer_value(SEND_TARGET_CMD, CURVES_CH1,&TargetSpeed, 1);                // ��ͨ�� 1 ����Ŀ��ֵ�������Ŀ�����ֵ����������ʱ���÷��ͣ������޷�����λ��������
//	//  #endif

//	return cont_val;
//}

///**
// * @brief ���2�ٶȻ�PID����
// * @return PID�������ٶ�
// */
//float speed2_pid_control(void)
//{

//	float cont_val = 0.0; // ��ǰ����ֵ
//	int32_t actual_speed;

//	actual_speed = ((float)g_nMotor2Pulse * 1000.0 * 60.0) / (ENCODER_TOTAL_RESOLUTION * REDUCTION_RATIO * SPEED_PID_PERIOD);

//	cont_val = speed_pid_realize(&pid_speed2, actual_speed); // ���� PID ����

//	// #if defined(PID_ASSISTANT_EN)
//	// 	set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_speed, 1); // ��ͨ�� 1 ����ʵ��ֵ
//	// #else
//	// #endif

//	return cont_val;
//}

///**
// * @brief ����pwm�����ٶȼ�����
// * @param {int} nMotorPwm ���1PWM
// * @param {int} nMotor2Pwm ���2PWM
// * @return
// */
//void MotorOutput(int nMotorPwm, int nMotor2Pwm)
//{
//	if (nMotorPwm >= 0)
//	{
//		set_motor_direction(MOTOR_FWD);
//	}
//	else
//	{
//		nMotorPwm = -nMotorPwm;
//		set_motor_direction(MOTOR_REV);
//	}

//	nMotorPwm = (nMotorPwm > PWM_MAX_PERIOD_COUNT) ? PWM_MAX_PERIOD_COUNT : nMotorPwm; // �ٶ����޴���

//	if (nMotor2Pwm >= 0)
//	{
//		set_motor2_direction(MOTOR_FWD);
//	}
//	else
//	{
//		nMotor2Pwm = -nMotor2Pwm;
//		set_motor2_direction(MOTOR_REV);
//	}
//	nMotor2Pwm = (nMotor2Pwm > PWM_MAX_PERIOD_COUNT) ? PWM_MAX_PERIOD_COUNT : nMotor2Pwm; // �ٶ����޴���

//	set_motor_speed(nMotorPwm, nMotor2Pwm);
//}

///**
// * @brief ���õ���ٶ�
// * @param {uint16_t} v �ٶ�1��ռ�ձȣ�
// * @param {uint16_t} v2 �ٶ�2��ռ�ձȣ�
// * @return
// */
//void set_motor_speed(uint16_t v, uint16_t v2)
//{
//	SET_COMPAER(v);
//	SET2_COMPAER(v2);
//}

///**
// * @brief ���õ��1����
// * @param {motor_dir_t} dir
// * @return {*}
// */
//void set_motor_direction(motor_dir_t dir)
//{
//	if (dir == MOTOR_FWD)
//	{
//		L_IN1(High);
//		L_IN2(Low);
//	}
//	else
//	{
//		L_IN1(Low);
//		L_IN2(High);
//	}
//}

///**
// * @brief ���õ��2����
// * @param {motor_dir_t} dir
// * @return
// */
//void set_motor2_direction(motor_dir_t dir)
//{
//	if (dir == MOTOR_FWD)
//	{
//		R_IN1(High);
//		R_IN2(Low);
//	}
//	else
//	{
//		R_IN1(Low);
//		R_IN2(High);
//	}
//}

///**
// * @brief ʹ�ܵ��
// * @return
// */
//void set_motor_enable(void)
//{
//	is_motor_en = 1;
//	MOTOR_ENABLE();
//}

///**
// * @brief ���õ��
// * @return
// */
//void set_motor_disable(void)
//{
//	is_motor_en = 0;
//	MOTOR_DISABLE();
//}
