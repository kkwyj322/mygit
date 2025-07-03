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
		otsuThreshold(mt9v03x_image[0]);
		Set_image_twovalues(threshold);
//		ips200_show_binary_image(0,0,mt9v03x_image_BandW[0],188,120,188,120);
//		ips200_show_gray_image(0,0,mt9v03x_image[0],188,120,180,120,threshold);
		ips200_show_gray_image(0,0,mt9v03x_image_BandW[0],188,120,180,120,0);
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

///*! 
// *  @brief      ��򷨶�ֵ��0.8ms����
// *  @date:   2018-10  
// *  @since      v1.2
// *  *image ��ͼ���ַ
// *  width:  ͼ���
// *  height��ͼ���
// *  @author     ZС��
// */
////活动阈值
//  
//uint8 otsuThreshold(uint8 *image, uint16 width, uint16 height)
//{
//    #define GrayScale 256
//    int pixelCount[GrayScale] = {0};//ÿ���Ҷ�ֵ��ռ���ظ���
//    float pixelPro[GrayScale] = {0};//ÿ���Ҷ�ֵ��ռ�����ر���
//    int i,j;   
//    int Sumpix = width * height;   //�����ص�
//    uint8 threshold = 0;
//    uint8* data = image;  //ָ���������ݵ�ָ��


//    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���  
//    for (i = 0; i < height; i++)
//    {
//        for (j = 0; j < width; j++)
//        {
//            pixelCount[(int)data[i * width + j]]++;  //������ֵ��Ϊ����������±�
//          //   pixelCount[(int)image[i][j]]++;    ������ָ�������
//        }
//    }
//    float u = 0;  
//    for (i = 0; i < GrayScale; i++)
//    {
//        pixelPro[i] = (float)pixelCount[i] / Sumpix;   //����ÿ������������ͼ���еı���  
//        u += i * pixelPro[i];  //��ƽ���Ҷ�
//    }

//      
//    float maxVariance=0.0;  //�����䷽��
//    float w0 = 0, avgValue  = 0;  //w0 ǰ������ ��avgValue ǰ��ƽ���Ҷ�
//    for(int i = 0; i < 256; i++)     //ÿһ��ѭ������һ��������䷽����� (����for����Ϊ1��)
//    {  
//        w0 += pixelPro[i];  //���赱ǰ�Ҷ�iΪ��ֵ, 0~i �Ҷ�������ռ����ͼ��ı�����ǰ������
//        avgValue  += i * pixelPro[i];        
//        
//        float variance = pow((avgValue/w0 - u), 2) * w0 /(1 - w0);    //��䷽��   
//        if(variance > maxVariance) 
//        {  
//            maxVariance = variance;  
//            threshold = i;  
//        }  
//    } 


//    return threshold;
//    
//}

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

//-------------------------------------------------------------------------------------------------------------------
//  @brief      快速大津
//  @return     uint8
//  @since      v1.1
//  Sample usage:   OTSU_Threshold = otsuThreshold(mt9v03x_image_dvp[0]);//大津法阈值
//-------------------------------------------------------------------------------------------------------------------
uint8 otsuThreshold(uint8 *image)   //注意计算阈值的一定要是原图像
{
#define GrayScale 256
    int Pixel_Max=0;
    int Pixel_Min=255;
    uint16 width = MT9V03X_W;
    uint16 height = MT9V03X_H;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j, pixelSum = width * height/4;
    uint8 threshold = 0;
	uint8 last_threshold = 130;
    uint8* data = image;  //指向像素数据的指针
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    uint32 gray_sum=0;
    //统计灰度级中每个像素在整幅图像中的个数
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j+=2)
        {
            pixelCount[(int)data[i * width + j]]++;  //将当前的点的像素值作为计数数组的下标
            gray_sum+=(int)data[i * width + j];       //灰度值总和
            if(data[i * width + j]>Pixel_Max)   Pixel_Max=data[i * width + j];
            if(data[i * width + j]<Pixel_Min)   Pixel_Min=data[i * width + j];
        }
    }

    //计算每个像素值的点在整幅图像中的比例

    for (i = Pixel_Min; i < Pixel_Max; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;

    }

    //遍历灰度级[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;

    w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
    for (j = Pixel_Min; j < Pixel_Max; j++)
    {

        w0 += pixelPro[j];  //背景部分每个灰度值的像素点所占比例之和   即背景部分的比例
        u0tmp += j * pixelPro[j];  //背景部分 每个灰度值的点的比例 *灰度值

        w1=1-w0;
        u1tmp=gray_sum/pixelSum-u0tmp;

        u0 = u0tmp / w0;              //背景平均灰度
        u1 = u1tmp / w1;              //前景平均灰度
        u = u0tmp + u1tmp;            //全局平均灰度
        deltaTmp = (float)(w0 *w1* (u0 - u1)* (u0 - u1)) ;
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = j;
        }
        if (deltaTmp < deltaMax)
        {
            break;
        }

    }

    if(threshold>90 && threshold<130)
        last_threshold = threshold;
    else
        threshold = last_threshold;

    return threshold;
}


////-------------------------------------------------------------------------------------------------------------------
////  @brief      图像压缩
////  @return     void
////  @since      v2.0
////  Sample usage:   void compressimage();
////-------------------------------------------------------------------------------------------------------------------
//#define IMAGE_H    50//图像高度
//#define IMAGE_W    90//图像宽度
//uint8 Image_use_zip[IMAGE_H][IMAGE_W];
//void compressimage(void)
//{
//  int i, j, row, line;
//  const float div_h = MT9V03X_H / IMAGE_H, div_w = MT9V03X_W / IMAGE_W;
//  for (i = 0; i < IMAGE_H; i++)
//  {
//    row = i * div_h + 0.5;
//    for (j = 0; j < IMAGE_W; j++)
//    {
//      line = j * div_w + 0.5;
//      Image_use_zip[i][j] = mt9v03x_image[row][line];
//    }
//  }
//}


////-------------------------------------------------------------------------------------------------------------------
////  @brief      Soble固定阈值
////  @return     void
////  @since      v1.2
////  Sample usage:   sobel(Image_use_zip, Image_use, 60);
////-------------------------------------------------------------------------------------------------------------------
//void sobel (uint8 imageIn[IMAGE_H][IMAGE_W], uint8 imageOut[IMAGE_H][IMAGE_W], uint8 Threshold)
//{
//    /** 卷积核大小 */
//    short KERNEL_SIZE = 3;
//    short xStart = KERNEL_SIZE / 2;
//    short xEnd = IMAGE_W - KERNEL_SIZE / 2;
//    short yStart = KERNEL_SIZE / 2;
//    short yEnd = IMAGE_H - KERNEL_SIZE / 2;
//    short i, j;
//    short temp[2];
//    for (i = yStart; i < yEnd; i++)
//    {
//        for (j = xStart; j < xEnd; j++)
//        {
//            /* 计算不同方向梯度幅值  */
//            temp[0] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i - 1][j + 1]     //{{-1, 0, 1},
//            - (short) imageIn[i][j - 1] + (short) imageIn[i][j + 1]                      // {-1, 0, 1},
//            - (short) imageIn[i + 1][j - 1] + (short) imageIn[i + 1][j + 1];             // {-1, 0, 1}};

//            temp[1] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i + 1][j - 1]     //{{-1, -1, -1},
//            - (short) imageIn[i - 1][j] + (short) imageIn[i + 1][j]                      // { 0,  0,  0},
//            - (short) imageIn[i - 1][j + 1] + (short) imageIn[i + 1][j + 1];             // { 1,  1,  1}};

//            temp[0] = abs(temp[0]);
//            temp[1] = abs(temp[1]);

//            /* 找出梯度幅值最大值  */
//            if (temp[0] < temp[1])
//                temp[0] = temp[1];

//            if (temp[0] > Threshold) imageOut[i][j] = 0;
//            else    imageOut[i][j] = 255;
//        }
//    }
//}


////-------------------------------------------------------------------------------------------------------------------
////  @brief      给图像画黑框为八邻域做准备
////  @return     void
////  @since      v1.0
////  Sample usage:   image_draw_rectan(Image_use);
////-------------------------------------------------------------------------------------------------------------------
//void image_draw_rectan(uint8(*image)[IMAGE_W])
//{
//    uint8 i = 0;
//    for (i = 0; i < IMAGE_H; i++)
//    {
//        image[i][0] = 0;
//        image[i][1] = 0;
//        image[i][IMAGE_W - 1] = 0;
//        image[i][IMAGE_W - 2] = 0;
//    }
//    for (i = 0; i < IMAGE_W; i++)
//    {
//        image[0][i] = 0;
//        image[1][i] = 0;
//    }
//}


///*---------------------------------------------------------------
// 【函    数】search_neighborhood
// 【功    能】八邻域找边界
// 【参    数】无
// 【返 回 值】无
// 【注意事项】
// ----------------------------------------------------------------*/
//struct LEFT_EDGE
//{
//    int16 row;  //行坐标
//    int16 col;  //列坐标
//    uint8 flag; //存在边界的标志
//};
//struct RIGHT_EDGE
//{
//    int16 row;  //行坐标
//    int16 col;  //列坐标
//    uint8 flag; //存在边界的标志
//};

//struct LEFT_EDGE  L_edge[140];     //左边界结构体
//struct RIGHT_EDGE R_edge[140];    //右边界结构体
//uint8 L_edge_count=0, R_edge_count = 0;                     //左右边点的个数
//uint8 dire_left,dire_right;                                 //记录上一个点的相对位置
//uint8 L_search_amount = 140, R_search_amount = 140;  //左右边界搜点时最多允许的点
//uint8 Boundary_search_end = 0; //从哪行开始八零与
//void search_neighborhood(uint8 image_use[MT9V03X_H][MT9V03X_W])
//{
//    L_edge_count = 0;//左边点个数清0
//    R_edge_count = 0;//右边点个数清0
//	
//	uint8 BLACK = 0;
//	uint8 WHITE = 255;

//    if(left_findflag)//如果左边界点存在并找到,则开始爬线
//    {
//        //变量声明
//        L_edge[0].row = L_start_y;
//        L_edge[0].col = L_start_x;
//        L_edge[0].flag = 1;
//        int16 curr_row = L_start_y;//初始化行坐标
//        int16 curr_col = L_start_x;//初始化列坐标
//        dire_left = 0; //初始化上个边界点的来向
//        //开始搜线，最多取150个点，不会往下搜，共7个方位
//        for(int i = 1;i < L_search_amount; i++)    //最多搜索150个点
//        {
//            ////越界退出 行越界和列越界（向上向下向左向右）
//            if(curr_row+1 < Boundary_search_end || curr_row>IMAGE_H-1)  break;
//            //搜线过程
//            if(dire_left != 2&&image_use[curr_row-1][curr_col-1]==BLACK&&image_use[curr_row-1][curr_col]==WHITE)   //左上黑，2，右边白
//            {
//                curr_row = curr_row -1;
//                curr_col = curr_col -1;
//                L_edge_count = L_edge_count +1;
//                dire_left = 7;
//                L_edge[i].row = curr_row;
//                L_edge[i].col = curr_col;
//                L_edge[i].flag = 1;
//            }
//            else if(dire_left!=3&&image_use[curr_row-1][curr_col+1]==BLACK&&image_use[curr_row][curr_col+1]==WHITE)    //右上黑，3，下边白
//            {
//                curr_row = curr_row -1;
//                curr_col = curr_col + 1;
//                L_edge_count = L_edge_count + 1;
//                dire_left = 6;
//                L_edge[i].row = curr_row;
//                L_edge[i].col = curr_col;
//                L_edge[i].flag = 1;
//            }
//            else if(image_use[curr_row-1][curr_col]==BLACK&&image_use[curr_row-1][curr_col+1]==WHITE)                  //正上黑，1，右白
//            {
//                curr_row = curr_row - 1;
//                L_edge_count = L_edge_count + 1;
//                dire_left = 0;
//                L_edge[i].row = curr_row;
//                L_edge[i].col = curr_col;
//                L_edge[i].flag = 1;
//            }
//            else if(dire_left!=5&&image_use[curr_row][curr_col-1]==BLACK&&image_use[curr_row-1][curr_col-1]==WHITE)     //正左黑，5，上白
//            {
//                curr_col = curr_col - 1;
//                L_edge_count = L_edge_count +1;
//                dire_left = 4;
//                L_edge[i].row = curr_row;
//                L_edge[i].col = curr_col;
//                L_edge[i].flag = 1;
//            }
//            else if(dire_left!=4&&image_use[curr_row][curr_col+1]==BLACK&&image_use[curr_row+1][curr_col+1]==WHITE)  //正右黑，4，下白
//            {
//                curr_col = curr_col + 1;
//                L_edge_count = L_edge_count +1;
//                dire_left = 5;
//                L_edge[i].row = curr_row;
//                L_edge[i].col = curr_col;
//                L_edge[i].flag = 1;
//            }
//            else if(dire_left!=6&&image_use[curr_row+1][curr_col-1]==BLACK&&image_use[curr_row][curr_col-1]==WHITE)    //左下黑，6，上白
//            {
//                curr_row = curr_row + 1;
//                curr_col = curr_col -1;
//                L_edge_count = L_edge_count +1;
//                dire_left = 3;
//                L_edge[i].row = curr_row;
//                L_edge[i].col = curr_col;
//                L_edge[i].flag = 1;
//            }
//            else if(dire_left!=7&&image_use[curr_row+1][curr_col+1]==BLACK&&image_use[curr_row+1][curr_col]==WHITE)    //右下黑，7，左白
//            {
//                curr_row = curr_row + 1;
//                curr_col = curr_col + 1;
//                L_edge_count = L_edge_count +1;
//                dire_left = 2;
//                L_edge[i].row = curr_row;
//                L_edge[i].col = curr_col;
//                L_edge[i].flag = 1;
//            }
//            else
//                break;
//        }
//    }

//    if(right_findflag)//如果右边界存在并搜到
//             {
//                 R_edge[0].row = R_start_y;
//                 R_edge[0].col = R_start_x;
//                 R_edge[0].flag = 1;
//                 int16 curr_row = R_start_y;
//                 int16 curr_col = R_start_x;
//                 dire_right = 0;
//                 for(int i = 1;i<R_search_amount;i++)
//                 {
//		////越界退出 行越界和列越界（向上向下向左向右）
//                     if(curr_row < Boundary_search_end || curr_row>IMAGE_H-1||curr_row+1<Boundary_search_end)  break;
//                     //爬线过程
//                     if(curr_col<IMAGE_W&&dire_right!=3&&image_use[curr_row-1][curr_col+1]==BLACK&&image_use[curr_row-1][curr_col]==WHITE)    //右上黑，3，左白
//                     {
//                         curr_row = curr_row - 1;
//                         curr_col = curr_col + 1;
//                         R_edge_count = R_edge_count + 1;
//                         dire_right = 6;
//                         R_edge[i].row = curr_row;
//                         R_edge[i].col = curr_col;
//                         R_edge[i].flag = 1;
//                     }
//                     else if(dire_right!=2&&image_use[curr_row-1][curr_col-1]==BLACK&&image_use[curr_row][curr_col-1]==WHITE) //左上黑，2，下白
//                     {
//                         curr_row = curr_row-1;
//                         curr_col = curr_col-1;
//                         R_edge_count = R_edge_count + 1;
//                         dire_right = 7;
//                         R_edge[i].row = curr_row;
//                         R_edge[i].col = curr_col;
//                         R_edge[i].flag = 1;
//                     }
//                     else if(image_use[curr_row-1][curr_col]==BLACK&&image_use[curr_row-1][curr_col-1]==WHITE)                  //正上黑，1，左白
//                     {
//                         curr_row = curr_row - 1;
//                         R_edge_count = R_edge_count + 1;
//                         dire_right = 0;
//                         R_edge[i].row = curr_row;
//                         R_edge[i].col = curr_col;
//                         R_edge[i].flag = 1;
//                     }
//                     else if(dire_right!=4&&image_use[curr_row][curr_col+1]==BLACK&&image_use[curr_row-1][curr_col+1]==WHITE)   //正右黑，4，上白
//                     {
//                         curr_col = curr_col + 1;
//                         R_edge_count = R_edge_count + 1;
//                         dire_right = 5;
//                         R_edge[i].row = curr_row;
//                         R_edge[i].col = curr_col;
//                         R_edge[i].flag = 1;
//                     }
//                     else if(dire_right!=5&&image_use[curr_row][curr_col-1]==BLACK&&image_use[curr_row+1][curr_col-1]==WHITE)   //正左黑，5，下白
//                     {
//                         curr_col = curr_col-1;
//                         R_edge_count = R_edge_count + 1;
//                         dire_right = 4;
//                         R_edge[i].row = curr_row;
//                         R_edge[i].col = curr_col;
//                         R_edge[i].flag = 1;
//                     }


//                     else if(dire_right!=6&&image_use[curr_row+1][curr_col-1]==BLACK&&image_use[curr_row+1][curr_col]==WHITE)   //左下黑，6，右白
//                     {
//                         curr_row = curr_row + 1;
//                         curr_col = curr_col - 1;
//                         R_edge_count = R_edge_count + 1;
//                         dire_right = 3;
//                         R_edge[i].row = curr_row;
//                         R_edge[i].col = curr_col;
//                         R_edge[i].flag = 1;
//                     }
//                     else if(dire_right!=7&&image_use[curr_row+1][curr_col+1]==BLACK&&image_use[curr_row][curr_col+1]==WHITE)   //右下黑，7，上白
//                     {
//                         curr_row = curr_row + 1;
//                         curr_col = curr_col + 1;
//                         R_edge_count = R_edge_count + 1;
//                         dire_right = 2;
//                         R_edge[i].row = curr_row;
//                         R_edge[i].col = curr_col;
//                         R_edge[i].flag = 1;
//                     }
//                     else
//                         break;
//                 }
//             }
//}

///*---------------------------------------------------------------
// 【函    数】clear_find_point
// 【功    能】八邻域边界初始化
// 【参    数】无
// 【返 回 值】
// 【注意事项】
// ----------------------------------------------------------------*/
//void clear_find_point(void)
//{
//    for(int i = 0;i<L_edge_count;i++)
//    {
//        L_edge[i].row = 0;
//        L_edge[i].col = 0;
//        L_edge[i].flag = 0;
//    }
//    for(int i = 0;i<R_edge_count;i++)
//    {
//        R_edge[i].row = 0;
//        R_edge[i].col = 0;
//        R_edge[i].flag = 0;
//    }
//}
///*---------------------------------------------------------------
// 【函    数】calc_diff
// 【功    能】差比和
// 【参    数】无
// 【返 回 值】
// 【注意事项】约放大128倍
// ----------------------------------------------------------------*/
//int16 calc_diff(int16 x, int16 y)
//{
//    return ( ((x-y)<<7)/(x+y) );
//}

////-------------------------------------------------------------------------------------------------------------------
////  @brief      限幅
////  @param      x               被限幅的数据
////  @param      y               限幅范围(数据会被限制在-y至+y之间)
////  @return     float           限幅之后的数据
////  Sample usage:               float dat = limit(500,300);//数据被限制在-300至+300之间  因此返回的结果是300
////-------------------------------------------------------------------------------------------------------------------
//float limit(float x, int32 y)
//{
//    if(x>y)             return (float)y;
//    else if(x<-y)       return (float)(-y);
//    else                return x;
//}

///*---------------------------------------------------------------
// 【函    数】get_turning_point
// 【功    能】拐点检测
// 【参    数】无
// 【返 回 值】
// 【注意事项】
// ----------------------------------------------------------------*/
//int16 L_corner_flag = 0;//左拐点存在标志
//int16 L_corner_row = 0;//左拐点所在行
//int16 L_corner_col = 0;//左拐点所在列
//int L_corner_angle = 0;//左拐点角度
//int16 R_corner_flag = 0;//右拐点存在标志
//int16 R_corner_row = 0;//右拐点所在行
//int16 R_corner_col = 0;//右拐点所在列
//int R_corner_angle = 0;//右拐点角度
//uint8 enable_L_corner=1,enable_R_corner=1;
//void get_turning_point(void)
//{
//    L_corner_flag = 0;// 初始化变量
//    L_corner_row = 0;
//    L_corner_col = 0;
//    L_corner_angle = 0;
//    if(enable_L_corner) //如果使能搜索左拐点
//    {
//        if(L_edge_count > 9&&L_start_y>=IMAGE_H/2&&left_lose<=IMAGE_H/2)
//        {
//            for(int i = 0; i<L_edge_count-9;i++)
//            {
//                if(L_edge[i+8].row>5)
//                {
//                    if((L_edge[i].col - L_edge[i + 4].col) * (L_edge[i + 8].col - L_edge[i + 4].col) +
//                       (L_edge[i].row - L_edge[i + 4].row) * (L_edge[i + 8].row - L_edge[i + 4].row) >= 0) //初步确认为锐角或者直角 向量法
//                    {
//                        L_corner_angle = Get_angle(L_edge[i].col, L_edge[i].row, L_edge[i + 4].col, L_edge[i + 4].row, L_edge[i + 8].col, L_edge[i + 8].row); //求角度
//                        if(L_edge[i+4].col>L_edge[i+8].col&&L_corner_angle>=28&&L_corner_angle<=110)
//                        {
//                            L_corner_flag = 1;
//                            L_corner_row = L_edge[i+4].row;
//                            L_corner_col = L_edge[i+4].col;
//                            break;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    R_corner_flag = 0;//初始化变量
//    R_corner_row = 0;
//    R_corner_col = 0;
//    R_corner_angle = 0;
//    if(enable_R_corner)    //如果使能搜索右拐点
//    {
//        if(R_edge_count > 9&&R_start_y>=IMAGE_H/2&&right_lose<=IMAGE_H/2)
//        {
//            for(int i = 0; i<R_edge_count-9;i++)
//            {
//                if(R_edge[i+8].row>5)
//                {
//                    if((R_edge[i].col - R_edge[i + 4].col) * (R_edge[i + 8].col - R_edge[i + 4].col) +
//                    (R_edge[i].row - R_edge[i + 4].row) * (R_edge[i + 8].row - R_edge[i + 4].row) >= 0) //初步确认为锐角或者直角 向量法
//                    {
//                        R_corner_angle = Get_angle(R_edge[i].col, R_edge[i].row, R_edge[i + 4].col, R_edge[i + 4].row, R_edge[i + 8].col, R_edge[i + 8].row); //求角度
//                        if(R_edge[i+8].col>R_edge[i+4].col&&R_corner_angle>=28&&R_corner_angle<=110)
//                        {
//                            R_corner_flag = 1;
//                            R_corner_row = R_edge[i+4].row;
//                            R_corner_col = R_edge[i+4].col;
//                            break;
//                        }
//                    }
//                }
//            }
//        }
//    }
//}


////-------------------------------------------------------------------------------------------------------------------
////  @brief      逆透视知三点求形成的角度(以左上角为原点形成坐标系)
////  @param      Ax，Ay      下边点
////  @param      Bx，By      要求角度的一点
////  @param      Cx，Cy      上边点
////  @return
////  @since      v1.0
////  Sample usage:
////-------------------------------------------------------------------------------------------------------------------
//float hd[3][3] ={{-0.436025, 0.000000, 21.365217}, {0.424457, 0.487500, -22.048370}, {0.018944, -0.000000, 0.071739}};
////x=[18,18,69,69]  % 依次为A、B、D、C在摄像头获取的照片中的的纵坐标
////y=[70,121,70,121] % 依次为A、B、D、C在摄像头获取的照片中的的横坐标
//float Get_angle(float Ax, float Ay, float Bx, float By, float Cx, float Cy)
//{

//    float BA = 0.00;//向量BA的模
//    float BC = 0.00;
//    float SBA_BC = 0.00;//向量点乘的值
//    float angle = 0.00;

//    float AX=((hd[0][0] * Ax + hd[0][1] * Ay + hd[0][2])/(hd[2][0] * Ax + hd[2][1] * Ay + hd[2][2]));
//    float AY=((hd[1][0] * Ax + hd[1][1] * Ay + hd[1][2])/(hd[2][0] * Ax + hd[2][1] * Ay + hd[2][2]));
//    float BX=((hd[0][0] * Bx + hd[0][1] * By + hd[0][2])/(hd[2][0] * Bx + hd[2][1] * By + hd[2][2]));
//    float BY=((hd[1][0] * Bx + hd[1][1] * By + hd[1][2])/(hd[2][0] * Bx + hd[2][1] * By + hd[2][2]));
//    float CX=((hd[0][0] * Cx + hd[0][1] * Cy + hd[0][2])/(hd[2][0] * Cx + hd[2][1] * Cy + hd[2][2]));
//    float CY=((hd[1][0] * Cx + hd[1][1] * Cy + hd[1][2])/(hd[2][0] * Cx + hd[2][1] * Cy + hd[2][2]));

//    BA = sqrt((AX-BX)*(AX-BX)+(AY-BY)*(AY-BY));
//    BC = sqrt((CX-BX)*(CX-BX)+(CY-BY)*(CY-BY));

//    SBA_BC = (AX-BX)*(CX-BX)+(AY-BY)*(CY-BY);

//    angle =  acos(SBA_BC*1.00/(BA*BC));

//    return angle*57.3;
//}



