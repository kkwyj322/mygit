#ifndef _menu_h_
#define _menu_h_

#include "zf_driver_delay.h"
#include "zf_device_ips200.h"
#include "zf_driver_gpio.h"
#include "encoder.h"
#include "motor.h"

extern int backmotor_RV,backmotor_LV;

void key_action();
void menu_main();
void Menu_show_1();
void duoji_show();
void AD_All_Show();
void encoder_data_show(void);

#endif
