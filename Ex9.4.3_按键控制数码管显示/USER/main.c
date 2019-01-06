/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : 按键控制数码管刷新驱动程序
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-07-19
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 
 * Copyright (C), 2014-2015, 兰州文轩电子科技有限公司
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_HC595.h"
#include "FsBSP_Delay.h"

sbit Key1 = P4^1;
sbit K6   = P4^4;

unsigned char code SMG_Array[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,
0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};  // 0 ~ F

void main(void)
{
	unsigned char ucNum = 0;	// 定义一个计数值，记录按键按下的次数
	
	Key1 = 0;					// 拉低Key1，目的产生独立按键
	P6 = 0x00;					// 使其8位数码管全部有效
	
	while(1)
	{
		if (K6 == 0)			// 检测按键是否按下
		{
			DelayMS(10);		// 延时去抖
			if (0 == K6)		// 判断按键抖动
			{
				while(!K6);		// 等待按键弹起
				ucNum++;
				if(ucNum >= 10)
				{
					ucNum = 0;
				}
				HC595_WrOneByte(SMG_Array[ucNum]);	// 计数值显示在8位数码管上
			}
		}
	}
}

/* *********************************** End of File *********************************** */