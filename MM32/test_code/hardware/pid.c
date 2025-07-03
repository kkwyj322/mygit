#include "pid.h"

int Max_Pid_Value=10000;
PID PosionPID,L_AddPID,R_AddPID;

void PID_Init(void)
{
	PosionPID.Target_Val=0;
	PosionPID.Output_Val=0.0;
	PosionPID.Error=0.0;
	PosionPID.LastError=0.0;
	PosionPID.Integral=0.0;
	PosionPID.Kp=0;
	PosionPID.Ki=0;
	PosionPID.Kd=0;
	
	L_AddPID.Target_Val=0;
	L_AddPID.Output_Val=0.0;
	L_AddPID.Error=0.0;
	L_AddPID.LastError=0.0;
	L_AddPID.Integral=0.0;
	L_AddPID.Kp=0;
	L_AddPID.Ki=0;
	L_AddPID.Kd=0;
	
	R_AddPID.Target_Val=0;
	R_AddPID.Output_Val=0.0;
	R_AddPID.Error=0.0;
	R_AddPID.LastError=0.0;
	R_AddPID.Integral=0.0;
	R_AddPID.Kp=0;
	R_AddPID.Ki=0;
	R_AddPID.Kd=0;
}


float AddPID_Realize(PID *pid, float Actual_val)
{
	pid->Error = pid->Target_Val - Actual_val;
	pid->Output_Val += pid->Kp * (pid->Error - pid->LastError) +
	                  pid->Ki * pid->Error +
	                  pid->Kd * (pid->Error-2*pid->LastError+pid->PrevError);
	pid->PrevError = pid->LastError;
	pid->LastError = pid->Error;
	if(pid->Output_Val > Max_Pid_Value)
	{
		pid->Output_Val=Max_Pid_Value;
		return Max_Pid_Value;
	}
	else if(pid->Output_Val < (-1)*Max_Pid_Value)
	{
		pid->Output_Val = (-1)*Max_Pid_Value;
		return (-1)*Max_Pid_Value;
	}
	else{
		return pid->Output_Val;
	}
}

float PosionPID_realize(PID *pid,float Actual_val)
{
	pid->Error = pid->Target_Val - Actual_val;
	pid->Integral += pid->Error;   //积分项
	pid->Output_Val = pid->Kp * pid->Error +
	                  pid->Ki * pid->Integral +
	                  pid->Kd * (pid->Error-pid->LastError);
	pid->LastError = pid->Error;
	if(pid->Output_Val > Max_Pid_Value)
	{
		pid->Output_Val=Max_Pid_Value;
		return Max_Pid_Value;
	}
	else if(pid->Output_Val < (-1)*Max_Pid_Value)
	{
		pid->Output_Val = (-1)*Max_Pid_Value;
		return (-1)*Max_Pid_Value;
	}
	else{
		return pid->Output_Val;
	}
}

//void TIM5_IRQHandler (void)
//{
//    // 此处编写用户代码
//	encoder_data_dir3_right=encoder_get_count(TIM3_ENCODER);
//	encoder_clear_count(TIM3_ENCODER);
//	encoder_data_dir4_left=encoder_get_count(TIM4_ENCODER);
//	encoder_clear_count(TIM4_ENCODER);
//    // 此处编写用户代码
//    TIM5->SR &= ~TIM5->SR;                                                      // 清空中断状态
//}



