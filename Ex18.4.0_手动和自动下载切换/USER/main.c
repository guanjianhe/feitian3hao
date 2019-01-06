/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : main.c
 * �ļ����� : ������� + �����
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-09-15
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, �����������ӿƼ����޹�˾/�廪��ѧ������
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#include "BSP_Include.h"

sbit LedModel = P3^4;        	//ģʽ��
sbit KeyOnOff_IO = P3^2;   		//��������

extern bit g_bKeyScanFlag;

typedef enum KeyEnum{StateInit,PrsDownOk,KeyOnOff,KeyModel};    
/* =================  δ���£�       ���£�     ���أ�   ģʽ  ============= */

void Timer_ConfigInit(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//�ṹ����

	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//����ģʽ��TIM_16BitAutoReload
	TIM_InitStructure.TIM_Polity    = PolityLow;			//�ж����ȼ���PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//������ ENABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//ʱ��Դ��TIM_CLOCK_1T
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�������������
	TIM_InitStructure.TIM_Value     = 65425;				//��ֵ����ʱ10us
	TIM_InitStructure.TIM_Run       = ENABLE;				//������ʱ��,ENABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//��ʼ��Timer0
	
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//ʱ��Դ��TIM_CLOCK_12T
	TIM_InitStructure.TIM_Value     = 47104;				//��ֵ����ʱ20ms
	Timer_Inilize(Timer2,&TIM_InitStructure);				//��ʼ��Timer2
}

void Interrupt_ConfigInit(void)
{
	EXTI_InitTypeDef	EXTI_InitStructure;					//�ṹ����
    
	EXTI_InitStructure.EXTI_Polity    = PolityHigh;			//�ж����ȼ�, PolityHigh
	EXTI_InitStructure.EXTI_Interrupt = ENABLE;				//�ж�����,  ENABLE
	Ext_Inilize(EXT_INT4,&EXTI_InitStructure);				//��ʼ��INT0,EXT_INT0
}

void KeyScan(void)   //����ɨ��
{
	static u8 KeyStateTemp=0,KeyTime=0;     //�����������,���ؼ�ʱ,������ʱ
	static bit bModelFlag=1;   				//�Զ����ֶ�����ģʽ�л���־λ
	
	switch (KeyStateTemp)
	{
		case StateInit: 	//δ��״̬
			if(KeyOnOff_IO)
				KeyStateTemp = StateInit;
			else KeyStateTemp = PrsDownOk;
		break;
			
		case PrsDownOk:    	//�а��µ�״̬(״̬δ֪���ж����Ŀ���)
			if(KeyOnOff_IO) KeyStateTemp = StateInit;
			else KeyStateTemp = KeyOnOff;	//��ı����£����뿪�ػ�״̬	
		break;
		
		case KeyOnOff:    	//���ػ�����״̬
			if(KeyOnOff_IO)
			{
				KeyTime = 0;
				OnOff_IO =~ OnOff_IO;		//����һ�Σ��л������͹ػ�
				KeyStateTemp = StateInit;
			}
			else
			{
				KeyTime++;
				if (KeyTime >= 50)			//��������1S(20ms*50)���л���ģʽ״̬
				{
					KeyTime=0;
					KeyStateTemp = KeyModel;
				}
			}
		break;
			
		case KeyModel:		//ģʽ���л����Զ����ػ����ֶ�ģʽ
			bModelFlag =~ bModelFlag;
			if(bModelFlag)		//�Զ�����ģʽ   
			{
				INT_CLKO |= 0x40;     	//�����ⲿ�ж�4
				LedModel = 0;			//ģʽ�������������Զ�����ģʽ
			}
			else 			// �ֶ�ģʽ
			{
				INT_CLKO &= 0xbf;    	//�ر��ⲿ�ж�4
				LedModel = 1;			//ģʽ�Ʋ�����������������ģʽ
			}
			KeyStateTemp = StateInit;
			IE2 &= 0xfb;    //�رն�ʱ��2����ֹ��������ʱ����
		break;
		default:	KeyStateTemp=StateInit;		break;
	}
}

void main(void)
{
	Delay_ms(10);			// ���ϵ��ȶ�
	
	EA = 1;					// �����ж�
	
	GPIO_ConfigInit();		// ��ʼ���˿�
	Timer_ConfigInit();		// ��ʼ����ʱ��
	Interrupt_ConfigInit();	// ��ʼ���ж�
	
	for(;;)
	{
		if(g_bKeyScanFlag == 1)		//�ڶ�ʱ��2������λ��������ÿ��20Sɨ��һ�ΰ���
		{
			g_bKeyScanFlag = 0;
			KeyScan();
		}
		if(KeyOnOff_IO) IE2 |=0x04;  //������ʱ��2
	}
}

/* *********************************** End of File *********************************** */
