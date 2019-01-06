/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : AT24CC02 + 串口
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

#include "BSP_Include.h"

u8 code InputData[4] = {0x12,0x34,0x56,0xab};
u8  OutputData[4] = {0};

static void	UART_ConfigInit(void)
{
	COMx_InitDefine		COMx_InitStructure;					//结构定义	
	       
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//模式,       UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//使用波特率,   BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
	COMx_InitStructure.UART_Interrupt = ENABLE;				//中断允许,   ENABLE或DISABLE
	COMx_InitStructure.UART_Polity    = PolityLow;			//中断优先级, PolityLow,PolityHigh
	COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(必须使用内部时钟)
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;		//内部短路RXD与TXD, 做中继, ENABLE,DISABLE
	USART_Configuration(USART1, &COMx_InitStructure);		//初始化串口1 USART1
	
	EA = 1; 												//开总中断
}

static void AT24C02_Demo(void)
{
	u8 i = 0;
	//u8 *sp;
	IIC_WrDatToAdd(0xa0,0x28,InputData,4);
	Delay_ms(10);
	IIC_RdDatFromAdd(0xa0,0x28,OutputData,4);
	
	#if 0		// 调试用，调试完之后，相当于总闸，直接关闭。
	sp = &InputData[0];
    for(i=0;i<4;i++)
    {
        TX1_write2buff(*sp);
        sp++;
    }    
	
	Delay_ms(10);
	
	sp = &OutputData[0];
    for(i=0;i<4;i++)
    {
        TX1_write2buff(*sp);
        sp++;
    }
	#endif
		
	for(i = 0; i < 4; i++)				// 比较写入和读出的数据是否相同
	{
		if(InputData[i] == OutputData[i])
		{
			PrintString1("\r /* Test OK... */ \r\n" );
			Delay_ms(10);
		}
		else 
		{
			PrintString1("\r /* Test ERROR... */ \r\n" );	
			Delay_ms(10);
		}
	}
}

void main(void)
{
	Delay_ms(100);		// 待上电稳定
	
	UART_ConfigInit();
	GPIO_ConfigInit();
	
	Delay_ms(10);
	PrintString1("\r /* =========================================== */ \r\n" );	Delay_ms(10);
	PrintString1("\r 欢迎使用飛天叁號（FSST15）开发板.............. \r\n" );		Delay_ms(10);
	PrintString1("\r 本开发板配套书籍——《与STC15单片机牵手的那些年》 \r\n" );	Delay_ms(10);
	PrintString1("\r 本开发板配套视频——《深入浅出玩转STC15单片机》 \r\n" );		Delay_ms(10);
	PrintString1("\r /* =========================================== */ \r\n" );	Delay_ms(10);
	
	AT24C02_Demo();
	
	while(1);
}

/* *********************************** End of File *********************************** */
