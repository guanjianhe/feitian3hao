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


/* ***************************************************** */
// 函数名称：DectectBusyBit()
// 函数功能：液晶遇忙检测
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void DectectBusyBit(void)
{   
	P0 = 0xff;				// 读状态值时，先赋高电平 
	RS = 0;
	RW = 1;					// 从液晶读数据
	EN = 1;
	DelayMS(1);
	while(P0 & 0x80);		// 若LCD忙，停止到这里，否则走起
	EN = 0;					// 之后将EN初始化为低电平 
}
/* ***************************************************** */
// 函数名称：WrComLCD()
// 函数功能：向液晶写命令
// 入口参数：命令(ComVal)
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
// 函数功能：向液晶写数据
// 入口参数：数据(DatVal)
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
// 函数功能：液晶初始化
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void LCD_Init(void)
{ 
	WrComLCD(0x38);		// 16*2行显示、5*7点阵、8位数据接口
	DelayMS(1);  		// 稍作延时
	WrComLCD(0x38);    	// 重新设置一遍
	WrComLCD(0x01);    	// 显示清屏 
	WrComLCD(0x06);    	// 光标自增、画面不动  
	DelayMS(1);			// 稍作延时
	WrComLCD(0x0C);    	// 开显示、关光标并不闪烁
}
/* ***************************************************** */
// 函数名称：ClearDisLCD()
// 函数功能：清屏
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void ClearDisLCD(void) 
{ 
	WrComLCD(0x01); 	   //发送清屏指令
	DelayMS(1);
}
/* ***************************************************** */
// 函数名称：WrStrLCD()
// 函数功能：向液晶写字符串数据
// 入口参数：行（Row）、列（Column）、字符串（*String）
// 出口参数：无
/* ***************************************************** */
void WrStrLCD(bit Row,uChar8 Column,uChar8 *String) 
{     
	if (!Row) 			 	//第1行第1列起始地址0x80
	{     
		WrComLCD(0x80 + Column);
	}
	else 				//第2行第1列起始地址0xC0
	{     
		WrComLCD(0xC0 + Column);     
	}        
	while (*String) 	 	//发送字符串
	{     
	    WrDatLCD( *String); 
		String ++;
	}
}
/* ***************************************************** */
// 函数名称：WrCharLCD()
// 函数功能：向液晶写字节数据
// 入口参数：行（Row）、列（Column）、字节数据（Dat）
// 出口参数：无
/* ***************************************************** */
void WrCharLCD(bit Row,uChar8 Column,uChar8 Dat) 
{
	if (!Row) 					//第1行第1列起始地址0x80
	{     
		WrComLCD(0x80 + Column);     
	}    
	else 			   		//第2行第1列起始地址0xC0
	{     
		WrComLCD(0xC0 + Column);     
	}        
	WrDatLCD( Dat);  			//发送数据
}
/* ***************************************************** */
// 函数名称：Dispaly_1602()
// 函数功能：1602的显示函数
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void Dispaly_1602(void)
{
  uChar8 i;			 		//循环变量
	uChar8 *Pointer;	 		//指针变量
	LCD_Init();		 		//初始化
	while(1)
	{
		i = 0;
		ClearDisLCD();  	 			//清屏
		Pointer = String2;	 			//指针指向字符串2首地址
		WrStrLCD(0,3,String1);  		//第1行第3列写入字符串1
		while (*Pointer) 				//按字节方式写入字符串2
		{   
			WrCharLCD(1,i,*Pointer);   	//第2行第i列写入一个字符
			i ++;   					//写入的列地址加一
			Pointer ++;   				//指针指向字符串中下一个字符
		  	if(i > 16)					//是否超出能显示的16个字符
			{
				WrStrLCD(0,3,"         ");	//将String1用空字符串代替;清空第1行显示应该使用9个空字符            
				WrComLCD(0x18);						//光标和显示一起向左移动
				WrStrLCD(0,i - 13,String1);  		//原来位置重新写入字符串1
				DelayMS(3000); 						//为了移动后清晰显示
			} 
			else
			{
				DelayMS(750);	  		//控制两字之间显示速度
			}
		}
	}
}

/* *********************************** End of File *********************************** */