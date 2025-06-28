//#include "mm32_device.h"                // Device header
#include <stdint.h>
#include "menu.h"

#define height 7  //屏幕一页有几行-1
#define key_enter gpio_get_level(D5)        //进入键由d5电平变化反应   高到低
#define key_return gpio_get_level(D1)        //进入键由d5电平变化反应
#define key_down gpio_get_level(D2)        //进入键由d5电平变化反应
#define key_up gpio_get_level(D3)        //进入键由d5电平变化反应
#define key_add gpio_get_level(D4)        //进入键由d5电平变化反应
#define key_sub gpio_get_level(D6)        //进入键由d5电平变化反应

int16_t page=1,arrow=0;   //控制菜单变量
int16_t page_last;//

float I_Kp =0,I_Kd = 0;

typedef struct{
	uint16 menu_open;
	
}key;

key fg = {
	.menu_open = 1
};

void key_action()
{                                  
    if((key_up)==0)
    {
		system_delay_ms(300);
        ips200_clear();
		arrow=arrow-1;
    }
    if((key_down)==0)
    {
        system_delay_ms(300);
        ips200_clear();
		arrow=arrow+1;
    }
	if((arrow<0)) arrow=height;
	else if((arrow>height))arrow=0;
}

//菜单主程序
void menu_main()
{
    if(fg.menu_open==1)       //打开菜单
    {
        switch(page)
        {
            case 1 :Menu_show_1();      break;//第一页
            case 21:Inductance_show();      break;//第一页进入第一个选项
//            case 22:PID_Velocity_Show();     break;
//            case 23:Encode_Show();     break;
//            case 24:Gyro_Show();      break;
//			case 25:State_Show();       break;
//			case 26:Threshold_Show(); break;
//			case 27:yh_and_bz(); break;//tools
//			case 28:Go(); break;
////            case 31:();        break;
//			case 32:Sudu_Huan_PD_deburg();break;
////            default:                    break;
////			case 241:Euler_Angle_Show(); break;//算力不足，舍去
			case 214:AD_All_Show(); break;//page=262 page范围不够
//			case 251:State_Other_Show(); break;
//			case 261:AD_Threshold_Show(); break;
//			case 2141:Inductor_Flag_show(); break;
//			case 2142:AD_E_Show(); break;//All_Inductor_Show
//			case 2143:Nomolization_Show(); break;
//			case 2144:V_Nomolization_Show(); break;
        }
    }
	 if((key_return)==0){
	 fg.menu_open=1;
//	 fg.chujie=0;
//	 fg.xunji=1;	
	 }
}

void Menu_show_1()//1
{
	page_last=page;
    page=1;
    if(page!=page_last)
    {
        arrow=0;
    }
    key_action();
    ips200_show_string(0,arrow,"->");
	ips200_show_string(20,0,"Indc_tracker");//page 21 enter 之后         y值要变化
    ips200_show_string(20,1,"Set_Velocity");	//page 22	
    ips200_show_string(20,2,"Encode_suduhaun");//page 23
	ips200_show_string(20,3,"Gyro_Show"); //page  24
    ips200_show_string(20,4,"Elemens_open");//page 25
	ips200_show_string(20,5,"Threshold_Show");//page 26  
    ips200_show_string(20,6,"Tools");//page 27
	ips200_show_string(20,7,"extra_Can_shu");//page 27
	
    
    if((key_enter)==0)
    {
        system_delay_ms(300);
        ips200_clear();
          switch((arrow)+1)//进入第二页，前面一页的箭头选中选项
		{
			case 1:page=21;arrow=0;break;
			case 2:page=22;arrow=0;break;
			case 3:page=23;arrow=0;break;
			case 4:page=24;arrow=0;break;
			case 5:page=25;arrow=0;break;
			case 6:page=26;arrow=0;break;
			case 7:page=27;arrow=0;break;
			case 8:page=28;arrow=0;break;
		}
 
    }
}

float I_Kp_debrug_val=0.1,I_Kd_debrug_val=0.1;
float I_count1=0,I_count2=0;
void Inductance_show()//21
{	
	key_action();
    ips200_show_string(0,arrow,"->");
	ips200_show_string(20,0,"Go");
	ips200_show_string(20,1,"I_Kp");ips200_show_float(50,1, I_Kp, 5, 2);
	ips200_show_string(20,2,"I_Kd");ips200_show_float(50,2, I_Kd, 5, 2);
//	ips200_show_string(20,3,"AD_All&Scan");//page 214
//	ips200_show_string(20,4,"AD_L");ips200_show_float(70,4,AD_L,4,4);
//	ips200_show_string(20,5,"AD_M");ips200_show_float(70,5,AD_M,4,4);
//	ips200_show_string(20,6,"AD_R");ips200_show_float(70,6,AD_R,4,4);
//	ips200_show_string(20,7,"Cret&S");ips200_show_float(70,7,Correct_Val,4,2);
 
		if((key_enter)== 0)
    {
        system_delay_ms(300);
        ips200_clear();
		
		switch(arrow)
		{
			case 0:ips200_show_string(20,0,"Goodluck");
//						delay_ms(200);
//						Go_Flag_Init();						
				break;
			case 1:I_count1++;break;
			case 2:I_count2++;break;			
//			case 7:fg.sao_miao=0;
			break;
		}
		switch((arrow)+1)//换页         第四行
		{
			case 4:page=214;arrow=0;break;
		}
		 
    }
 
    if((key_return)== 0)
    {
        system_delay_ms(300);
        ips200_clear();
        page=1;
    }
	   if((key_add)==0)
    {
		switch(arrow)
		{
			case 1:I_Kp=I_Kp+I_Kp_debrug_val;break;
			case 2:I_Kd=I_Kd+I_Kd_debrug_val;break;
//			case 3:fg.sao_miao=1;break;
		}
    }
	
    if((key_sub)== 0)
    {
		switch(arrow)
		{
			case 1:I_Kp=I_Kp-I_Kp_debrug_val;break;
			case 2:I_Kd=I_Kd-I_Kd_debrug_val;break;
//			case 3:fg.sao_miao=0;break;
 
		}
    }	
 
				   if(I_count1==0)I_Kp_debrug_val=100;
				   if(I_count1==1)I_Kp_debrug_val=10;
				   if(I_count1==2)I_Kp_debrug_val=1;
				   if(I_count1==3)I_Kp_debrug_val=0.1;
				   if(I_count1==4)I_Kp_debrug_val=0.01;
				   if(I_count1==5)I_Kp_debrug_val=0.001;
				   if(I_count1==6)I_count1=0;
				   if(I_count2==0)I_Kd_debrug_val=100;
				   if(I_count2==1)I_Kd_debrug_val=10;
				   if(I_count2==2)I_Kd_debrug_val=1;
				   if(I_count2==3)I_Kd_debrug_val=0.1;
				   if(I_count2==4)I_Kd_debrug_val=0.01;
				   if(I_count2==5)I_Kd_debrug_val=0.001;
				   if(I_count1==5)I_count2=0;	
}

void AD_All_Show()//page 214
{
	key_action();
	ips200_show_string(0,arrow,"->");	
	ips200_show_string(20,0,"Inductor_Flag_show");
	ips200_show_string(20,1,"AD_Show_All");
	ips200_show_string(20,2,"Nomolization_Show");
	ips200_show_string(20,3,"V_Nomolization_Show");
	
	if((key_enter)== 0)
    {		
        system_delay_ms(300);
        ips200_clear();
				switch((arrow)+1)
		{
			case 1:page=2141;break;//Inductor_Flag_show
			case 2:page=2142;break;//AD_E_Show
			case 3:page=2143;break;//Nomolization_Show
		}
    }
	if((key_return)== 0)
    {
        system_delay_ms(300);
        ips200_clear();
        page=21;
		arrow=0;//page=1;
    }
}

