#ifndef __FsBSP_Timer_H__
#define __FsBSP_Timer_H__

#include "STC15.h"

sbit T0CLKO = P3^5;                          //��ʱ��0��ʱ�������

#define FOSC 11059200L                       //���徧��Ƶ��Ϊ11.0592MHz  


#define F38_4KHz   (65535-FOSC/2/38400)      //1Tģʽ�¶������38.4KHz�ķ���


extern void Timer0_InitClock(void);

#endif