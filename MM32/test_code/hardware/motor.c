#include "motor.h"

float M_Kp=0,M_Ki=0,M_Kd=0;
int backmotor_RV=1000,backmotor_LV=1000;

void motor_init(void)
{
	pwm_init(TIM2_PWM_CH4_A3, 17000, backmotor_RV);
	pwm_init(TIM2_PWM_CH2_A1, 17000, backmotor_LV);
	gpio_init(A2,GPO,GPIO_HIGH,GPO_PUSH_PULL);   //dir up
	gpio_init(A0,GPO,GPIO_LOW,GPO_PUSH_PULL);
}


