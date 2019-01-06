#ifndef __FsBSP_Timer_H__
#define __FsBSP_Timer_H__

#include "STC15.h"

extern bit flagBuzzAndLedOn;

sbit BUZZ = P2^1;  //蜂鸣器控制引脚
sbit LED = P7^0;   //LED灯D9的控制引脚

extern void Timer0_1ms();

#endif