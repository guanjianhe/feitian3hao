/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : 红外解码 + 数码管
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-09-14
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "BSP_Include.h"

#define BAUDRATE 9600

u8 t, r;
u8 xdata Buf[256];

extern bit TxSta;			// 发送开始标志位
extern bit TxEnd,RxEnd;		// 发送、接收结束标志位
extern u8 TxBuf,RxBuf;		// 待发送、接收缓冲数据

void Timer_ConfigInit(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//结构定义
	
	u16 Timer0InitVal;
	Timer0InitVal = (65536 - MAIN_Fosc / BAUDRATE / 4);		//计算初始值,以4倍的采样率进行采样

	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload
	TIM_InitStructure.TIM_Polity    = PolityHigh;			//指定中断优先级, PolityHigh
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//中断是否允许,   ENABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//指定时钟源,     TIM_CLOCK_1T
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, DISABLE
	TIM_InitStructure.TIM_Value     = Timer0InitVal;		//初值
	TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//初始化Timer0
}

void main(void)
{
	Delay_ms(10);		// 待上电稳定
	EA = 1;				// 开总中断
	Timer_ConfigInit();	// 初始化定时器
	USART_Init();		// 初始化变量
	
	for(;;)
	{
        if(RxEnd)					// 接收完成，等到存数据
        {
            RxEnd = 0;
            Buf[r++] = RxBuf;		// 接收到的数据存到Buf中
        }
        if(TxEnd)
        {
            if (t != r)				// 如果接收到了数据，则 t 不等于 r
            {
                TxEnd = 0;			// 发送结束结束标志位清0，也即开始发送数据
                TxBuf = Buf[t++];	// 发送数据
                TxSta = 1;			// 发送置位，开发发送数据
            }
        }
	}
}

/* *********************************** End of File *********************************** */
