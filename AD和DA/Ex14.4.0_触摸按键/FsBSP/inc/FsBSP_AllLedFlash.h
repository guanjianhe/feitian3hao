
#ifndef	__FsBSP_AllLedFlash_H__
#define	__FsBSP_AllLedFlash_H__

#include "stc15.h"


sbit LED9  = P5^4;
sbit LED10 = P5^5;
sbit LED11 = P3^6;
sbit LED12 = P3^7;

void LedGPIO_Init(void);
//void AllLedFlash(void);

#endif

