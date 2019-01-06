#ifndef	__FsBSP_1602_H__
#define	__FsBSP_1602_H__

#include "STC15.h"

#define  uChar8 unsigned char
#define  uInt16 unsigned int

/* ***************************************************** */
// 位定义
/* ***************************************************** */
sbit RS = P3^3;		//数据/命令选择端(H/L)
sbit RW = P3^4;		//数/写选择端(H/L)
sbit EN = P3^5;		//使能信号

extern uChar8 xdata TAB1[];
extern uChar8 xdata TAB2[];
extern void LcdGPIO_Init(void);
extern void Dispaly_1602(void);

#endif
