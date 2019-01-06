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
		DB = 0xff;				// 读状态值时，先赋高电平 
		RS = 0;
		RW = 1;					// 从液晶读数据
		EN = 1;
		DelayMS(1);
		while(DB & 0x80);		// 若LCD忙，停止到这里，否则走起
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
		DB = ComVal;
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
		DB = DatVal;
		DelayMS(1);
		EN = 0;	
}
/* ***************************************************** */
// 函数名称：LcdSetCursor(uChar8 x, uChar8 y)
// 函数功能：设置显示起始地址
// 入口参数：uChar8 x, uChar8 y，即光标的坐标位置
// 出口参数：无
/* ***************************************************** */
void LcdSetCursor(uChar8 x, uChar8 y)
{
		uChar8 addr;
		if(y == 0)
			addr = 0x00 + x;
		else
			addr = 0x40 + x;
		WrComLCD(addr | 0x80);
		DelayMS(1);
}
/* ***************************************************** */
// 函数名称：LcdShowStr(uChar8 x, uChar8 y, uChar8 *str)
// 函数功能：设置字符串的显示
// 入口参数：uChar8 x, uChar8 y（即光标的坐标位置）uChar8 *str是字符串指针
// 出口参数：无
/* ***************************************************** */
void LcdShowStr(uChar8 x, uChar8 y, uChar8 *str)
{
		LcdSetCursor(x, y);
		while(*str != '\0')
		{
			WrDatLCD(*str++); 
			DelayMS(1);
		}
}
/* ***************************************************** */
// 函数名称：LcdShowCn(uChar8 x, uChar8 y, uChar8 seat)
// 函数功能：设置汉字显示
// 入口参数：uChar8 x, uChar8 y（即光标的坐标位置）uChar8 seat是数据
// 出口参数：无
/* ***************************************************** */
void LcdShowCn(uChar8 x, uChar8 y, uChar8 seat)
{
		LcdSetCursor(x, y);
		WrDatLCD(seat);
		DelayMS(1);
}
/* ***************************************************** */
// 函数名称：InitLcdCn(uChar8 *str)
// 函数功能：将自定义字符串的数据写入CGRAM中
// 入口参数：*str是字符串指针
// 出口参数：无
/* ***************************************************** */
void InitLcdCn(uChar8 *str)
{
		uChar8 i;
		WrComLCD(0x40);
	 	for(i = 0;i<32;i++)  //连续写入自定义字符串数据
    {
      WrDatLCD(*str++);
			DelayMS(1);
    }
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
		DelayMS(5);  		// 稍作延时
		WrComLCD(0x38);    	// 重新设置一遍
		WrComLCD(0x01);    	// 显示清屏 
		WrComLCD(0x06);    	// 光标自增、画面不动  
		DelayMS(5);			// 稍作延时
		WrComLCD(0x0C);    	// 开显示、关光标并不闪烁
}

//========================================================================
// 函数: void   CheckBusy(void)
// 描述: 检测忙函数
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void    CheckBusy(void)
{
    u16 i;
    for(i=0; i<5000; i++)   {if(!LCD_B7)    break;}     //check the LCD busy or not. With time out
//  while(LCD_B7);          //check the LCD busy or not. Without time out
}

//========================================================================
// 函数: void IniSendCMD(u8 cmd)
// 描述: 初始化写命令(不检测忙)
// 参数: cmd: 要写的命令.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void IniSendCMD(u8 cmd)
{
    LCD_RW = 0;
    LCD_BusData(cmd);
    LCD_DelayNop();
    LCD_ENA = 1;
    LCD_DelayNop();
    LCD_ENA = 0;
    LCD_BusData(0xff);
}

//========================================================================
// 函数: void Write_CMD(u8 cmd)
// 描述: 写命令(检测忙)
// 参数: cmd: 要写的命令.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void Write_CMD(u8 cmd)
{
    LCD_RS  = 0;
    LCD_RW = 1;
    LCD_BusData(0xff);
    LCD_DelayNop();
    LCD_ENA = 1;
    CheckBusy();            //check the LCD busy or not.
    LCD_ENA = 0;
    LCD_RW = 0;
    
    LCD_BusData(cmd);
    LCD_DelayNop();
    LCD_ENA = 1;
    LCD_DelayNop();
    LCD_ENA = 0;
    LCD_BusData(0xff);
}

//========================================================================
// 函数: void Write_DIS_Data(u8 dat)
// 描述: 写显示数据(检测忙)
// 参数: dat: 要写的数据.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void Write_DIS_Data(u8 dat)
{
    LCD_RS = 0;
    LCD_RW = 1;

    LCD_BusData(0xff);
    LCD_DelayNop();
    LCD_ENA = 1;
    CheckBusy();            //check the LCD busy or not.
    LCD_ENA = 0;
    LCD_RW = 0;
    LCD_RS  = 1;

    LCD_BusData(dat);
    LCD_DelayNop();
    LCD_ENA = 1;
    LCD_DelayNop();
    LCD_ENA = 0;
    LCD_BusData(0xff);
}


//========================================================================
// 函数: void Initialize_LCD(void)
// 描述: 初始化函数
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void Initialize_LCD(void)
{
    LCD_ENA = 0;
    LCD_RS  = 0;
    LCD_RW = 0;

    delay_ms(100);
    IniSendCMD(C_BIT8);     //set the data is 8 bits

    delay_ms(10);
    Write_CMD(C_L2DOT7);        //tow lines 5*7 dots

    delay_ms(6);
    Write_CMD(C_CLEAR);     //clear LCD RAM
    Write_CMD(C_CUR_R);     //Curror Shift Right
    Write_CMD(C_ON);        //turn on  LCD
}



//========================================================================
// 函数: void ClearLine(u8 row)
// 描述: 清除1行
// 参数: row: 行(0或1)
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void ClearLine(u8 row)
{
    u8 i;
    Write_CMD(((row & 1) << 6) | 0x80);
    for(i=0; i<LineLength; i++) Write_DIS_Data(' ');
}

//========================================================================
// 函数: void   WriteChar(u8 row, u8 column, u8 dat)
// 描述: 指定行、列和字符, 写一个字符
// 参数: row: 行(0或1),  column: 第几个字符(0~15),  dat: 要写的字符.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void    WriteChar(u8 row, u8 column, u8 dat)
{
    Write_CMD((((row & 1) << 6) + column) | 0x80);
    Write_DIS_Data(dat);
}


/* ***************************************************** */
// 函数名称：Dispaly_1602()
// 函数功能：1602的显示函数
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void Dispaly_1602(void)
{
    uChar8 str[] = "fsmcu.taobao.com";      //液晶第一行显示的字符串
		LCD_Init();                         //初始化液晶
		InitLcdCn(tab);                     //初始化汉字显示也就是操作CGRAM
		LcdShowStr(0, 0, str);                //设置显示地址和内容
		LcdShowStr(0,1,"2015-08-30  25`C");   //第二行显示时间和温度
		LcdShowCn(4, 1, 0);		 			 //显示  ‘年’
		LcdShowCn(7, 1, 1);		 			 //显示  ‘月’
		LcdShowCn(10, 1, 2);				 //显示  ‘日’
		LcdShowCn(14, 1, 3);	 			 //显示  ‘。c’
		while(1);		
}

/* *********************************** End of File *********************************** */