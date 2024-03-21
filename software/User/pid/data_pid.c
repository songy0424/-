/*
 * @Date: 2023-07-14 13:48:43
 * @LastEditTime: 2023-07-17 17:08:14
 * @Description:PID��ʼ��
 */
#include "data_pid.h"

_pid pid_speed, pid_speed2;
_pid pid_location, pid_location2;

void PID_param_init(void) // λ��ʽPID����
{
	/* λ����س�ʼ������ */
	pid_location.target_val = 0.0;
	pid_location.actual_val = 0.0;
	pid_location.err = 0.0;
	pid_location.err_last = 0.0;
	pid_location.integral = 0.0;

	pid_location.Kp = 0.225;
	pid_location.Ki = 0.0;
	pid_location.Kd = 0.0;

	/* �ٶ���س�ʼ������ */
	pid_speed.target_val = 0.0;
	pid_speed.actual_val = 0.0;
	pid_speed.err = 0.0;
	pid_speed.err_last = 0.0;
	pid_speed.integral = 0.0;

	pid_speed.Kp = 2.6;
	pid_speed.Ki = 0.787;
	pid_speed.Kd = 0.25;

	/* λ����س�ʼ������ */
	pid_location2.target_val = 0.0;
	pid_location2.actual_val = 0.0;
	pid_location2.err = 0.0;
	pid_location2.err_last = 0.0;
	pid_location2.integral = 0.0;

	pid_location2.Kp = 0.225;
	pid_location2.Ki = 0.0;
	pid_location2.Kd = 0.0;

	/* �ٶ���س�ʼ������ */
	pid_speed2.target_val = 0.0;
	pid_speed2.actual_val = 0.0;
	pid_speed2.err = 0.0;
	pid_speed2.err_last = 0.0;
	pid_speed2.integral = 0.0;

	pid_speed2.Kp = 2.6;
	pid_speed2.Ki = 0.787;
	pid_speed2.Kd = 0.25;
}

/**
 * @brief ����Ŀ��ֵ
 * @param {_pid} *pid
 * @param {float} temp_val Ŀ��ֵ
 * @return
 */
void set_pid_target(_pid *pid, float temp_val)
{
	pid->target_val = temp_val; // ?��???��?��????����??
}

/**
 * @brief ��ȡĿ��ֵ
 * @param {_pid} *pid
 * @return Ŀ��ֵ
 */
float get_pid_target(_pid *pid)
{
	return pid->target_val; // ?��???��?��????����??
}
/**
 * @brief ����ϵ��
 * @param {_pid} *pid
 * @param {float} p
 * @param {float} i
 * @param {float} d
 * @return {*}
 */
void set_p_i_d(_pid *pid, float p, float i, float d)
{
	pid->Kp = p;
	pid->Ki = i;
	pid->Kd = d;
}

/**
 * @brief λ��PID�㷨ʵ��
 * @param {_pid} *pid
 * @param {float} actual_val ʵ��ֵ
 * @return ���PID������ֵ
 */
float location_pid_realize(_pid *pid, float actual_val) // ?????��????Kp??????????
{
	/*����ƫ��*/
	pid->err = pid->target_val - actual_val;

	//    /* �趨�ջ����� */   //�⻷�������Բ�Ҫ
	//    if((pid->err >= -0.1) && (pid->err <= 0.1))
	//    {
	//      pid->err = 0;
	//      pid->integral = 0;
	//    }

	/*����ۻ�*/
	pid->integral += pid->err;

	/*PID�㷨ʵ��*/
	pid->actual_val = pid->Kp * pid->err + pid->Ki * pid->integral + pid->Kd * (pid->err - pid->err_last);

	/*����*/
	pid->err_last = pid->err;

	/*���ص�ǰʵ��ֵ*/
	return pid->actual_val;
}

/**
 * @brief �ٶ�PID�㷨ʵ��
 * @param {_pid} *pid
 * @param {float} actual_val ʵ��ֵ
 * @return ���PID������ֵ
 */
float speed_pid_realize(_pid *pid, float actual_val)
{
	/*�������*/
	pid->err = pid->target_val - actual_val;

	if ((pid->err < 0.5f) && (pid->err > -0.5f)) // ��������������ٶ�ƫ������1���ӣ�������ƫ���Ȧ
	{
		pid->err = 0.0f;
	}

	pid->integral += pid->err; // ����ۻ�

	/*�����޷�*/
	if (pid->integral >= 1000)
	{
		pid->integral = 1000;
	}
	else if (pid->integral < -1000)
	{
		pid->integral = -1000;
	}

	/*PID�㷨ʵ��*/
	pid->actual_val = pid->Kp * pid->err + pid->Ki * pid->integral + pid->Kd * (pid->err - pid->err_last);

	/*����*/
	pid->err_last = pid->err;

	/*���ص�ǰʵ��ֵ*/
	return pid->actual_val;
}
