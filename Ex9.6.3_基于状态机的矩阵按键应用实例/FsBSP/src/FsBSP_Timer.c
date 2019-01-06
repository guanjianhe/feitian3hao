/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : FsBSP_Timer.c
 * 文件描述 : 定时器和中断驱动程序
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

/* ******************************************************************
* 函数名称： Timer0_Init()
* 入口参数：无
* 出口参数：无
* 函数功能：初始化定时器 0
****************************************************************** */
void Timer0_Init(void)
{
	TMOD = 0x01;		                    // 设置定时器0工作在模式1下
	TH0 = 0xDC;		                     	// 定时10ms
	TL0 = 0x00;		                     	// 赋初始值
	TR0 = 1;			                    // 开定时器0
}
