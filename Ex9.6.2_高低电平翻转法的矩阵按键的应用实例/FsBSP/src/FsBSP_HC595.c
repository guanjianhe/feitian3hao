/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : FsBSP_HC595.c
 * 文件描述 : 74HC595驱动程序
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-07-29
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 
 * Copyright (C), 2014-2015, 兰州文轩电子科技有限公司
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_HC595.h"
#include <intrins.h>

/* ******************************************************************
 * 函数名称：HC595_WrOneByte()
 * 入口参数：待写入HC595的一个字节（ucDat）
 * 出口参数：无
 * 函数功能：向HC595中写入一个字节
****************************************************************** */
void HC595_WrOneByte(unsigned char ucDat)
{
	unsigned char i = 0;
	/* 通过8循环将8位数据一次移入74HC595 */
	for(i=0;i<8;i++)
	{
		smgSER = (bit)(ucDat & 0x80);
		SCK = 0;
		ucDat <<= 1;
		SCK = 1;
	}
	/* 数据并行输出（借助上升沿） */
	RCK = 0;		
	_nop_();
	_nop_();
	RCK = 1;
}
/* ***************************************************** */
// 函数名称：Display()
// 函数功能：数码管刷新
// 入口参数：需显示的数值(ucVal)
// 出口参数：无
/* ***************************************************** */
void Display(uChar8 ucVal)
{
	P60 = 0;                //启动第一个数码管的位选
	if(ucVal == 16)			//若键值是16即没有按键按下，则不显示
	{
   		HC595_WrOneByte(SMG_Array[0]);
	}
	else				   //若有按下，显示对应键值
	{
		HC595_WrOneByte(SMG_Array[ucVal]);
	}
}
/* *********************************** End of File *********************************** */