#include "servo.h"
#include "zf_driver_pwm.h"

extern float I_Kp,I_Kd,I_KI;


void servo_init(void)
{
	pwm_init(TIM5_PWM_CH1_A0,50,2000);
}

