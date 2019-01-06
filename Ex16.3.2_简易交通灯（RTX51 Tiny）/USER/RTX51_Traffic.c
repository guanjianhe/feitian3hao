/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : RTX51_Traffic.c
 * 文件描述 : RTX51 Tiny + 交通灯
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-09-12
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "BSP_Include.h"
#include <rtx51tny.h>
#include "RTX51_Traffic.h"

u8 g_ucGreTime = 24;	// 南北、东西方向同行的时间，以绿灯亮为准
u8 g_ucYleTime = 5;		// 黄灯亮的时间
bit g_bDirFlag = 0;		// 南北通行与东西通行方向切换标志位 默认为南北通行
bit g_bYledFlag = 0;	// 黄灯亮灭标志位

/******************************************************************************/
/*        Task 0 'TaskInit': Initialize                                       */
/******************************************************************************/
void TaskInit (void) _task_ INIT_ID   /* program execution starts here        */
{       
	GPIO_ConfigInit();
	
	os_create_task(SMG_ID);
	os_create_task(LED_ID);
	os_create_task(Time_ID);
	
	os_delete_task (INIT_ID);           
	/* stop init task (no longer needed)    */
}
/* ********************************************************
/* 函数名称：TaskSmg()									 
/* 函数功能：SMG_ID任务函数（任务号为：1）					 
/* 入口参数：无						 
/* 出口参数：无										
******************************************************** */
void TaskSmg (void) _task_ SMG_ID
{
	u8 ShiNum,GeNum;
	
	while(1)
	{
		if(!g_bYledFlag)
		{
			GeNum  = g_ucGreTime % 10;			// 分离个位数
			ShiNum = g_ucGreTime /10;			// 刷新黄灯亮的时间
		}
		else
		{
			GeNum  = g_ucYleTime % 10;			// 分离个位数
			ShiNum = g_ucYleTime /10;			// 刷新绿灯亮的通行时间
		}
		
		P6 = 0xBF;
		HC595_WrOneByte(Disp_Tab[ShiNum]);
		HC595_WrOneByte(0x00);
		P6 = 0x7F;							// 送位选数据
		HC595_WrOneByte(Disp_Tab[GeNum]);	// 送段选数据
		HC595_WrOneByte(0x00);				// 消除鬼影现象
	}
}
/* ********************************************************
/* 函数名称：TaskLed()									 
/* 函数功能：SMG_ID任务函数（任务号为：2）					 
/* 入口参数：无						 
/* 出口参数：无										
******************************************************** */
void TaskLed (void) _task_ LED_ID
{
	while(1)
	{
		if(!g_bDirFlag)					// g_bDirFlag = 0，则南北通行
		{
			if(!g_bYledFlag)
			{
				N_rLed = S_rLed = 1;	// 南北红灯灭
				N_gLed = S_gLed = 0;	// 南北绿灯亮
				N_yLed = S_yLed = 1;	// 南北红灯灭
			}
			else
			{
				N_rLed = S_rLed = 1;	// 南北红灯灭
				N_gLed = S_gLed = 1;	// 南北绿灯灭
				N_yLed = S_yLed = 0;	// 南北黄灯亮				
			}

			E_rLed = W_rLed = 0;		// 东西红灯亮
			E_gLed = W_gLed = 1;		// 东西绿灯灭
			E_yLed = W_yLed = 1;		// 东西黄灯灭	
		}
		else							// g_bDirFlag = 1，则东西通行
		{
			N_rLed = S_rLed = 0;		// 和南北通行方向同理
			N_gLed = S_gLed = 1;
			N_yLed = S_yLed = 1;
			
			if(!g_bYledFlag)
			{
				E_rLed = W_rLed = 1;
				E_gLed = W_gLed = 0;
				E_yLed = W_yLed = 1;
			}
			else
			{
				E_rLed = W_rLed = 1;
				E_gLed = W_gLed = 1;
				E_yLed = W_yLed = 0;	
			}
		}
	}
}
/* ********************************************************
/* 函数名称：TaskTime()									 
/* 函数功能：SMG_ID任务函数（任务号为：3）					 
/* 入口参数：无						 
/* 出口参数：无										
******************************************************** */
void TaskTime (void) _task_ Time_ID
{
	static u16 nTime = 0;
	
	while(1)
	{
		os_wait(K_TMO,200,0);		// 等待200个滴答
		nTime++;					// 每过(12/11059200)*50*200时间，nTime加一次
		if(108 == nTime)			// (12/11059200)*50*200*108 ≈ 1S
		{
			nTime = 0;				// 计数变量清零
			if(!g_bYledFlag)		// g_bYledFlag = 0，通行状态
			{
				g_ucGreTime--;		// 通行时间变量g_ucGreTime每过一秒递减一
				if(g_ucGreTime == 0)// g_ucGreTime = 0，表明通行时间到
				{
					g_bYledFlag = 1;// 切换到黄灯亮模式
					g_ucGreTime = 24;// g_ucGreTime从新赋初始值
				}
			}
			else					// g_bYledFlag = 1，黄灯亮状态
			{
				g_ucYleTime--;		// 黄灯亮状态，时间变量g_ucYleTime每过一秒递减一
				if(0 == g_ucYleTime)// g_ucYleTime = 0，表明黄灯亮时间到
				{
					g_ucYleTime = 5;// 从新赋初始值
					g_bDirFlag = ~g_bDirFlag;	// 切换通行方向
					g_bYledFlag = 0;			// 切换到黄灯灭状态
				}
			}
		}
	}
}
/* *********************************** End of File *********************************** */
