#ifndef _image_h_
#define _image_h_

#include "zf_driver_pwm.h"
#include "zf_device_mt9v03x.h"
#include "zf_device_ips200.h"
#include "zf_common_font.h"
#include <math.h>

extern uint8    mt9v03x_image_BandW[MT9V03X_H][MT9V03X_W];
extern uint8 mid_line;

void image_control(void);
void draw_points(uint8 x,uint8 y, uint16 color);
void Set_image_twovalues(uint8 value);
void find_fenjieline(uint8 index[MT9V03X_H][MT9V03X_W]);
void find_mid_Line_draw(void);
void find_mid_line_weight(void);
uint8 otsuThreshold(uint8 *image);


#endif
