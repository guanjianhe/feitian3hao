/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : STC15_Timer.c
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-08-12
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 文件说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 刘平（xymbmcu@163.com）/清华大学出版社/STC MCU Limited
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include	"STC15_Timer.h"

/********************* Timer0中断函数************************/
void Timer0_ISR (void) interrupt TIMER0_VECTOR
{

}

/********************* Timer1中断函数************************/
void Timer1_ISR (void) interrupt TIMER1_VECTOR
{

}

/********************* Timer2中断函数************************/
void Timer2_ISR (void) interrupt TIMER2_VECTOR
{
	
}

/********************* Timer3中断函数************************/
void timer3_int (void) interrupt TIMER3_VECTOR
{

}

/********************* Timer4中断函数************************/
void timer4_int (void) interrupt TIMER4_VECTOR
{

}

//========================================================================
// 函数: uint8	Timer_Inilize(uint8 TIM, TIM_InitTypeDef *TIMx)
// 描述: 定时器初始化程序.
// 参数: TIMx: 结构参数,请参考timer.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
// 版本: V1.0, 2012-10-22
//========================================================================
uint8 Timer_Init(uint8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer4)	return 1;	//空操作

	if(TIM == Timer0)
	{
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TR0 = 0;		//停止计数
		ET0 = 0;	//禁止中断
		PT0 = 0;	//低优先级中断
		TMOD &= 0xf0;	//定时模式, 16位自动重装
		AUXR &= ~0x80;	//12T模式, 
		INT_CLKO &= ~0x01;	//不输出时钟
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//允许中断
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//高优先级中断
		TMOD |= TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 16位自动重装, 不可屏蔽中断
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//对外计数或分频
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x01;	//输出时钟
		
		TH0 = (u8)(TIMx->TIM_Value >> 8);
		TL0 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer1)
	{
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TR1 = 0;	//停止计数
		ET1 = 0;	//禁止中断
		PT1 = 0;	//低优先级中断
		TMOD &=  0x0f;	//定时模式, 16位自动重装
		AUXR &= ~0x40;	//12T模式, 
		INT_CLKO &= ~0x02;	//不输出时钟
		if(TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//允许中断
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//高优先级中断
		TMOD |= (TIMx->TIM_Mode << 4);	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//对外计数或分频
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x02;	//输出时钟
		
		TH1 = (u8)(TIMx->TIM_Value >> 8);
		TL1 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer2)		//Timer2,固定为16位自动重装, 中断无优先级
	{
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		AUXR &= ~0x1c;		//停止计数, 定时模式, 12T模式
		IE2  &= ~(1<<2);	//禁止中断
		INT_CLKO &= ~0x04;	//不输出时钟
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<2);	//允许中断
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//对外计数或分频
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x04;	//输出时钟

		TH2 = (u8)(TIMx->TIM_Value >> 8);
		TL2 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer3)		//Timer3,固定为16位自动重装, 中断无优先级
	{
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		T4T3M &= 0xf0;		//停止计数, 定时模式, 12T模式, 不输出时钟
		IE2  &= ~(1<<5);	//禁止中断
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<5);	//允许中断
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T4T3M |=  (1<<1);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T4T3M |=  (3<<1);	//对外计数或分频
		if(TIMx->TIM_ClkOut == ENABLE)	T4T3M |=  1;	//输出时钟

		TH3 = (u8)(TIMx->TIM_Value >> 8);
		TL3 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	T4T3M |=  (1<<3);	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer4)		//Timer4,固定为16位自动重装, 中断无优先级
	{
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		T4T3M &= 0x0f;		//停止计数, 定时模式, 12T模式, 不输出时钟
		IE2  &= ~(1<<6);	//禁止中断
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<6);	//允许中断
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T4T3M |=  (1<<5);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T4T3M |=  (3<<5);	//对外计数或分频
		if(TIMx->TIM_ClkOut == ENABLE)	T4T3M |=  (1<<4);	//输出时钟

		TH4 = (u8)(TIMx->TIM_Value >> 8);
		TL4 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	T4T3M |=  (1<<7);	//开始运行
		return	0;		//成功
	}

	return 2;	//错误
}
