#include "servo.h"
#include "zf_driver_pwm.h"

float D_Kp=0,D_Kd=0,D_KI=0;


void servo_init(void)
{
	pwm_init(TIM2_PWM_CH1_A15,50,2000);
}

