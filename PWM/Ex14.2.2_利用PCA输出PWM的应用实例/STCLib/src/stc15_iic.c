/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : stc15_iic.c
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-08-29
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 刘平（xymbmcu@163.com）/清华大学出版社/STC MCU International Limited
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include	"stc15_iic.h"

/* ***************************************************** */
// 函数名称：Delay5US()
// 函数功能：5微秒延时,如果自己的主频有变，请自行修改
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void Delay5US(void)		//@11.0592MHz
{
	u8 i;

	_nop_();
	i = 11;
	while (--i);
}

/* ***************************************************** */
// 函数名称：IIC_Start()
// 函数功能：IIC起动
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void IIC_Start(void)
{
	SDA = 1;
	Delay5US();
	SCL = 1;
	Delay5US();
	SDA = 0;
	Delay5US();
}

/* ***************************************************** */
// 函数名称：IIC_Stop()
// 函数功能：IIC停止
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void IIC_Stop(void)                     
{
	SDA = 0;
	Delay5US();
	SCL = 1;
	Delay5US();
	SDA =1;
}

/* ***************************************************** */
// 函数名称：IIC_Ack()
// 函数功能：IIC应答
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void IIC_Ack(void)                      
{ 
	SCL = 0;				// 为产生脉冲准备
	SDA = 0;				// 产生应答信号
	Delay5US();				// 延时你懂得
	SCL = 1;
	Delay5US();  
	SCL = 0;
	Delay5US();		// 产生高脉冲 
	SDA = 1;				// 释放总线
}

/* ***************************************************** */
// 函数名称：IIC_RdAck()
// 函数功能：读IIC应答
// 入口参数：无
// 出口参数：是否应答真值
/* ***************************************************** */
u8 IIC_RdAck(void)                      
{ 
	u8 AckFlag;
	u8 uiVal = 0;
	SCL = 0;
	Delay5US();    
	SDA = 1;
	SCL = 1;
	Delay5US();
	while((1 == SDA) && (uiVal < 255))
	{
		uiVal ++;
		AckFlag = SDA;
	} 
	SCL = 0;  
	return AckFlag;		// 应答返回：0;不应答返回：1
}

/* ***************************************************** */
// 函数名称：IIC_Nack()
// 函数功能：IIC不应答
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void IIC_Nack(void)                    
{   
	SDA = 1;
	SCL = 0;
	Delay5US();      
	SCL = 1;
	Delay5US();      
	SCL = 0;
}

/* ***************************************************** */
// 函数名称：OutputOneByte()
// 函数功能：从IIC器件中读出一个字节
// 入口参数：无
// 出口参数：读出的一个字节（uByteVal）
/* ***************************************************** */
u8 OutputOneByte(void)        
{
	u8 uByteVal = 0;
	u8 iCount;
	SDA = 1;
	for (iCount = 0;iCount < 8;iCount++)
	{
		SCL = 0;
		Delay5US();
		SCL = 1;
		Delay5US(); 
		uByteVal <<= 1;
		if(SDA)
			uByteVal |= 0x01;
	}         
	SCL = 0;
	return(uByteVal);
}

/* ***************************************************** */
// 函数名称：InputOneByte()
// 函数功能：向IIC器件写入一个字节
// 入口参数：待写入的一个字节（uByteVal）
// 出口参数：无
/* ***************************************************** */
void InputOneByte(u8 uByteVal)
{
    u8 iCount;
    for(iCount = 0;iCount < 8;iCount++)
	{  
		SCL = 0;
		Delay5US();			
		SDA = (uByteVal & 0x80) >> 7;
		Delay5US();         
		SCL = 1;
		Delay5US();
		uByteVal <<= 1;
    } 
	SCL = 0;   	  
}

/* ***************************************************** */
// 函数名称：IIC_WrDevAddAndDatAdd()
// 函数功能：向IIC器件写入器件和数据地址
// 入口参数：器件地址（uDevAdd），数据地址（uDatAdd）
// 出口参数：写入是否成功真值
/* ***************************************************** */
u8 IIC_WrDevAddAndDatAdd(u8 uDevAdd,u8 uDatAdd)
{
	IIC_Start();			// 发送开始信号
	InputOneByte(uDevAdd);	// 输入器件地址
	IIC_RdAck();  			// 读应答信号
	InputOneByte(uDatAdd);	// 输入数据地址
	IIC_RdAck();			// 读应答信号
	return TRUE;          
}

/* ***************************************************** */
// 函数名称：IIC_WrDatToAdd()
// 函数功能：向IIC器件写数据
// 入口参数：器件ID(uDevID)、数据存储起始地址(uStaAddVal)
//			 待存数据(*p)、连续存储数据的个数(uiLenVal)
// 出口参数：无
/* ***************************************************** */
void IIC_WrDatToAdd(u8 uDevID, u8 uStaAddVal, u8 *p, u8 ucLenVal)
{      
	u8 iCount;	  
	IIC_WrDevAddAndDatAdd(uDevID | IIC_WRITE,uStaAddVal);  
	// IIC_WRITE 为写命令后缀符                                           
	for(iCount = 0;iCount < ucLenVal;iCount++)
	{
		InputOneByte(*p++);
		IIC_RdAck(); 
	}
	IIC_Stop(); 		
}

/* ***************************************************** */
// 函数名称：IIC_RdDatFromAdd()
// 函数功能：向IIC器件读数据
// 入口参数：器件ID(uDevID)、数据存储地址(uStaAddVal)
//			 待存数据(*p)、连续存储数据的个数(uiLenVal)
// 出口参数：无
/* ***************************************************** */
void IIC_RdDatFromAdd(u8 uDevID, u8 uStaAddVal, u8 *p, u8 uiLenVal)
{                                                    
	u8 iCount;
	IIC_WrDevAddAndDatAdd(uDevID | IIC_WRITE,uStaAddVal);  
	IIC_Start();
	InputOneByte(uDevID | IIC_READ);
	// IIC_READ 为写命令后缀符
	IIC_RdAck();     
	for(iCount = 0;iCount < uiLenVal;iCount++)
	{
		*p++ = OutputOneByte();
	   	if(iCount != (uiLenVal - 1))
			IIC_Ack();      	   
	}       
	IIC_Nack();        
	IIC_Stop();	  
}

