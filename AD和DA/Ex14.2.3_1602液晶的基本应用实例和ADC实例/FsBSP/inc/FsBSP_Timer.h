#ifndef __FsBSP_Timer_H__
#define __FsBSP_Timer_H__

#include "STC15.h"

extern bit flagBuzzAndLedOn;

sbit BUZZ = P2^1;  //��������������
sbit LED = P7^0;   //LED��D9�Ŀ�������

extern void Timer0_1ms();

#endif