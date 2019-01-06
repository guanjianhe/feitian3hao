/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : FsBSP_LedScreen.c
 * 文件描述 : FsSTC15飞天三号开发板点阵屏驱动程序
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-09-04
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 
 * Copyright (C), 2014-2015, 兰州文轩电子科技有限公司
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_LedScreen.h"
#include <intrins.h>

/* ******************************************************************
 * 函数名称：LedScreen_WrOneByte(unsigned char ucDat)
 * 入口参数：unsigned char SEGDat,unsigned charCOMDat 
 * 出口参数：无
 * 函数功能：向LedScreen中写入一个字节
****************************************************************** */
void LedScreen_WrOneByte(unsigned char SEGDat,unsigned char COMDat)
{
	unsigned char i = 0;
	unsigned char j = 0;
	/* 通过8循环将8位数据一次移入第一个595 */
	for(i=0;i<8;i++)
	{
		LedSER = (bit)(SEGDat & 0x80);
		SCK = 0;
		SEGDat <<= 1;
		SCK = 1;
	}
	/* 通过8循环将8位数据，通过级联的方式最后的结果是
	SEGDat在是点阵的负极端数据，COMDat是点阵的正极端数据*/
	for(j=0;j<8;j++)
	{
		LedSER = (bit)(COMDat & 0x80);
		SCK = 0;
		COMDat <<= 1;
		SCK = 1;
	}
	/* 数据并行输出（借助上升沿） */
	RCK = 0;		
	_nop_();
	_nop_();
	RCK = 1;
}
