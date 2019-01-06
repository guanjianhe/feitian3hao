
#ifndef	__FsBSP_AllLedFlash_H__
#define	__FsBSP_AllLedFlash_H__

#include "stc15_gpio.h"

sbit N_rLed = P7^0;		// ���ߺ�ɫָʾ��
sbit N_yLed = P7^1;		// ���߻�ɫָʾ��
sbit N_gLed = P7^2;		// ������ɫָʾ��

sbit E_rLed = P7^3;		// ���ߺ�ɫָʾ��
sbit E_yLed = P7^4;		// ���߻�ɫָʾ��
sbit E_gLed = P7^5;		// ������ɫָʾ��

sbit S_rLed = P7^6;		// �ϱߺ�ɫָʾ��
sbit S_yLed = P7^7;		// �ϱ߻�ɫָʾ��
sbit S_gLed = P5^4;		// �ϱ���ɫָʾ��

sbit W_rLed = P5^5;		// ���ߺ�ɫָʾ��
sbit W_yLed = P3^6;		// ���߻�ɫָʾ��
sbit W_gLed = P3^7;		// ������ɫָʾ��

//void AllLedFlash(void);

#endif

