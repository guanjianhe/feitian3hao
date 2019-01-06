/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : FsBSP_Key.c
 * �ļ����� : �����������߾��󰴼�����������
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-08-08
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, �����������ӿƼ����޹�˾/�廪��ѧ������
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#include "FsBSP_Key.h"
#include "STC15.h"
#include "FsBSP_Delay.h"



/* ***************************************************** */
// �������ƣ�ScanKey()
// �������ܣ����󰴼�ɨ��
// ��ڲ�������
// ���ڲ�������
/* ***************************************************** */
void ScanKey(void)
{
  uChar8 RowTemp,ColumnTemp,RowColTemp;
	KEYPORT = 0xf0;			 					// �ȸ�����λ�ߵ�ƽ
	DelayMS(2);										//�õ�Ƭ������������ΪSTC15���ٶ�̫����~~
	RowTemp = KEYPORT & 0xf0;					// ��ȡ��ֵ��Ϊȷ������һ����
	DelayMS(2);										//�õ�Ƭ������������ΪSTC15���ٶ�̫����~~
	if((KEYPORT & 0xf0) != 0xf0)							// �ж��Ƿ��а�������ʱ������ȷ���ǰ��������Ƕ���
	{
		DelayMS(5);								// ȥ����
		if((KEYPORT & 0xf0)!= 0xf0)
		{
			RowTemp = KEYPORT & 0xf0;			// ˵������м����£���ô��ȡ��ֵ
			DelayMS(2);									//�õ�Ƭ������������ΪSTC15���ٶ�̫����~~
			KEYPORT = 0x0f;						// ���Ÿ�����λ�ߵ�ƽ
			DelayMS(2);								//�õ�Ƭ������������ΪSTC15���ٶ�̫����~~
			ColumnTemp = KEYPORT & 0x0f;		// ��ȡ��ֵ��Ϊȷ������һ����
			RowColTemp = RowTemp | ColumnTemp;	// ����ֵ���л����㣬�Ӷ�ȷʵ����ֵ��ȷ��������
			while((KEYPORT & 0x0f) != 0x0f);	// ���ּ��
		}
	}
	switch(RowColTemp)							// ȷ������
	{
		case 0xee:	g_ucKeyNum = 0; break;
		case 0xde:	g_ucKeyNum = 1; break;
		case 0xbe:	g_ucKeyNum = 2; break;
		case 0x7e:	g_ucKeyNum = 3; break;
		case 0xed:	g_ucKeyNum = 4; break;
		case 0xdd:	g_ucKeyNum = 5; break;
		case 0xbd:	g_ucKeyNum = 6; break;
		case 0x7d:	g_ucKeyNum = 7; break;
		case 0xeb:	g_ucKeyNum = 8; break;
		case 0xdb:	g_ucKeyNum = 9; break;
		case 0xbb:	g_ucKeyNum = 10; break;
		case 0x7b:	g_ucKeyNum = 11; break;
		case 0xe7:	g_ucKeyNum = 12; break;
		case 0xd7:	g_ucKeyNum = 13; break;
		case 0xb7:	g_ucKeyNum = 14; break;
		case 0x77:	g_ucKeyNum = 15; break;
		default:	g_ucKeyNum = 16; break;
	}
}