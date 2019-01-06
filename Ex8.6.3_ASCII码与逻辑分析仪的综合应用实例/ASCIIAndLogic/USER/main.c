/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : ACSII码和逻辑分析仪
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

#include "FsBSP_Delay.h"
#include "FsBSP_Uart.h"

/* ***************************************************** */
// 函数名称：main()
// 函数功能：串口初始化后发广告语再做算术演示
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void main(void)
{
	DelayMS(100);		// 等待开发板上电稳定
	ConfigUART(9600);
	DelayMS(10);		// 等待串口初始化完成
	UART_SendString("\r /* =========================================== */ \r\n" );
	UART_SendString("\r 欢迎使用飛天叁號（FSST15）开发板.............. \r\n" );
	UART_SendString("\r 本开发板配套书籍——《与STC15单片机牵手的那些年》 \r\n" );
	UART_SendString("\r 本开发板配套视频——《深入浅出玩转STC15单片机》 \r\n" );
	UART_SendString("\r /* =========================================== */ \r\n\n" );
	while(1)
	{
		UART_SendDat();
		P7 = UART_RecDat();		// 用8个LED灯来指示接收到的数据，以便观察
	}
}

/* *********************************** End of File *********************************** */
