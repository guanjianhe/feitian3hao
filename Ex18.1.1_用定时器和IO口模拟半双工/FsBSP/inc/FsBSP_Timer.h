#ifndef __FsBSP_Timer_H__
#define __FsBSP_Timer_H__

#include "STC15.h"

extern unsigned char i ;					
extern unsigned char uiCounter ; 

extern unsigned int  DecimalPart ;
extern unsigned int  IntegerPart ;
	
extern void Timer0_Init(void);
extern void StopwatchDisplay();

#endif