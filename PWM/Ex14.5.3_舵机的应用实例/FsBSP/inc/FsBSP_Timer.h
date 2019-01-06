#ifndef __FsBSP_Timer_H__
#define __FsBSP_Timer_H__

#include "STC15.h"
sbit _PWM = P0^0;
extern unsigned char ucCount;
extern unsigned long uCount;

extern  void Timer0_Init(void);

#endif