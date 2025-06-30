#include "image.h"

uint8    mt9v03x_image_BandW[MT9V03X_H][MT9V03X_W];
uint8 threshold = 200;  //固定阈值

//显示函数
void image_control(void)
{
	mt9v03x_init();
	if(mt9v03x_finish_flag == 1)
	{
		ips200_show_gray_image(0,0,mt9v03x_image[0],188,120,180,120,threshold);
	}
}



//------------------摄像头参数--------------//

//uint8 image_threshold = 46;  //图像阈值
//uint8 dis_image[60][80];

//大津法二值化//

/*! 
 *  @brief      大津法二值化0.8ms程序
 *  @date:   2018-10  
 *  @since      v1.2
 *  *image ：图像地址
 *  width:  图像宽
 *  height：图像高
 *  @author     Z小旋
 */
//宽高可以变
  
uint8 otsuThreshold(uint8 *image, uint16 width, uint16 height)
{
    #define GrayScale 256
    int pixelCount[GrayScale] = {0};//每个灰度值所占像素个数
    float pixelPro[GrayScale] = {0};//每个灰度值所占总像素比例
    int i,j;   
    int Sumpix = width * height;   //总像素点
    uint8 threshold = 0;
    uint8* data = image;  //指向像素数据的指针


    //统计灰度级中每个像素在整幅图像中的个数  
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            pixelCount[(int)data[i * width + j]]++;  //将像素值作为计数数组的下标
          //   pixelCount[(int)image[i][j]]++;    若不用指针用这个
        }
    }
    float u = 0;  
    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / Sumpix;   //计算每个像素在整幅图像中的比例  
        u += i * pixelPro[i];  //总平均灰度
    }

      
    float maxVariance=0.0;  //最大类间方差
    float w0 = 0, avgValue  = 0;  //w0 前景比例 ，avgValue 前景平均灰度
    for(int i = 0; i < 256; i++)     //每一次循环都是一次完整类间方差计算 (两个for叠加为1个)
    {  
        w0 += pixelPro[i];  //假设当前灰度i为阈值, 0~i 灰度像素所占整幅图像的比例即前景比例
        avgValue  += i * pixelPro[i];        
        
        float variance = pow((avgValue/w0 - u), 2) * w0 /(1 - w0);    //类间方差   
        if(variance > maxVariance) 
        {  
            maxVariance = variance;  
            threshold = i;  
        }  
    } 


    return threshold;
    
}

//void find_mid_Line(void)
//{
//	for(uint8 i =MT9V03X_H - 1;i>0;i--)
//	{
//		draw_points(left_line_list[i],i,BLUE);
//	}
//}

//void draw_points(uint8 x,uint8 y, uint16 color)
//{
//	ifu



//void Set_image_twovalues(uint8 value)
//{
//	uint8 temp_value; 
//	for(uint8 i=0;i<MT9V03X_H;i++)
//	{
//		for(uint8 j =0;j<MT9V03X_W;j++)
//		{
//			temp_value = mt9v03x_image[i][j];
//			if(temp_value < value)
//			{
//				mt9v03x_image_BandW[i][j] = 0;
//			}
//			else{
//				mt9v03x_image_BandW[i][j] = 255;
//			}
//		}
//	}
//}
