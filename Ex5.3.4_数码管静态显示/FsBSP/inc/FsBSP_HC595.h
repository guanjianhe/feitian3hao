#ifndef	__FsBSP_HC595_H__
#define	__FsBSP_HC595_H__

#include "STC15.h"

sbit smgSER = P5^0;		// 595��14�ţ�SER  ������������
sbit RCK = P5^2;		// 595��12�ţ�STCP ����ʱ�� 1������������һ������
sbit SCK = P5^3;		// 595��11�ţ�SHCP ��λʱ�� 8��ʱ������һ���ֽ�

extern void HC595_WrOneByte(unsigned char ucDat);

#endif