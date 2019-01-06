#ifndef	__FsBSP_HC595_H__
#define	__FsBSP_HC595_H__

#include  "STC15_CLKVARTYPE.H"

sbit smgSER = P5^0;		// 595（14脚）SER  数据输入引脚
sbit RCK = P5^2;		// 595（12脚）STCP 锁存时钟 1个上升沿所存一次数据
sbit SCK = P5^3;		// 595（11脚）SHCP 移位时钟 8个时钟移入一个字节

extern unsigned char LedBuff[6];
extern unsigned char  Bit_Tab[];
extern unsigned char  Disp_Tab[];

extern bit StopwatchRunning ;  //秒表运行标志
extern bit StopwatchRefresh ;  //秒表计数刷新标志
extern unsigned int DecimalPart ;  //秒表的小数部分
extern unsigned int  IntegerPart ;  //秒表的整数部分

void HC595_WrOneByte(unsigned char ucDat);

#endif