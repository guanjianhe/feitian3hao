/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : STC15_Timer.c
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-08-12
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * �ļ�˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, ��ƽ��xymbmcu@163.com��/�廪��ѧ������/STC MCU Limited
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#include	"STC15_Timer.h"

u16 g_uiCnt_Time = 0;		//ʱ��Ϊ10us����һ��
extern bit g_bProgmOK;		//���ؼ��OK��׼λ
bit g_bKeyScanFlag = 0;		//����ɨ���־λ

/********************* Timer0�жϺ���************************/
void Timer0_ISR (void) interrupt TIMER0_VECTOR
{
	g_uiCnt_Time++;		// ʱ���׼��ÿ��10us��һ�Σ�
}

/********************* Timer1�жϺ���************************/
void Timer1_ISR (void) interrupt TIMER1_VECTOR
{

}

/********************* Timer2�жϺ���************************/
void Timer2_ISR (void) interrupt TIMER2_VECTOR
{
	static u8 uOkPowOnTime = 0;		// ���ؼ��OK�������ļ��ʱ�䣬ÿ��20ms��һ��
	static bit TempFlag = 0;		// ����֮�󵽿��ⲿ�жϵı�־λ
	static u8 uPowOnInt4Time = 0;	// ����֮�󵽿��ⲿ�жϵ�ʱ�䣬ÿ��20ms��һ��
	
	g_bKeyScanFlag = 1;
	
	if(g_bProgmOK)					// ��⵽����OK֮��ʼ����Ĳ���
	{
		g_bProgmOK = 0;				// ����OK��־λ����
		uOkPowOnTime++;				// ��������ÿ��20ms��һ��
		if(uOkPowOnTime == 20)		// ���20*20ms����,��...
		{
			uOkPowOnTime = 0;
			OnOff_IO = 1;			// �ߵ�ƽ,����(ʵ���Զ�������Դ)
			TempFlag = 1;			// ��λ��־λ
		}
	}
	
	if(TempFlag)					// ����֮�󣬱�־�Ѿ���λ
	{
		uPowOnInt4Time++;			// �����󣬴������ÿ��20ms��һ��
		if(100 == uPowOnInt4Time)	// ��������ʱ����ֹ�󴥷�
		{
			uPowOnInt4Time = 0;
			TempFlag = 0;			// �����־λ
			INT_CLKO |= 0x40;		// �����ⲿ�ж�4
		}
	}
}

/********************* Timer3�жϺ���************************/
void timer3_int (void) interrupt TIMER3_VECTOR
{

}

/********************* Timer4�жϺ���************************/
void timer4_int (void) interrupt TIMER4_VECTOR
{

}

//========================================================================
// ����: uint8	Timer_Inilize(uint8 TIM, TIM_InitTypeDef *TIMx)
// ����: ��ʱ����ʼ������.
// ����: TIMx: �ṹ����,��ο�timer.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2012-10-22
//========================================================================
u8 Timer_Inilize(uint8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer4)	return 1;	//�ղ���

	if(TIM == Timer0)
	{
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//����
		TR0 = 0;		//ֹͣ����
		ET0 = 0;	//��ֹ�ж�
		PT0 = 0;	//�����ȼ��ж�
		TMOD &= 0xf0;	//��ʱģʽ, 16λ�Զ���װ
		AUXR &= ~0x80;	//12Tģʽ, 
		INT_CLKO &= ~0x01;	//�����ʱ��
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//�����ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//�����ȼ��ж�
		TMOD |= TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x01;	//���ʱ��
		
		TH0 = (u8)(TIMx->TIM_Value >> 8);
		TL0 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer1)
	{
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//����
		TR1 = 0;	//ֹͣ����
		ET1 = 0;	//��ֹ�ж�
		PT1 = 0;	//�����ȼ��ж�
		TMOD &=  0x0f;	//��ʱģʽ, 16λ�Զ���װ
		AUXR &= ~0x40;	//12Tģʽ, 
		INT_CLKO &= ~0x02;	//�����ʱ��
		if(TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//�����ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//�����ȼ��ж�
		TMOD |= (TIMx->TIM_Mode << 4);	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x02;	//���ʱ��
		
		TH1 = (u8)(TIMx->TIM_Value >> 8);
		TL1 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer2)		//Timer2,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		AUXR &= ~0x1c;		//ֹͣ����, ��ʱģʽ, 12Tģʽ
		IE2  &= ~(1<<2);	//��ֹ�ж�
		INT_CLKO &= ~0x04;	//�����ʱ��
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<2);	//�����ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x04;	//���ʱ��

		TH2 = (u8)(TIMx->TIM_Value >> 8);
		TL2 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer3)		//Timer3,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		T4T3M &= 0xf0;		//ֹͣ����, ��ʱģʽ, 12Tģʽ, �����ʱ��
		IE2  &= ~(1<<5);	//��ֹ�ж�
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<5);	//�����ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T4T3M |=  (1<<1);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T4T3M |=  (3<<1);	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	T4T3M |=  1;	//���ʱ��

		TH3 = (u8)(TIMx->TIM_Value >> 8);
		TL3 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	T4T3M |=  (1<<3);	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer4)		//Timer4,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		T4T3M &= 0x0f;		//ֹͣ����, ��ʱģʽ, 12Tģʽ, �����ʱ��
		IE2  &= ~(1<<6);	//��ֹ�ж�
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<6);	//�����ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T4T3M |=  (1<<5);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T4T3M |=  (3<<5);	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	T4T3M |=  (1<<4);	//���ʱ��

		TH4 = (u8)(TIMx->TIM_Value >> 8);
		TL4 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	T4T3M |=  (1<<7);	//��ʼ����
		return	0;		//�ɹ�
	}

	return 2;	//����
}
