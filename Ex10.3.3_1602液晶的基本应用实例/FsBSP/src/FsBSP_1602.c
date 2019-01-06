/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : FsBSP_1602.c
 * 文件描述 : 1602液晶的驱动程序
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-08-30
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_1602.h"
#include "FsBSP_Delay.h"

void LcdGPIO_Init(void)
{
	P0M1 = 0;   P0M0 = 0;   //设置为准双向口
    P3M1 = 0;   P3M0 = 0;   //设置为准双向口
}
/* ***************************************************** */
// 函数名称：DectectBusyBit()
// 函数功能：检测状态标志位（判断是忙/闲）
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void DectectBusyBit(void)
{   
	P0 = 0xff;			// 读状态值时，先赋高电平
	RS = 0;
	RW = 1;
	EN = 1;
	DelayMS(1);
	while(P0 & 0x80);	// 若LCD忙，停止到这里，否则走起
	EN = 0;				// 之后将EN初始化为低电平 
}
/* ***************************************************** */
// 函数名称：WrComLCD()
// 函数功能：为LCD写指令
// 入口参数：指令（ComVal）
// 出口参数：无
/* ***************************************************** */
void WrComLCD(uChar8 ComVal)
{
	DectectBusyBit();
	RS = 0;
	RW = 0;
	EN = 1;
	P0 = ComVal;
	DelayMS(1);
	EN = 0;	
}
/* ***************************************************** */
// 函数名称：WrDatLCD()
// 函数功能：为LCD写数据
// 入口参数：数据（DatVal）
// 出口参数：无
/* ***************************************************** */
void WrDatLCD(uChar8 DatVal)
{
	DectectBusyBit();
	RS = 1;
	RW = 0;
	EN = 1;
	P0 = DatVal;
	DelayMS(1);
	EN = 0;	
}
/* ***************************************************** */
// 函数名称：LCD_Init()
// 函数功能：初始化LCD
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void LCD_Init(void)
{ 
	WrComLCD(0x38);		// 16*2行显示、5*7点阵、8位数据接口
	DelayMS(1);			// 稍作延时
	WrComLCD(0x38);    	// 重新设置一遍
	WrComLCD(0x01);    	// 显示清屏 
	WrComLCD(0x06);    	// 光标自增、画面不动  
	DelayMS(1);			// 稍作延时
	WrComLCD(0x0C);    	// 开显示、关光标并不闪烁
}
/* ***************************************************** */
// 函数名称：Dispaly_1602()
// 函数功能：1602的显示函数
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void Dispaly_1602(void)
{
  uChar8 ucVal;
	LCD_Init();
	DelayMS(5);
	WrComLCD(0x80);					// 选择第一行
	while(TAB1[ucVal] != '\0')		// 字符串数组的最后还有个隐形的"\0"
	{
		WrDatLCD(TAB1[ucVal]);
		ucVal++;
	}
	ucVal = 0;						// 语句简单，功能重要
	WrComLCD(0xC0);					// 选择第二行（0x80+0x40）
	while(TAB2[ucVal] != '\0')
	{
		WrDatLCD(TAB2[ucVal]);
		ucVal++;
	}
}

/* *********************************** End of File *********************************** */