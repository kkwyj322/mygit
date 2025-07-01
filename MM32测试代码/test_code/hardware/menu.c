//#include "mm32_device.h"                // Device header
#include <stdint.h>
#include "menu.h"
#include "zf_common_headfile.h"

#define height 10  //é«˜åº¦
#define key_enter key_get_state(KEY_1)       //e2çŸ­æŒ‰
#define key_return key_get_state(KEY_1)        //e2é•¿æŒ‰
#define key_down key_get_state(KEY_2)        //e3çŸ­æŒ‰
#define key_up key_get_state(KEY_2)        //e3é•¿æŒ‰
#define key_add key_get_state(KEY_3)        //e4çŸ­æŒ‰
#define key_sub key_get_state(KEY_4)        //e5çŸ­æŒ‰

int16_t page=1,arrow=0;   //ç¿»é¡µ æ¢è¡Œ
int16_t page_last;//
uint16 ziti = 16;

float I_Kp =0,I_Kd = 0,I_KI = 0;

typedef struct{
	uint16 menu_open;
	
}key;

key fg = {
	.menu_open = 1
};

void key_action()
{                                  
    if((key_up)==KEY_LONG_PRESS)
    {
		system_delay_ms(300);
        ips200_clear();
		arrow=arrow-1;
    }
    if((key_down)==KEY_SHORT_PRESS)
    {
        system_delay_ms(300);
        ips200_clear();
		arrow=arrow+1;
    }
	if((arrow<0)) arrow=height;
	else if((arrow>height))arrow=0;
}

//²Ëµ¥Ö÷³ÌĞò
void menu_main()
{
    if(fg.menu_open==1)       //´ò¿ª²Ëµ¥
    {
        switch(page)
        {
            case 1 :Menu_show_1();      break;//ç¬¬ä¸€é¡µ
            case 21:duoji_show();      break;//ç¬¬ä¸€é¡µç¬¬ä¸€è¡Œè¿›å…¥
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
////			case 241:Euler_Angle_Show(); break;//ËãÁ¦²»×ã£¬ÉáÈ¥
			case 214:AD_All_Show(); break;//page=262 page·¶Î§²»¹»
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
	 ips200_show_int(2,300,arrow,2);
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
    ips200_show_string(0,132+ziti*arrow,"->");
	ips200_show_string(20,132,"duoji");//page 21 enter Ö®ºó         yÖµÒª±ä»¯
    ips200_show_string(20,132+ziti,"houlun");	//page 22	
    ips200_show_string(20,132+ziti*2,"Encode_suduhaun");//page 23
//	ips200_show_string(20,3,"Gyro_Show"); //page  24
//    ips200_show_string(20,4,"Elemens_open");//page 25
//	ips200_show_string(20,5,"Threshold_Show");//page 26  
//    ips200_show_string(20,6,"Tools");//page 27
//	ips200_show_string(20,7,"extra_Can_shu");//page 27
	
    
    if((key_enter)==KEY_SHORT_PRESS)
    {
        system_delay_ms(300);
        ips200_clear();
          switch((arrow)+1)//½øÈëµÚ¶şÒ³£¬Ç°ÃæÒ»Ò³µÄ¼ıÍ·Ñ¡ÖĞÑ¡Ïî
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
void duoji_show()//21
{	
	key_action();
    ips200_show_string(0,132+ziti*arrow,"->");
	ips200_show_string(20,132,"Go");
	ips200_show_string(20,132+ziti,"I_Kp");ips200_show_float(50,132+ziti, I_Kp, 5, 2);
	ips200_show_string(20,132+ziti*2,"I_Kd");ips200_show_float(50,132+ziti*2, I_Kd, 5, 2);
//	ips200_show_string(20,3,"AD_All&Scan");//page 214
//	ips200_show_string(20,4,"AD_L");ips200_show_float(70,4,AD_L,4,4);
//	ips200_show_string(20,5,"AD_M");ips200_show_float(70,5,AD_M,4,4);
//	ips200_show_string(20,6,"AD_R");ips200_show_float(70,6,AD_R,4,4);
//	ips200_show_string(20,7,"Cret&S");ips200_show_float(70,7,Correct_Val,4,2);
 
		if((key_enter)== KEY_SHORT_PRESS)
    {
        system_delay_ms(300);
        ips200_clear();
		
		switch(arrow)
		{
			case 0:ips200_show_string(20,132,"Goodluck");
//						delay_ms(200);
//						Go_Flag_Init();						
				break;
			case 1:I_count1++;break;
			case 2:I_count2++;break;			
//			case 7:fg.sao_miao=0;
			break;
		}
		switch((arrow)+1)//»»Ò³         µÚËÄĞĞ
		{
			case 4:page=214;arrow=0;break;
		}
		 
    }
 
    if((key_return)== KEY_LONG_PRESS)
    {
        system_delay_ms(300);
        ips200_clear();
        page=1;
    }
	   if((key_add)==KEY_SHORT_PRESS)
    {
		switch(arrow)
		{
			case 1:I_Kp=I_Kp+I_Kp_debrug_val;break;
			case 2:I_Kd=I_Kd+I_Kd_debrug_val;break;
//			case 3:fg.sao_miao=1;break;
		}
    }
	
    if((key_sub)== KEY_SHORT_PRESS)
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

