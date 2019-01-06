/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : 红外解码 + 数码管
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-09-09
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "BSP_Include.h"

extern bit g_IR_OK;				// stc15_exti.c 文件中定义，这里只是声明
extern u8  xdata g_IRcord[4];	// stc15_exti.c 文件中定义，这里只是声明

unsigned char  Bit_Tab[] = 
{0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};		//位选数组

unsigned char  Disp_Tab[] = 
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void Timer_ConfigInit(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//结构定义

	TIM_InitStructure.TIM_Mode      = TIM_8BitAutoReload;	//指定工作模式,   TIM_8BitAutoReload
	TIM_InitStructure.TIM_Polity    = PolityLow;			//指定中断优先级, PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//中断是否允许,   ENABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//指定时钟源,     TIM_CLOCK_12T
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, DISABLE
	TIM_InitStructure.TIM_Value     = 0;					//初值
	TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//初始化Timer0
}

void Interrupt_ConfigInit(void)
{
	EXTI_InitTypeDef	EXTI_InitStructure;					//结构定义
    
	EXTI_InitStructure.EXTI_Mode      = EXT_MODE_Fall;	    //中断模式,  EXT_MODE_Fall
	EXTI_InitStructure.EXTI_Polity    = PolityHigh;			//中断优先级, PolityHigh
	EXTI_InitStructure.EXTI_Interrupt = ENABLE;				//中断允许,   ENABLE
	Ext_Inilize(EXT_INT0,&EXTI_InitStructure);				//初始化INT0	EXT_INT0
}

/* ***************************************************** */
// 函数名称：LedDisplay()
// 函数功能：数码管显示
// 入口参数：待显示数据(ByteVal[])
// 出口参数：无
/* ***************************************************** */
void LedDisplay(u8 ByteVal[])
{
	u8  *Dis_ByteVal = ByteVal;
	
	P6 = Bit_Tab[0];					// 送位选数据
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+0)/16]);	// 送段选数据
	HC595_WrOneByte(0x00);				// 消除鬼影现象
	P6 = Bit_Tab[1];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+0)%16]);
	HC595_WrOneByte(0x00);
	
	P6 = Bit_Tab[2];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+1)/16]);
	HC595_WrOneByte(0x00);
	P6 = Bit_Tab[3];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+1)%16]);
	HC595_WrOneByte(0x00);
	
	P6 = Bit_Tab[4];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+2)/16]);
	HC595_WrOneByte(0x00);
	P6 = Bit_Tab[5];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+2)%16]);
	HC595_WrOneByte(0x00);
	
	P6 = Bit_Tab[6];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+3)/16]);
	HC595_WrOneByte(0x00);
	P6 = Bit_Tab[7];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+3)%16]);
	HC595_WrOneByte(0x00);
}

void main(void)
{
	Delay_ms(100);		// 待上电稳定
	
	EA = 1;				// 开总中断
	
	GPIO_ConfigInit();
	Timer_ConfigInit();
	Interrupt_ConfigInit();
	
	for(;;)
	{
		if(g_IR_OK)         	//如果接收好了进行红外处理
		{   
			IrcordPro();
			g_IR_OK=0;
		}
		LedDisplay(g_IRcord);
	}
}

/* *********************************** End of File *********************************** */
