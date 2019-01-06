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

/* ***************************************************** */
// �������ƣ�ScanKey(void)
// �������ܣ�ɨ�谴��
// ��ڲ�������
// ���ڲ�������ֵ��num��
/* ***************************************************** */
uChar8 ScanKey(void)
{
	static uChar8 KeyStateTemp = 0,KeyTime = 0;
	uChar8 num;
	bit KeyPressTemp;
	Key0 = 0;
	DelayMS(5);                   //�õ�Ƭ������������ΪSTC15���ٶ�̫����~~
	KeyPressTemp = KEY1;					//��ȡI/O�ڵļ�ֵ
	DelayMS(5);                   //�õ�Ƭ������������ΪSTC15���ٶ�̫����~~
	switch(KeyStateTemp)
	{
		case StateInit:						//������ʼ״̬
			if(!KeyPressTemp)				//���������£�״̬�л���ȷ��̬
				KeyStateTemp = StateAffirm;
			break;
		case StateAffirm:					//����ȷ��̬
			if(!KeyPressTemp)				//�����Ѿ�����
			{
				KeyTime = 0;
				KeyStateTemp = StateSingle;	//�л������δ���̬
			}
			else KeyStateTemp = StateInit; 	//�����ڶ���״̬���л�����ʼ̬
			break;
		case StateSingle:					//��������̬
			if(KeyPressTemp)				//����ʱ��С��1s�Ұ����Ѿ��ͷ�
			{ 
				KeyStateTemp = StateInit;  	//�����ͷţ���ص���ʼ̬
				num++;						//��ֵ��һ
				if(16 == num) 	num = 0;
			}
			else if(++KeyTime > 100)		//����ʱ�����1s(100*10ms)
			{
				KeyStateTemp = StateRepeat;	//״̬�л�������̬
				KeyTime = 0;	
			}
			break;
		case StateRepeat:					//��������̬	
			if(KeyPressTemp) 
				KeyStateTemp = StateInit;	//�����ͷţ������ʼ̬
			else							//����δ�ͷ�
			{
				if(++KeyTime > 10)			//������ʱֵ����100ms��10*10ms��
				{
					KeyTime = 0;	
					num++; 					//��ֵÿ��100ms��һ��
					if(16 == num) 	num = 0;
				}
				break;
			}
			break;
        default:	KeyStateTemp = KeyStateTemp = StateInit; break;
	}
	return num;
}
/* ***************************************************** */
// �������ƣ�ExecuteKeyNum()
// �������ܣ�����ֵ��ִ����Ӧ�Ķ���
// ��ڲ�������
// ���ڲ�������
/* ***************************************************** */
void ExecuteKeyNum(void)
{
	static uChar8 KeyNum = 0;		//������⣺�����static�ܲ���ʡ�ԣ�Ϊ�Σ�
	
	if(TF0)							//��ʱ���Ƿ��������
	{
		TF0 = 0;
		TH0 = 0xDC; 
		TL0 = 0x00;
		KeyNum = ScanKey();			//��KeyScan()�����ķ���ֵ��ֵ��KeyNum��
	}
	switch(KeyNum)
	{
		
		case 0:	g_ucKeyNum = 0; break;
		case 1:	g_ucKeyNum = 1; break;
		case 2:	g_ucKeyNum = 2; break;
		case 3:	g_ucKeyNum = 3; break;
		case 4:	g_ucKeyNum = 4; break;
		case 5:	g_ucKeyNum = 5; break;
		case 6:	g_ucKeyNum = 6; break;
		case 7:	g_ucKeyNum = 7; break;
		case 8:	g_ucKeyNum = 8; break;
		case 9:	g_ucKeyNum = 9; break;
		case 10:	g_ucKeyNum = 10; break;
		case 11:	g_ucKeyNum = 11; break;
		case 12:	g_ucKeyNum = 12; break;
		case 13:	g_ucKeyNum = 13; break;
		case 14:	g_ucKeyNum = 14; break;
		case 15:	g_ucKeyNum = 15; break;
		default:	g_ucKeyNum = 16; break;
	}
	
}
