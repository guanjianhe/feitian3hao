/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : 步进电机的应用实例
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-09-09
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */
#include "BSP_Include.h"

unsigned char code MotorArr[8] = 
{0xEF,0xCF,0xDF,0x9F,0xBF,0x3F,0x7F,0x6F};

void Motor(void)
{
    unsigned long ulBeats = 0;
    unsigned char uStep  = 0;
    ulBeats = 20 * 4096;
    while(ulBeats--)
    {
        P2 = MotorArr[uStep];
        uStep++;
        if(8 == uStep)
        uStep = 0;
        DelayMS(5);
    }
}

void main(void)
{
		P2M0 = 0;
		P2M1 = 0;
    while(1)
		{
			Motor();
		}
}

/* *********************************** End of File *********************************** */
