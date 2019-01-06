#ifndef	__FsBSP_1602_H__
#define	__FsBSP_1602_H__

#include "STC15.h"

#define  uChar8 unsigned char
#define  uInt16 unsigned int

/* ***************************************************** */
// λ����
/* ***************************************************** */
sbit RS = P3^3;		//����/����ѡ���(H/L)
sbit RW = P3^4;		//��/дѡ���(H/L)
sbit EN = P3^5;		//ʹ���ź�

extern uChar8 xdata TAB1[];
extern uChar8 xdata TAB2[];
extern void LcdGPIO_Init(void);
extern void Dispaly_1602(void);

#endif
