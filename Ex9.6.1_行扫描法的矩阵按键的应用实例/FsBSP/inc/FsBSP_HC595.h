#ifndef	__FsBSP_HC595_H__
#define	__FsBSP_HC595_H__

#include "STC15.h"

#define uInt16 unsigned int
#define uChar8 unsigned char

sbit smgSER = P5^0;		// 595��14�ţ�SER  ������������
sbit RCK = P5^2;		// 595��12�ţ�STCP ����ʱ�� 1������������һ������
sbit SCK = P5^3;		// 595��11�ţ�SHCP ��λʱ�� 8��ʱ������һ���ֽ�

extern unsigned char LedBuff[6];
extern unsigned char  Bit_Tab[];
extern unsigned char  Disp_Tab[];

extern unsigned char code SMG_Array[];
extern void Display(uChar8 ucVal);
extern void HC595_WrOneByte(unsigned char ucDat);

#endif