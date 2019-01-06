/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : RTX51_Traffic.c
 * �ļ����� : RTX51 Tiny + ��ͨ��
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-09-12
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, �����������ӿƼ����޹�˾/�廪��ѧ������
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#include "BSP_Include.h"
#include <rtx51tny.h>
#include "RTX51_Traffic.h"

u8 g_ucGreTime = 24;	// �ϱ�����������ͬ�е�ʱ�䣬���̵���Ϊ׼
u8 g_ucYleTime = 5;		// �Ƶ�����ʱ��
bit g_bDirFlag = 0;		// �ϱ�ͨ���붫��ͨ�з����л���־λ Ĭ��Ϊ�ϱ�ͨ��
bit g_bYledFlag = 0;	// �Ƶ������־λ

/******************************************************************************/
/*        Task 0 'TaskInit': Initialize                                       */
/******************************************************************************/
void TaskInit (void) _task_ INIT_ID   /* program execution starts here        */
{       
	GPIO_ConfigInit();
	
	os_create_task(SMG_ID);
	os_create_task(LED_ID);
	os_create_task(Time_ID);
	
	os_delete_task (INIT_ID);           
	/* stop init task (no longer needed)    */
}
/* ********************************************************
/* �������ƣ�TaskSmg()									 
/* �������ܣ�SMG_ID�������������Ϊ��1��					 
/* ��ڲ�������						 
/* ���ڲ�������										
******************************************************** */
void TaskSmg (void) _task_ SMG_ID
{
	u8 ShiNum,GeNum;
	
	while(1)
	{
		if(!g_bYledFlag)
		{
			GeNum  = g_ucGreTime % 10;			// �����λ��
			ShiNum = g_ucGreTime /10;			// ˢ�»Ƶ�����ʱ��
		}
		else
		{
			GeNum  = g_ucYleTime % 10;			// �����λ��
			ShiNum = g_ucYleTime /10;			// ˢ���̵�����ͨ��ʱ��
		}
		
		P6 = 0xBF;
		HC595_WrOneByte(Disp_Tab[ShiNum]);
		HC595_WrOneByte(0x00);
		P6 = 0x7F;							// ��λѡ����
		HC595_WrOneByte(Disp_Tab[GeNum]);	// �Ͷ�ѡ����
		HC595_WrOneByte(0x00);				// ������Ӱ����
	}
}
/* ********************************************************
/* �������ƣ�TaskLed()									 
/* �������ܣ�SMG_ID�������������Ϊ��2��					 
/* ��ڲ�������						 
/* ���ڲ�������										
******************************************************** */
void TaskLed (void) _task_ LED_ID
{
	while(1)
	{
		if(!g_bDirFlag)					// g_bDirFlag = 0�����ϱ�ͨ��
		{
			if(!g_bYledFlag)
			{
				N_rLed = S_rLed = 1;	// �ϱ������
				N_gLed = S_gLed = 0;	// �ϱ��̵���
				N_yLed = S_yLed = 1;	// �ϱ������
			}
			else
			{
				N_rLed = S_rLed = 1;	// �ϱ������
				N_gLed = S_gLed = 1;	// �ϱ��̵���
				N_yLed = S_yLed = 0;	// �ϱ��Ƶ���				
			}

			E_rLed = W_rLed = 0;		// ���������
			E_gLed = W_gLed = 1;		// �����̵���
			E_yLed = W_yLed = 1;		// �����Ƶ���	
		}
		else							// g_bDirFlag = 1������ͨ��
		{
			N_rLed = S_rLed = 0;		// ���ϱ�ͨ�з���ͬ��
			N_gLed = S_gLed = 1;
			N_yLed = S_yLed = 1;
			
			if(!g_bYledFlag)
			{
				E_rLed = W_rLed = 1;
				E_gLed = W_gLed = 0;
				E_yLed = W_yLed = 1;
			}
			else
			{
				E_rLed = W_rLed = 1;
				E_gLed = W_gLed = 1;
				E_yLed = W_yLed = 0;	
			}
		}
	}
}
/* ********************************************************
/* �������ƣ�TaskTime()									 
/* �������ܣ�SMG_ID�������������Ϊ��3��					 
/* ��ڲ�������						 
/* ���ڲ�������										
******************************************************** */
void TaskTime (void) _task_ Time_ID
{
	static u16 nTime = 0;
	
	while(1)
	{
		os_wait(K_TMO,200,0);		// �ȴ�200���δ�
		nTime++;					// ÿ��(12/11059200)*50*200ʱ�䣬nTime��һ��
		if(108 == nTime)			// (12/11059200)*50*200*108 �� 1S
		{
			nTime = 0;				// ������������
			if(!g_bYledFlag)		// g_bYledFlag = 0��ͨ��״̬
			{
				g_ucGreTime--;		// ͨ��ʱ�����g_ucGreTimeÿ��һ��ݼ�һ
				if(g_ucGreTime == 0)// g_ucGreTime = 0������ͨ��ʱ�䵽
				{
					g_bYledFlag = 1;// �л����Ƶ���ģʽ
					g_ucGreTime = 24;// g_ucGreTime���¸���ʼֵ
				}
			}
			else					// g_bYledFlag = 1���Ƶ���״̬
			{
				g_ucYleTime--;		// �Ƶ���״̬��ʱ�����g_ucYleTimeÿ��һ��ݼ�һ
				if(0 == g_ucYleTime)// g_ucYleTime = 0�������Ƶ���ʱ�䵽
				{
					g_ucYleTime = 5;// ���¸���ʼֵ
					g_bDirFlag = ~g_bDirFlag;	// �л�ͨ�з���
					g_bYledFlag = 0;			// �л����Ƶ���״̬
				}
			}
		}
	}
}
/* *********************************** End of File *********************************** */
