
#ifndef	__FsBSP_LEDSCREEN_H__
#define	__FsBSP_LEDSCREEN_H__

#include "stc15.h"

#define uInt16 unsigned int
#define uChar8 unsigned char

sbit LedSER = P5^1;	// 595��14�ţ�SER  ������������
sbit RCK = P5^2;		// 595��12�ţ�STCP ����ʱ�� 1������������һ������
sbit SCK = P5^3;		// 595��11�ţ�SHCP ��λʱ�� 8��ʱ������һ���ֽ�

extern void LedScreen_WrTwoByte(unsigned char SEGDat,unsigned char COMDat);
#endif

