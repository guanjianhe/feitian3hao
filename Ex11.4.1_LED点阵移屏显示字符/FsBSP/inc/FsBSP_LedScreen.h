
#ifndef	__FsBSP_LEDSCREEN_H__
#define	__FsBSP_LEDSCREEN_H__

#include "stc15.h"

#define uInt16 unsigned int
#define uChar8 unsigned char

sbit LedSER = P5^1;	// 595（14脚）SER  数据输入引脚
sbit RCK = P5^2;		// 595（12脚）STCP 锁存时钟 1个上升沿所存一次数据
sbit SCK = P5^3;		// 595（11脚）SHCP 移位时钟 8个时钟移入一个字节

extern void LedScreen_WrTwoByte(unsigned char SEGDat,unsigned char COMDat);
#endif

