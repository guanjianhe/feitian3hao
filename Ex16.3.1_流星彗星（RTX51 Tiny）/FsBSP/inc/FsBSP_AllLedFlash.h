
#ifndef	__FsBSP_AllLedFlash_H__
#define	__FsBSP_AllLedFlash_H__

#include "stc15_gpio.h"

sbit N_rLed = P7^0;		// 北边红色指示灯
sbit N_yLed = P7^1;		// 北边黄色指示灯
sbit N_gLed = P7^2;		// 北边绿色指示灯

sbit E_rLed = P7^3;		// 东边红色指示灯
sbit E_yLed = P7^4;		// 东边黄色指示灯
sbit E_gLed = P7^5;		// 东边绿色指示灯

sbit S_rLed = P7^6;		// 南边红色指示灯
sbit S_yLed = P7^7;		// 南边黄色指示灯
sbit S_gLed = P5^4;		// 南边绿色指示灯

sbit W_rLed = P5^5;		// 西边红色指示灯
sbit W_yLed = P3^6;		// 西边黄色指示灯
sbit W_gLed = P3^7;		// 西边绿色指示灯

//void AllLedFlash(void);

#endif

