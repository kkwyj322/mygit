#include "image.h"

uint8    mt9v03x_image_BandW[MT9V03X_H][MT9V03X_W];
uint8 threshold = 200;  //固定阈值
uint8 left_line_list[MT9V03X_H];
uint8 right_line_list[MT9V03X_H];
uint8 mid_line_list[MT9V03X_H];
uint8 mid_line = 94; //中值

//图像控制
void image_control(void)
{
//	mt9v03x_init();
	if(mt9v03x_finish_flag == 1)
	{
		Set_image_twovalues(200);
//		ips200_show_binary_image(0,0,mt9v03x_image_BandW[0],188,120,188,120);
		ips200_show_gray_image(0,0,mt9v03x_image[0],188,120,180,120,threshold);
//		ips200_show_gray mage(0,0,mt9v03x_image_BandW[0],188,120,180,120,0);
		find_fenjieline(mt9v03x_image_BandW);		
		find_mid_Line_draw();
		find_mid_line_weight();
		ips200_show_int(200,60,mid_line,4);
		mt9v03x_finish_flag = 0;
	}
}

//权重
uint8 mid_weight_list[120] =
{
	1,1,1,1,1,2,2,2,2,2,
    3,3,3,3,3,4,4,4,4,4,
    5,5,5,5,5,5,5,5,5,5,
    7,7,8,8,9,9,10,10,10,10,
    10,10,10,10,10,10,10,10,9,9,
    9,9,8,8,7,7,6,6,5,5,
    4,4,4,4,4,4,4,4,4,4,
    3,3,3,3,3,3,3,3,3,3,
    2,2,2,2,2,2,2,2,2,2,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1
};

void find_mid_line_weight(void)
{
    uint16_t weight_sum = 0;
    int mid_line_error = 0;
    uint8_t mid_diuxian_flag = 0;
    uint16_t weight_midline_sum = 0;

    for (uint8_t i = MT9V03X_H - 1; i > 0; i--)
    {
        if (i == MT9V03X_H - 1)
        {
            weight_midline_sum += mid_line_list[i] * mid_weight_list[i];
            weight_sum += mid_weight_list[i];
        }
        else
        {
            mid_line_error = abs((int)(mid_line_list[i] - mid_line_list[i + 1]));

            if (mid_diuxian_flag == 1)
            {
                continue;
            }
            else if (mid_line_error > 34 && mid_diuxian_flag == 0)
            {
                mid_diuxian_flag = 1;
                continue;
            }
            else
            {
                weight_midline_sum += mid_line_list[i] * mid_weight_list[i];
                weight_sum += mid_weight_list[i];
            }
        }
    }
	
	mid_line = weight_midline_sum / weight_sum;
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
//活动阈值
  
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

void find_mid_Line_draw(void)
{
	for(uint8 i =MT9V03X_H - 1;i>0;i--)
	{
		draw_points(left_line_list[i],i,RGB565_BLUE);
		draw_points(right_line_list[i],i,RGB565_BLUE);
		draw_points(mid_line_list[i],i,RGB565_RED);
	}
}


void find_fenjieline(uint8 index[MT9V03X_H][MT9V03X_W])
{
	uint8 left_point = 1;
	uint8 right_point = MT9V03X_W-1;
	uint8 flag = 0;
	
	left_line_list[0] = 1;
	right_line_list[0] = MT9V03X_W-1;
	mid_line_list[0] = (left_point + right_point)/2;
	
	for(uint8 i = MT9V03X_H - 1;i>0;i--)
	{
		//1/2
		if(index[i][MT9V03X_W/2] == 255)
		{
			for(uint8 j =MT9V03X_W/2-1;j>0;j--)
			{
				if(index[i][j] == 0 && index[i][j+1] == 255)
				{
					left_point = j;
					break;
				}
			}
			for(uint8 j =MT9V03X_W/2+1;j<MT9V03X_W;j++)
			{
				if(index[i][j] == 0 && index[i][j-1] == 255)
				{
					right_point = j;
					break;
				}
			}
		}
		//1/4
		else if(index[i][MT9V03X_W/4] == 255)
		{
			for(uint8 j =MT9V03X_W/4-1;j>0;j--)
			{
				if(index[i][j] == 0 && index[i][j+1] == 255)
				{
					left_point = j;
					break;
				}
			}
			for(uint8 j =MT9V03X_W/4+1;j<MT9V03X_W;j++)
			{
				if(index[i][j] == 0 && index[i][j-1] == 255)
				{
					right_point = j;
					break;
				}
			}
		}
		//3/4
		else if(index[i][MT9V03X_W/4*3] == 255)
		{
			for(uint8 j =MT9V03X_W/4*3-1;j>0;j--)
			{
				if(index[i][j] == 0 && index[i][j+1] == 255)
				{
					left_point = j;
					break;
				}
			}
			for(uint8 j =MT9V03X_W/4*3+1;j<MT9V03X_W;j++)
			{
				if(index[i][j] == 0 && index[i][j-1] == 255)
				{
					right_point = j;
					break;
				}
			}
		}
		else{
			left_point = 1;
			right_point = MT9V03X_W-1;
//			flag = 1;
		}
		left_line_list[i] = left_point;
	    right_line_list[i] = right_point;
	    mid_line_list[i] = (left_point + right_point)/2;
		ips200_show_int(200,120,left_point,4);
//		if(flag == 1)
//		{
//		    for(uint8 j=1;j<MT9V03X_W;j++)
//		    {
//			    if(index[i][j] == 255)
//				{
//					flag =2;
//				}
//			}
//		}
//		if(flag == 1)
//		{
			
	}
}

void draw_points(uint8 x,uint8 y, uint16 color)
{
	//区域限制
	if(x>=MT9V03X_W)
	{
		x=MT9V03X_W-1;
	}
	else if(x<=0)
	{
		x=1;
	}
	if(y>=MT9V03X_H)
	{
		y=MT9V03X_H-1;
	}
	else if(y<=0)
	{
		y=1;
	}
	ips200_draw_point(x,y,color);
	ips200_draw_point(x,y-1,color);
	ips200_draw_point(x,y+1,color);
	ips200_draw_point(x-1,y,color);
	ips200_draw_point(x-1,y-1,color);
	ips200_draw_point(x-1,y+1,color);
	ips200_draw_point(x+1,y-1,color);
	ips200_draw_point(x+1,y,color);
	ips200_draw_point(x+1,y+1,color);
}



void Set_image_twovalues(uint8 value)
{
	uint8 temp_value; 
	for(uint8 i=0;i<MT9V03X_H;i++)
	{
		for(uint8 j =0;j<MT9V03X_W;j++)
		{
			temp_value = mt9v03x_image[i][j];
			if(temp_value < value)
			{
				mt9v03x_image_BandW[i][j] = 0;
			}
			else{
				mt9v03x_image_BandW[i][j] = 255;
			}
		}
	}
}
