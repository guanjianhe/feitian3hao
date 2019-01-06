/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : 红外解码 + 数码管
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-09-15
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "BSP_Include.h"

sbit LedModel = P3^4;        	//模式灯
sbit KeyOnOff_IO = P3^2;   		//开机按键

extern bit g_bKeyScanFlag;

typedef enum KeyEnum{StateInit,PrsDownOk,KeyOnOff,KeyModel};    
/* =================  未按下，       按下，     开关，   模式  ============= */

void Timer_ConfigInit(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//结构定义

	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//工作模式，TIM_16BitAutoReload
	TIM_InitStructure.TIM_Polity    = PolityLow;			//中断优先级，PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//否允许 ENABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//时钟源，TIM_CLOCK_1T
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//不输出高速脉冲
	TIM_InitStructure.TIM_Value     = 65425;				//初值，定时10us
	TIM_InitStructure.TIM_Run       = ENABLE;				//启动定时器,ENABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//初始化Timer0
	
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//时钟源，TIM_CLOCK_12T
	TIM_InitStructure.TIM_Value     = 47104;				//初值，定时20ms
	Timer_Inilize(Timer2,&TIM_InitStructure);				//初始化Timer2
}

void Interrupt_ConfigInit(void)
{
	EXTI_InitTypeDef	EXTI_InitStructure;					//结构定义
    
	EXTI_InitStructure.EXTI_Polity    = PolityHigh;			//中断优先级, PolityHigh
	EXTI_InitStructure.EXTI_Interrupt = ENABLE;				//中断允许,  ENABLE
	Ext_Inilize(EXT_INT4,&EXTI_InitStructure);				//初始化INT0,EXT_INT0
}

void KeyScan(void)   //按键扫描
{
	static u8 KeyStateTemp=0,KeyTime=0;     //按键动作序号,开关计时,长按计时
	static bit bModelFlag=1;   				//自动和手动下载模式切换标志位
	
	switch (KeyStateTemp)
	{
		case StateInit: 	//未按状态
			if(KeyOnOff_IO)
				KeyStateTemp = StateInit;
			else KeyStateTemp = PrsDownOk;
		break;
			
		case PrsDownOk:    	//有按下的状态(状态未知，有抖动的可能)
			if(KeyOnOff_IO) KeyStateTemp = StateInit;
			else KeyStateTemp = KeyOnOff;	//真的被按下，进入开关机状态	
		break;
		
		case KeyOnOff:    	//开关机控制状态
			if(KeyOnOff_IO)
			{
				KeyTime = 0;
				OnOff_IO =~ OnOff_IO;		//单按一次，切换开机和关机
				KeyStateTemp = StateInit;
			}
			else
			{
				KeyTime++;
				if (KeyTime >= 50)			//长按超过1S(20ms*50)则切换到模式状态
				{
					KeyTime=0;
					KeyStateTemp = KeyModel;
				}
			}
		break;
			
		case KeyModel:		//模式里切换是自动下载还是手动模式
			bModelFlag =~ bModelFlag;
			if(bModelFlag)		//自动下载模式   
			{
				INT_CLKO |= 0x40;     	//开启外部中断4
				LedModel = 0;			//模式灯亮，代表是自动下载模式
			}
			else 			// 手动模式
			{
				INT_CLKO &= 0xbf;    	//关闭外部中断4
				LedModel = 1;			//模式灯不亮，代表是冷启动模式
			}
			KeyStateTemp = StateInit;
			IE2 &= 0xfb;    //关闭定时器2，防止长按按键时乱闪
		break;
		default:	KeyStateTemp=StateInit;		break;
	}
}

void main(void)
{
	Delay_ms(10);			// 待上电稳定
	
	EA = 1;					// 开总中断
	
	GPIO_ConfigInit();		// 初始化端口
	Timer_ConfigInit();		// 初始化定时器
	Interrupt_ConfigInit();	// 初始化中断
	
	for(;;)
	{
		if(g_bKeyScanFlag == 1)		//在定时器2中中置位，作用是每过20S扫描一次按键
		{
			g_bKeyScanFlag = 0;
			KeyScan();
		}
		if(KeyOnOff_IO) IE2 |=0x04;  //开启定时器2
	}
}

/* *********************************** End of File *********************************** */
