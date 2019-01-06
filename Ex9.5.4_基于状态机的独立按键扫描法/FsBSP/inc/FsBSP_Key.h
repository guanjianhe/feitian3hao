#ifndef	__FsBSP_KEY_H__
#define	__FsBSP_KEY_H__

#include "STC15.h"


#define uChar8 unsigned char
#define uInt16 unsigned int



sbit KEY0 = P4^0; //设置KEY0 =0 则可以k2，k3，k4，k5组成四个独立按键
sbit K2 = P4^4;
sbit K3 = P4^5;

extern void SingleKey_Init(void);


#endif