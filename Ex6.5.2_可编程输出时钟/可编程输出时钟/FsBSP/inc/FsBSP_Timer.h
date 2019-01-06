#ifndef __FsBSP_Timer_H__
#define __FsBSP_Timer_H__

#include "STC15.h"

sbit T0CLKO = P3^5;                          //定时器0的时钟输出脚

#define FOSC 11059200L                       //定义晶振频率为11.0592MHz  


#define F38_4KHz   (65535-FOSC/2/38400)      //1T模式下定义输出38.4KHz的方波


extern void Timer0_InitClock(void);

#endif