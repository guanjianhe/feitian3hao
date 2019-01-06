/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : FsBSP_TIMRR.c
 * 文件描述 : 定时器初始化设置函数
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-07-16
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 
 * Copyright (C), 2014-2015, 兰州文轩电子科技有限公司
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_Timer.h"

/* ******************************************************************
* 函数名称： Timer0_InitClock()
* 入口参数：无
* 出口参数：无
* 函数功能：初始化定时器0设置其为可编程时钟模式，并且输出38.4KHz的方波
****************************************************************** */
void Timer0_InitClock(void)
{
	AUXR |= 0x80;          //定时器0为1T模式
	TMOD = 0x00;           //设置定时器为模式0(16位自动重装载)
	TMOD &= ~0x04;         //C/T0=0, 对内部时钟进行时钟输出
	TL0 = F38_4KHz;        //初始化计时值
	TH0 = F38_4KHz >> 8;
	TR0 = 1;               //开启定时器0的运行控制位
	INT_CLKO = 0x01;       //使能定时器0的时钟输出功能
}
