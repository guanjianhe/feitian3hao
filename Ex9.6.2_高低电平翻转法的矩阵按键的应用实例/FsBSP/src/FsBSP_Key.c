/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : FsBSP_Key.c
 * 文件描述 : 独立按键或者矩阵按键的驱动程序
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-08-08
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_Key.h"
#include "STC15.h"
#include "FsBSP_Delay.h"



/* ***************************************************** */
// 函数名称：ScanKey()
// 函数功能：矩阵按键扫描
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void ScanKey(void)
{
  uChar8 RowTemp,ColumnTemp,RowColTemp;
	KEYPORT = 0xf0;			 					// 先给高四位高电平
	DelayMS(2);										//让单片机喘口气，因为STC15的速度太快啦~~
	RowTemp = KEYPORT & 0xf0;					// 读取行值，为确定是那一行用
	DelayMS(2);										//让单片机喘口气，因为STC15的速度太快啦~~
	if((KEYPORT & 0xf0) != 0xf0)							// 判断是否有按键，此时还不能确定是按键，还是抖动
	{
		DelayMS(5);								// 去抖动
		if((KEYPORT & 0xf0)!= 0xf0)
		{
			RowTemp = KEYPORT & 0xf0;			// 说明真的有键按下，那么读取行值
			DelayMS(2);									//让单片机喘口气，因为STC15的速度太快啦~~
			KEYPORT = 0x0f;						// 接着给低四位高电平
			DelayMS(2);								//让单片机喘口气，因为STC15的速度太快啦~~
			ColumnTemp = KEYPORT & 0x0f;		// 读取列值，为确定是那一列用
			RowColTemp = RowTemp | ColumnTemp;	// 行列值进行或运算，从而确实行列值，确定按键用
			while((KEYPORT & 0x0f) != 0x0f);	// 松手检测
		}
	}
	switch(RowColTemp)							// 确定按键
	{
		case 0xee:	g_ucKeyNum = 0; break;
		case 0xde:	g_ucKeyNum = 1; break;
		case 0xbe:	g_ucKeyNum = 2; break;
		case 0x7e:	g_ucKeyNum = 3; break;
		case 0xed:	g_ucKeyNum = 4; break;
		case 0xdd:	g_ucKeyNum = 5; break;
		case 0xbd:	g_ucKeyNum = 6; break;
		case 0x7d:	g_ucKeyNum = 7; break;
		case 0xeb:	g_ucKeyNum = 8; break;
		case 0xdb:	g_ucKeyNum = 9; break;
		case 0xbb:	g_ucKeyNum = 10; break;
		case 0x7b:	g_ucKeyNum = 11; break;
		case 0xe7:	g_ucKeyNum = 12; break;
		case 0xd7:	g_ucKeyNum = 13; break;
		case 0xb7:	g_ucKeyNum = 14; break;
		case 0x77:	g_ucKeyNum = 15; break;
		default:	g_ucKeyNum = 16; break;
	}
}