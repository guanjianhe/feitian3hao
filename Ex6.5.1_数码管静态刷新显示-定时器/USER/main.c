/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : 数码管动态刷新驱动程序
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-07-05
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 
 * Copyright (C), 2014-2015, 兰州文轩电子科技有限公司
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_HC595.h"
#include "FsBSP_Timer.h"

unsigned char code SMG_Array[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,
0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};  // 0 ~ F

void main(void)
{	
	unsigned char i = 0;					//发送数组的选择位
	unsigned char uiCounter = 0;            //记录定时器溢出次数标志位
	
	Timer0_Init();							//定时器0初始化
	
	P6 = 0x00;								// 使其8位数码管全部有效
	
	while(1)
	{
		if(TF0 == 1)
		{
			TF0 = 0;             //有溢出时要记得清标志位哦
			uiCounter++;         // 记录溢出次数
			if(100 == uiCounter) // 一次 10ms，那 100 次呢？
			{
			   if(i < 16) i++;
			   else i = 0;
			}
			HC595_WrOneByte(SMG_Array[i]);	// 调用函数，依次送入数组中的16个数
		}
	}
}


/* *********************************** End of File *********************************** */