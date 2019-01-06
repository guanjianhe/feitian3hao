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
#include "FsBSP_Delay.h"
#include <intrins.h>

/* *******说明(选择列所用的数组)****************
*1.最低位控制第一列
*2.该数组的意思是从第一列开始，依次选中第1...8列
********************************************* */
uChar8 code ColArr[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
/* ********心图案1******************************
* 该数组用于存储图案
* 取摸方式 纵向取摸 方式：由下到上
********************************************* */
uChar8 RowArr[8] = {0x1C,0x22,0x42,0x84,0x84,0x42,0x22,0x1C};


/* ******************************************************************
 * 函数名称：void LedScreen_WrTwoByte(unsigned char SEGDat,unsigned char COMDat)
 * 入口参数：unsigned char SEGDat,unsigned charCOMDat 
 * 出口参数：无
 * 函数功能：向LedScreen中写入两个字节
****************************************************************** */
void LedScreen_WrTwoByte(unsigned char SEGDat,unsigned char COMDat)
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
/* ******************************************************************
 * 函数名称：LedScreenDis()
 * 入口参数：无
 * 出口参数：无
 * 函数功能：LedScreenDis()用来显示行列数组组成的点阵内容-对了纵向取模的数据
****************************************************************** */
void LedScreenDis()
{
	unsigned char j;
	for(j=0;j<8;j++)
	{
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]);
		DelayMS(1);                                 //延时函数用来人为调节刷新的频率，太快画面显示太快，太慢有抖动现象
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]);
		DelayMS(1);
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]);
		DelayMS(1);			
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]); 
		DelayMS(1);
		
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]); 
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]); 
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]);		
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]);
	}
}
/* ******************************************************************
 * 函数名称：Up_Move_Dis(void)
 * 入口参数：无
 * 出口参数：无
 * 函数功能：当前画面上移显示，需要LedScreenDis()子函数配合
****************************************************************** */
void Up_Move_Dis(void)
{
	uChar8 iCtr;
	for(iCtr = 0; iCtr < 8; iCtr++)
	{
		RowArr[iCtr] = _cror_(RowArr[iCtr],1);	
		LedScreenDis();
	}
	DelayMS(30);						//延时函数用来人为调节刷新的频率，太快画面显示太快，太慢有抖动现象
}
/* ***************************************************** */
// 函数名称：Down_Move_Dis(void)
// 函数功能：当前画面下移显示,需要LedScreenDis()子函数配合
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void Down_Move_Dis(void)
{
	uChar8 iCtr;  
	for(iCtr = 0; iCtr < 8; iCtr++)
	{
		RowArr[iCtr] = _crol_(RowArr[iCtr],1);	
		LedScreenDis();
	}
	DelayMS(30);						//延时函数用来人为调节刷新的频率，太快画面显示太快，太慢有抖动现象
}
