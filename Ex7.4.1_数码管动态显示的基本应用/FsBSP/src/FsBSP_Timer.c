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

unsigned char  Disp_Tab[] = 
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07};	 	//0~7数字显示编码数组

void Timer0_Init(void)
{
	AUXR |= 0x80;	// 定时器时钟1T模式
	TMOD &= 0xF0;	// 设置定时器0 工作在模式0下（16位自动重装）
	TL0 = 0x9A;		// 设置定时初值
	TH0 = 0xA9;		// 定时2ms
	TR0 = 1; 	  	// 开定时器 0
	ET0 = 1;      	// 打开定时器0的中断标志位
	EA = 1;       	// 开总中断
}

/* ******************************************************************
* 函数名称：Timer0_ISR(void) 
* 入口参数：无
* 出口参数：无
* 函数功能：定时器0的中断函数
****************************************************************** */
void Timer0_ISR(void) interrupt 1
{
	unsigned long int uiNum = 1314520;
	
	P6 = 0xFE;		// 选择第一位数码管
	HC595_WrOneByte(Disp_Tab[uiNum / 1000000]);
	P6 = 0xFD;		// 选择第二位数码管
	HC595_WrOneByte(Disp_Tab[uiNum / 100000 % 10]);
	P6 = 0xFB;		// 选择第三位数码管
	HC595_WrOneByte(Disp_Tab[uiNum / 10000 % 10]);
	P6 = 0xF7;		// 选择第四位数码管
	HC595_WrOneByte(Disp_Tab[uiNum / 1000 % 10]);
	P6 = 0xEF;		// 选择第五位数码管
	HC595_WrOneByte(Disp_Tab[uiNum / 100 % 10]);
	P6 = 0xDF;		// 选择第六位数码管
	HC595_WrOneByte(Disp_Tab[uiNum / 10 % 10]);
	P6 = 0xBF;		// 选择第七位数码管
	HC595_WrOneByte(Disp_Tab[uiNum % 10]);
}
