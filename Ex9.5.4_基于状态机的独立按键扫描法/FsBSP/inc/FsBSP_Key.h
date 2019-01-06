#ifndef	__FsBSP_KEY_H__
#define	__FsBSP_KEY_H__

#include "STC15.h"


#define uChar8 unsigned char
#define uInt16 unsigned int



sbit KEY0 = P4^0; //����KEY0 =0 �����k2��k3��k4��k5����ĸ���������
sbit K2 = P4^4;
sbit K3 = P4^5;

extern void SingleKey_Init(void);


#endif