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
#include "FsBSP_Delay.h"
#include <intrins.h>

/* *******˵��(ѡ�������õ�����)****************
*1.���λ���Ƶ�һ��
*2.���������˼�Ǵӵ�һ�п�ʼ������ѡ�е�1...8��
********************************************* */
uChar8 code ColArr[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
/* ********��ͼ��1******************************
* ���������ڴ洢ͼ��
* ȡ����ʽ ����ȡ�� ��ʽ�����µ���
********************************************* */
uChar8 RowArr[8] = {0x1C,0x22,0x42,0x84,0x84,0x42,0x22,0x1C};


/* ******************************************************************
 * �������ƣ�void LedScreen_WrTwoByte(unsigned char SEGDat,unsigned char COMDat)
 * ��ڲ�����unsigned char SEGDat,unsigned charCOMDat 
 * ���ڲ�������
 * �������ܣ���LedScreen��д�������ֽ�
****************************************************************** */
void LedScreen_WrTwoByte(unsigned char SEGDat,unsigned char COMDat)
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
/* ******************************************************************
 * �������ƣ�LedScreenDis()
 * ��ڲ�������
 * ���ڲ�������
 * �������ܣ�LedScreenDis()������ʾ����������ɵĵ�������-��������ȡģ������
****************************************************************** */
void LedScreenDis()
{
	unsigned char j;
	for(j=0;j<8;j++)
	{
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]);
		DelayMS(1);                                 //��ʱ����������Ϊ����ˢ�µ�Ƶ�ʣ�̫�컭����ʾ̫�죬̫���ж�������
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]);
		DelayMS(1);
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]);
		DelayMS(1);			
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]); 
		DelayMS(1);
		
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]); 
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]); 
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]);		
		LedScreen_WrTwoByte(ColArr[j],RowArr[j]);
	}
}
/* ******************************************************************
 * �������ƣ�Up_Move_Dis(void)
 * ��ڲ�������
 * ���ڲ�������
 * �������ܣ���ǰ����������ʾ����ҪLedScreenDis()�Ӻ������
****************************************************************** */
void Up_Move_Dis(void)
{
	uChar8 iCtr;
	for(iCtr = 0; iCtr < 8; iCtr++)
	{
		RowArr[iCtr] = _cror_(RowArr[iCtr],1);	
		LedScreenDis();
	}
	DelayMS(30);						//��ʱ����������Ϊ����ˢ�µ�Ƶ�ʣ�̫�컭����ʾ̫�죬̫���ж�������
}
/* ***************************************************** */
// �������ƣ�Down_Move_Dis(void)
// �������ܣ���ǰ����������ʾ,��ҪLedScreenDis()�Ӻ������
// ��ڲ�������
// ���ڲ�������
/* ***************************************************** */
void Down_Move_Dis(void)
{
	uChar8 iCtr;  
	for(iCtr = 0; iCtr < 8; iCtr++)
	{
		RowArr[iCtr] = _crol_(RowArr[iCtr],1);	
		LedScreenDis();
	}
	DelayMS(30);						//��ʱ����������Ϊ����ˢ�µ�Ƶ�ʣ�̫�컭����ʾ̫�죬̫���ж�������
}
