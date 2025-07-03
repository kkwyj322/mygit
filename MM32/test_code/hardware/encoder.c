#include "encoder.h"

int16 encoder_data_dir3_right = 0;
int16 encoder_data_dir4_left = 0;

void encoder_init(void)
{
	encoder_dir_init(TIM3_ENCODER, TIM3_ENCODER_CH1_B4, TIM3_ENCODER_CH2_B5);          // 初始化编码器模块与引脚 带方向增量编码器模式
    encoder_dir_init(TIM4_ENCODER, TIM4_ENCODER_CH1_B6, TIM4_ENCODER_CH2_B7); 
	
	pit_ms_init(TIM5_PIT, 100);
	interrupt_set_priority(TIM5_IRQn, 1);
}


//void pit3_handler (void)
//{
//    encoder_data_dir3_right = encoder_get_count(TIM3_ENCODER);                          // 获取编码器计数

//    encoder_clear_count(TIM3_ENCODER);                                       // 清空编码器计数
//}

//void pit4_handler (void)
//{
//    encoder_data_dir4_left = encoder_get_count(TIM4_ENCODER);                          // 获取编码器计数

//    encoder_clear_count(TIM4_ENCODER);                                       // 清空编码器计数
//}

