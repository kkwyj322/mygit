#ifndef _pid_h_
#define _pid_h_

#include "zf_driver_pwm.h"
#include "zf_common_headfile.h"
#include "zf_driver_pwm.h"

typedef struct
{
	float Target_Val;     //目标值
	float Error;          //第k次偏差
	float LastError;      //k-1
	float PrevError;      //k-2
	float Kp,Ki,Kd;       //
	float Integral;       //积分值
	float Output_Val;     //输出值
}PID;

void PID_Init(void);


#endif
