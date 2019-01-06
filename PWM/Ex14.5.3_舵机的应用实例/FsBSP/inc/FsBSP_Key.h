#ifndef	__FsBSP_KEY_H__
#define	__FsBSP_KEY_H__

#include "BSP_Include.h"


sbit KEY0   =   P4^0; //����KEY0 =0 �����k2��k3��k4��k5����ĸ���������
sbit KeyInc =   P4^4;      
sbit KeyDec =   P4^5;



extern void SingleKey_Init(void);
extern void KeyScan(void);

#endif