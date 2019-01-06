#ifndef	__FsBSP_HC595_H__
#define	__FsBSP_HC595_H__

#include "STC15.h"

#define uInt16 unsigned int
#define uChar8 unsigned char

sbit smgSER = P5^0;		// 595（14脚）SER  数据输入引脚
sbit RCK = P5^2;		// 595（12脚）STCP 锁存时钟 1个上升沿所存一次数据
sbit SCK = P5^3;		// 595（11脚）SHCP 移位时钟 8个时钟移入一个字节

extern unsigned char LedBuff[6];
extern unsigned char  Bit_Tab[];
extern unsigned char  Disp_Tab[];

extern unsigned char code SMG_Array[];
extern void Display(uChar8 ucVal);
extern void HC595_WrOneByte(unsigned char ucDat);

#endif