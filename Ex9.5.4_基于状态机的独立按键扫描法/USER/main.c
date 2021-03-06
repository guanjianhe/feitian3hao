/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : 基于状态机的独立按键扫描法
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
#include "FsBSP_Key.h"
#include "FsBSP_AllLedFlash.h"

/* ***************************************************** */
// 函数名称：main()
// 函数功能：扫描按键并做出相应LED灯亮灭动作
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void main(void)
{
	LedGPIO_Init();                    //初始化所用端口设置为准双向口
	SingleKey_Init();
	while(1)
	{
		if(0 == K2)	   			// 检测按键是否按下
		{
			DelayMS(5);	 			// 延时去抖
			if(0 == K2)	  		// 再次检测
			{
				P70 = 0;   		// 点亮LED灯
				while(!K2);		// 等待按键弹起
			}
		}
		if(!K3)
		{
			DelayMS(5);
			if(!K3)
			{
				P70 = 1;
				while(!K3);
			}
		}
	}
}

/* *********************************** End of File *********************************** */
