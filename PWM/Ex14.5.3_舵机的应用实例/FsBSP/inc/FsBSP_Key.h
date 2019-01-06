#ifndef	__FsBSP_KEY_H__
#define	__FsBSP_KEY_H__

#include "BSP_Include.h"


sbit KEY0   =   P4^0; //设置KEY0 =0 则可以k2，k3，k4，k5组成四个独立按键
sbit KeyInc =   P4^4;      
sbit KeyDec =   P4^5;



extern void SingleKey_Init(void);
extern void KeyScan(void);

#endif