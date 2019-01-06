/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : FsBSP_LedScreen.c
 * �ļ����� : FsSTC15�������ſ������������������
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-09-04
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 
 * Copyright (C), 2014-2015, �����������ӿƼ����޹�˾
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#include "FsBSP_LedScreen.h"
#include <intrins.h>

/* ******************************************************************
 * �������ƣ�LedScreen_WrOneByte(unsigned char ucDat)
 * ��ڲ�����unsigned char SEGDat,unsigned charCOMDat 
 * ���ڲ�������
 * �������ܣ���LedScreen��д��һ���ֽ�
****************************************************************** */
void LedScreen_WrOneByte(unsigned char SEGDat,unsigned char COMDat)
{
	unsigned char i = 0;
	unsigned char j = 0;
	/* ͨ��8ѭ����8λ����һ�������һ��595 */
	for(i=0;i<8;i++)
	{
		LedSER = (bit)(SEGDat & 0x80);
		SCK = 0;
		SEGDat <<= 1;
		SCK = 1;
	}
	/* ͨ��8ѭ����8λ���ݣ�ͨ�������ķ�ʽ���Ľ����
	SEGDat���ǵ���ĸ��������ݣ�COMDat�ǵ��������������*/
	for(j=0;j<8;j++)
	{
		LedSER = (bit)(COMDat & 0x80);
		SCK = 0;
		COMDat <<= 1;
		SCK = 1;
	}
	/* ���ݲ�����������������أ� */
	RCK = 0;		
	_nop_();
	_nop_();
	RCK = 1;
}
