/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : 1602液晶的基本应用实例
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-08-30
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

/////////////////////////////////
//头文件
#include	"BSP_Include.h"

/////////////////////////////////
//LED管脚预定义
#define     LED1    P70
#define     LED2    P71
#define     LED3    P72   
#define     LED4    P73  
/*************	功能说明	**************
旋转ADC旋钮 
4个LED会根据电压的大小 来显示4位十六进制的亮灭现象
LED1是最高位 LED4是最低位
即旋钮调电压越大，LED1234呈现的4位十六进制数就越大
LCD1602第一行会显示10位真实的采样值
LCD1602第二行会显示放大10倍后的真实电压值
******************************************/

void	GPIO_config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.Mode=GPIO_OUT_PP;
    GPIO_InitStructure.Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
    GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);//LED灯IO初始化

    GPIO_InitStructure.Mode=GPIO_OUT_PP;
    GPIO_InitStructure.Pin=GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
    GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);//1602液晶控制管脚IO初始化
	
	GPIO_InitStructure.Mode=GPIO_PullUp;
    GPIO_InitStructure.Pin=GPIO_Pin_All;
    GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);//1602液晶DB管脚IO初始化
    
    GPIO_InitStructure.Mode=GPIO_HighZ;
    GPIO_InitStructure.Pin=GPIO_Pin_6;
    GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);//ADC管脚IO初始化
}

void	ADC_config(void)
{
	ADC_InitTypeDef		ADC_InitStructure;				//结构定义
	ADC_InitStructure.ADC_Px        = ADC_P15 ;	        //设置要做ADC的IO
	ADC_InitStructure.ADC_Speed     = ADC_360T;			//ADC速度			ADC_90T,ADC_180T,ADC_360T,ADC_540T
	ADC_InitStructure.ADC_Power     = DISABLE;			//ADC功率允许/关闭	ENABLE,DISABLE
	ADC_InitStructure.ADC_AdjResult = ADC_RES_H8L2;		//ADC结果调整,	ADC_RES_H2L8,ADC_RES_H8L2
	ADC_InitStructure.ADC_Polity    = PolityLow;		//优先级设置	PolityHigh,PolityLow
	ADC_InitStructure.ADC_Interrupt = DISABLE;			//中断允许		ENABLE,DISABLE
	ADC_Inilize(&ADC_InitStructure);					//初始化
	ADC_PowerControl(ENABLE);							//单独的ADC电源操作函数, ENABLE或DISABLE
}
/**********************************************/
void main(void)
{		
	u8	j;
	u16 k;
	ADC_config();
	Delay_ms(100);
	GPIO_config();
	Delay_ms(100);
	Dispaly_1602();   //1602的显示函数
	Delay_ms(100);
	while (1)
	{	  
			
        k = Get_ADC10bitResult(5);	//参数0~7,查询方式做一次ADC, 返回值就是结果, == 1024 为错误
		Delay_ms(100);
	    display_num(k);//1602的显示函数-1024真实的采样值
        Delay_ms(100);
	    display_Voltage_value(k);//1602的显示函数-放大十倍的真实采样电压值
		Delay_ms(100);
        j=k>>6;//将右对齐的数据变成4位的数值--取最大的前4位 
        if(1==(j&0x01))
        {
            LED1=0;
        } 
        else
        {
            LED1=1;
        }
      
        if(0X02==(j&0x02))
        {
            LED2=0;
        } 
        else
        {
            LED2=1;
        }
     
        if(0X04==(j&0x04))
        {
            LED3=0;
        } 
        else
        {
            LED3=1;
        }
       
        if(0X08==(j&0x08))
        {
            LED4=0;
        } 
        else
        {
            LED4=1;
        }
        Delay_ms(200);
	}
}

/* *********************************** End of File *********************************** */

