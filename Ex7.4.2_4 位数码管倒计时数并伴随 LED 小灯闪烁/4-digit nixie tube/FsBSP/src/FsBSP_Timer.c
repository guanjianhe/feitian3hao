/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : FsBSP_Timer.c
 * 文件描述 : 定时器和中断的驱动程序
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-07-11
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 
 * Copyright (C), 2014-2015, 兰州文轩电子科技有限公司
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_Timer.h"
#include "FsBSP_HC595.h"

unsigned char  Bit_Tab[] = 
{0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};		//位选数组

unsigned char  Disp_Tab[] = 
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};	 	
//0~7数字显示编码数组

unsigned int g_uiNum = 0;				  //发给数码管的数，需要分离个，十，百，千

/* ******************************************************************
* 函数名称： Timer_Init()
* 入口参数：无
* 出口参数：无
* 函数功能：初始化定时器 0，定时器1
****************************************************************** */
void Timer01_Init(void)
{
	AUXR |= 0x80;	// 定时器0工作于1T模式
	TMOD &= 0x00;	// 设置定时器0、1工作在模式0下（16位自动重装）
	TL0 = 0x9A;		// 设置定时初值
	TH0 = 0xA9;		// 定时2ms
	TR0 = 1; 	  	// 开定时器 0
	ET0 = 1;      	// 打开定时器0的中断标志位

	AUXR |= 0x00;	// 定时器1工作于12T模式
	TH1 = 0x4C;   	// 为定时器1赋初始值
	TL1 = 0x00;   	// 定时50ms
	TR1 = 1; 	  	// 启动定时器 1
	ET1 = 1;      	//打开定时器1的中断
	
	EA = 1;       	// 开总中断
}

/* ******************************************************************
 * 函数名称：Display()
 * 入口参数：无
 * 出口参数：无
 * 函数功能：四位数码管倒计时的显示函数
****************************************************************** */
void Display()
{
	unsigned char QianNum,BaiNum,ShiNum,GeNum;

	GeNum  = g_uiNum % 10;			// 分类各个数位
	ShiNum = g_uiNum /10% 10;
	BaiNum = g_uiNum /100% 10;
	QianNum = g_uiNum /1000;

	P6 = Bit_Tab[3];					// 送位选数据
	HC595_WrOneByte(Disp_Tab[GeNum]);	// 送段选数据
	HC595_WrOneByte(0x00);				// 消除鬼影现象
	P6 = Bit_Tab[2];
	HC595_WrOneByte(Disp_Tab[ShiNum]);
	HC595_WrOneByte(0x00);
	P6 = Bit_Tab[1];
	HC595_WrOneByte(Disp_Tab[BaiNum]);
	HC595_WrOneByte(0x00);
	P6 = Bit_Tab[0];
	HC595_WrOneByte(Disp_Tab[QianNum]);
	HC595_WrOneByte(0x00);
}
/* ******************************************************************
* 函数名称：Timer0_ISR(void) 
* 入口参数：无
* 出口参数：无
* 函数功能：定时器0的中断函数
****************************************************************** */
void Timer0_ISR(void) interrupt 1
{
	static unsigned int  uiCounter = 0;
	EA = 0;

    uiCounter ++;                 
	if(500 == uiCounter)  //计数500次，说明1s到了
	{
		uiCounter = 0;
		g_uiNum++;
		if(1000 == g_uiNum) //四位数码管最多显示9999
			g_uiNum = 0;
	}
	
	EA = 1;

}
/* ******************************************************************
* 函数名称：Timer1_ISR(void) 
* 入口参数：无
* 出口参数：无
* 函数功能：定时器1的中断函数
****************************************************************** */
void Timer1_ISR(void) interrupt 3
{
	static unsigned char ucCounter = 0;
	EA = 0;
	
    ucCounter ++;
	if(20 == ucCounter)  	// 计数20次是多少秒呢？
	{
		ucCounter = 0;
		P7 = ~P7;         	// 八个LED灯取反
	}
	
	EA = 1;
}
