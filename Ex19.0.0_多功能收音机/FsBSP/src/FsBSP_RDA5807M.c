/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 ：FsBSP_RDA5807M.c
 * 文件描述 ：RDA5807M收音机驱动源码
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号 ：V1.0 	   					
 * 修改日期 ：2015-09-16
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_RDA5807M.h"

// 待写入RDA5807M寄存器的数据
u8 xdata RDA5807_WrRegDat[8] =
{
   0xd0,0x00,  		// 02H
   0x00,0x00,  		// 03H
   0x00,0x40,  		// 04H
   0x90,0x88,  		// 05H
};
// 待读出RDA5807M寄存器的数据
u8 xdata RDA5807_RdRegDat[4] =
{
   0x00,0x00,  		// 0AH
   0x00,0x00,  		// 0BH
};

/* ***************************************************** */
// 函数名称：RDA5807M_WrReg()
// 函数功能：连续向RDA5807M中写入N个数据
// 入口参数：*p(待写入的数据)，ucLenVal写入数据的个数
// 出口参数：无
/* ***************************************************** */
void RDA5807M_WrReg(u8 *p,u8 ucLenVal)
{
	u8 iCount;	  
	
	IIC_Start();						// 发送开始信号
	InputOneByte(RDA5807M_WrDevAddr);	// 输入器件地址(写操作)   
	IIC_RdAck(); 						// 读应答位
	for(iCount = 0;iCount < ucLenVal;iCount++)
	{
		InputOneByte(*p++);				// 写入数据
		IIC_RdAck(); 					// 读应答位
	}
	IIC_Stop(); 						// 产生停止信号
}

/* ***************************************************** */
// 函数名称：RDA5807M_RdReg()
// 函数功能：连续向RDA5807M读取N个数据
// 入口参数：*p(待读出的数据)，ucLenVal读出数据的个数
// 出口参数：无
/* ***************************************************** */
void RDA5807M_RdReg(u8 *p,u8 ucLenVal)
{
	u8 iCount;	  
	
	IIC_Start();						// 发送开始信号
	InputOneByte(RDA5807M_RdDevAddr);	// 输入器件地址   
	IIC_RdAck(); 						// 读应答位
	for(iCount = 0;iCount < ucLenVal;iCount++)
	{
		*p++ = OutputOneByte();
	   	if(iCount != (ucLenVal - 1))	
			IIC_Ack();    
	}
	IIC_Nack();
	IIC_Stop(); 						// 产生停止信号
}

/* ***************************************************** */
// 函数名称：RDA5807M_PowerOnAndInit()
// 函数功能：给RDA5807M收音机上电，并初始化收音机
// 入口参数：
// 出口参数：
/* ***************************************************** */
void RDA5807M_PowerOnAndInit(void)
{
	Delay_ms(5);
	RDA5807_WrRegDat[0] = 0x00;
	RDA5807_WrRegDat[1] = 0x02;		// 发送软件复位指令
	RDA5807M_WrReg(RDA5807_WrRegDat,2);
	Delay_ms(5);
	RDA5807_WrRegDat[0] = 0xd0;
	RDA5807_WrRegDat[1] = 0x01;		// 为收音机上电，并初始化
	RDA5807M_WrReg(RDA5807_WrRegDat,8);
}

/* ***************************************************** */
// 函数名称：RDA5807M_AutoSeek()
// 函数功能：RDA5807M收音机自动寻台模式
// 入口参数：bit（bUpAndDown），1：向下寻台   0：向上寻台
// 出口参数：
/* ***************************************************** */
void RDA5807M_AutoSeek(bit bUpAndDown)
{
	u16 CurFreqPoint;						//当前工作频点

	RDA5807_WrRegDat[3] &= ~(1 << 4);		//禁用调谐。Tune位清零

	if(bUpAndDown)
		RDA5807_WrRegDat[0] &= ~(1 << 1);	//向下自动寻台
	else
		RDA5807_WrRegDat[0] |= (1 << 1); 	//向上自动寻台

	RDA5807_WrRegDat[0] |= (1 << 0);      	//SEEK位置1，内部自动寻台使能
	RDA5807M_WrReg(RDA5807_WrRegDat,4);		//将设置好的数据写入寄存器

	// 等待STC 标志置位
	while(0 == (RDA5807_RdRegDat[0] & 0x40))
	{
		Delay_ms(20);
		RDA5807M_RdReg(RDA5807_RdRegDat,4);	//获取当前工作频点
	}
	
	Delay_ms(5000);							// 这里的两个延时只是用于调试
	Delay_ms(5000);							// 当自动收到电台时，停顿10S
	
	CurFreqPoint = RDA5807_RdRegDat[0] & 0x03;			//读取的频点为【9:0】
	CurFreqPoint = RDA5807_RdRegDat[1] | (CurFreqPoint << 8);
	CurFreqPoint = CurFreqPoint << 6;					//保存频点的寄存器为【15:9】

	RDA5807_WrRegDat[2] = (CurFreqPoint >> 8) & 0xff;	//保存当前工作频点
	RDA5807_WrRegDat[3] = (CurFreqPoint & 0xff);
}

/* ***************************************************** */
// 函数名称：RDA5807M_AutoSeek()
// 函数功能：设置RDA5807M收音机的声音
// 入口参数：bit（bUpAndDown），1：声音递增   0：声音减小
// 出口参数：
/* ***************************************************** */
void RDA5807M_SetVolume(bit bUpAndDown)
{
	if(bUpAndDown)
	{
		if((RDA5807_WrRegDat[7] & 0x0f) < 0x0f)	// 只有音量不是最大时，才可加
		{
			RDA5807_WrRegDat[0] = 0xd0;
			RDA5807_WrRegDat[1] = 0x01;
			RDA5807_WrRegDat[3] &= ~(1 << 4);	// 禁用调谐。Tune位清零

			RDA5807_WrRegDat[7]++;	 			// 音量递增
			RDA5807M_WrReg(RDA5807_WrRegDat,8);
		}
	}
	else
	{
		if((RDA5807_WrRegDat[7] & 0x0f) > 0x00)	// 只有音量不是最小时，才可减
		{
			RDA5807_WrRegDat[0] = 0xd0;
			RDA5807_WrRegDat[1] = 0x01;
			RDA5807_WrRegDat[3] &= ~(1 << 4);	// 禁用调谐。Tune位清零

			RDA5807_WrRegDat[7]--;	 			// 音量递减
			RDA5807M_WrReg(RDA5807_WrRegDat,8);
		}
	}
}
