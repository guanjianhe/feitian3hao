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
#include "FsBSP_Delay.h"

/* ****************************************************************************
 * �������ƣ�LedGPIO_Init()
 * ��ڲ�������
 * ���ڲ�������
 * �������ܣ���ʼ�����ö˿�����Ϊ׼˫���
**************************************************************************** */
void GPIO_Init(void)
{
    P4M1 = 0;   
	P4M0 = 0;   //����Ϊ׼˫���
}
/* *****************************************************
// �������ƣ�ScanKey()
// �������ܣ����󰴼�ɨ��
// ��ڲ�������
// ���ڲ�������
// �������ܣ�������ɨ�跨�����󰴼�
/* ***************************************************** */
void ScanKey(void)
{
	uChar8 ucTemp;

	KEYPORT = 0xfe;		  			//����һ��
	ucTemp = KEYPORT;	  			//��ȡ���̶˿���ֵ
	if(ucTemp != 0xfe)		 		//���ǲ�����0xF0��ʾ�а�������
	{
		DelayMS(5);                 //ȥ��
		ucTemp = KEYPORT;			//���˿�ֵ
		if(ucTemp != 0xfe)			//�ٴ��ж�
		{
			ucTemp = KEYPORT;		//ȡ��ֵ
			switch(ucTemp)			//�жϼ�ֵ��Ӧ����
			{
				case 0xee:g_ucKeyNum = 0;break;
				case 0xde:g_ucKeyNum = 1;break;
				case 0xbe:g_ucKeyNum = 2;break;
				case 0x7e:g_ucKeyNum = 3;break;        
			}
			while(KEYPORT != 0xfe);	//�����ͷż��
		}
	}	
	KEYPORT = 0xfd;
	ucTemp = KEYPORT;
	if(ucTemp != 0xfd)
	{
		DelayMS(5);
		ucTemp = KEYPORT;
		if(ucTemp != 0xfd)
		{
			ucTemp = KEYPORT;
			switch(ucTemp)
			{
				case 0xed:g_ucKeyNum = 4;break;
				case 0xdd:g_ucKeyNum = 5;break;
				case 0xbd:g_ucKeyNum = 6;break;
				case 0x7d:g_ucKeyNum = 7;break;        
			}
			while(KEYPORT != 0xfd);
		}
	}	
	KEYPORT = 0xfb;
	ucTemp = KEYPORT;
	if(ucTemp != 0xfb)
	{
		DelayMS(5);
		ucTemp = KEYPORT;
		if(ucTemp != 0xfb)
		{
			ucTemp = KEYPORT;
			switch(ucTemp)
			{
				case 0xeb:g_ucKeyNum = 8;break;
				case 0xdb:g_ucKeyNum = 9;break;
				case 0xbb:g_ucKeyNum = 10;break;
				case 0x7b:g_ucKeyNum = 11;break;        
			}
			while(KEYPORT != 0xfb);
		}
	}	
	KEYPORT = 0xf7;
	ucTemp = KEYPORT;
	if(ucTemp != 0xf7)
	{
		DelayMS(5);                   
		ucTemp = KEYPORT;
		if(ucTemp != 0xf7)
		{
			ucTemp = KEYPORT;
			switch(ucTemp)
			{
				case 0xe7:g_ucKeyNum = 12;break;
				case 0xd7:g_ucKeyNum = 13;break;
				case 0xb7:g_ucKeyNum = 14;break;
				case 0x77:g_ucKeyNum = 15;break;        
			}
			while(KEYPORT != 0xf7);
		}
	}
}
