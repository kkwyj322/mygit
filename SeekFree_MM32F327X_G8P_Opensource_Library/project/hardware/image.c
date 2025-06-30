#include "image.h"

uint8    mt9v03x_image_BandW[MT9V03X_H][MT9V03X_W];
uint8 threshold = 200;  //�̶���ֵ

//��ʾ����
void image_control(void)
{
	mt9v03x_init();
	if(mt9v03x_finish_flag == 1)
	{
		ips200_show_gray_image(0,0,mt9v03x_image[0],188,120,180,120,threshold);
	}
}



//------------------����ͷ����--------------//

//uint8 image_threshold = 46;  //ͼ����ֵ
//uint8 dis_image[60][80];

//��򷨶�ֵ��//

/*! 
 *  @brief      ��򷨶�ֵ��0.8ms����
 *  @date:   2018-10  
 *  @since      v1.2
 *  *image ��ͼ���ַ
 *  width:  ͼ���
 *  height��ͼ���
 *  @author     ZС��
 */
//��߿��Ա�
  
uint8 otsuThreshold(uint8 *image, uint16 width, uint16 height)
{
    #define GrayScale 256
    int pixelCount[GrayScale] = {0};//ÿ���Ҷ�ֵ��ռ���ظ���
    float pixelPro[GrayScale] = {0};//ÿ���Ҷ�ֵ��ռ�����ر���
    int i,j;   
    int Sumpix = width * height;   //�����ص�
    uint8 threshold = 0;
    uint8* data = image;  //ָ���������ݵ�ָ��


    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���  
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            pixelCount[(int)data[i * width + j]]++;  //������ֵ��Ϊ����������±�
          //   pixelCount[(int)image[i][j]]++;    ������ָ�������
        }
    }
    float u = 0;  
    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / Sumpix;   //����ÿ������������ͼ���еı���  
        u += i * pixelPro[i];  //��ƽ���Ҷ�
    }

      
    float maxVariance=0.0;  //�����䷽��
    float w0 = 0, avgValue  = 0;  //w0 ǰ������ ��avgValue ǰ��ƽ���Ҷ�
    for(int i = 0; i < 256; i++)     //ÿһ��ѭ������һ��������䷽����� (����for����Ϊ1��)
    {  
        w0 += pixelPro[i];  //���赱ǰ�Ҷ�iΪ��ֵ, 0~i �Ҷ�������ռ����ͼ��ı�����ǰ������
        avgValue  += i * pixelPro[i];        
        
        float variance = pow((avgValue/w0 - u), 2) * w0 /(1 - w0);    //��䷽��   
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
