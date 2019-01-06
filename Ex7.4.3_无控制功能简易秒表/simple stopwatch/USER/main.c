/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : 简易秒表
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-08-05
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_HC595.h"
#include "FsBSP_Timer.h"

/* ***************************************************** */
// 数组定义
/* ***************************************************** */
unsigned char  Bit_Tab[] = 
{0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};		//位选数组

unsigned char  Disp_Tab[] = 
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};	 	//0~7数字显示编码数组

unsigned char LedBuff[6] = 
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};           //数码管显示缓冲区
    


unsigned char i = 0;					//发送数组的选择位
unsigned char uiCounter = 0;            //记录定时器溢出次数标志位



unsigned int DecimalPart = 0;   //秒表的小数部分
unsigned int IntegerPart = 0;  //秒表的整数部分

void main(void)
{
	
	Timer0_Init();
	
	while(1)
	{
		StopwatchDisplay();
	}

}

/* *********************************** End of File *********************************** */
