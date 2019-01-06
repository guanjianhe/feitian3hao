/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : stc15_exti.c
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-08-29
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, ��ƽ��xymbmcu@163.com��/�廪��ѧ������/STC MCU International Limited
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#include	"stc15_exti.h"

extern u8 g_uIR_Time;	//������stc15_timer.c �ж���

bit g_IR_OK;			//������ɱ�־λ
bit g_IR_Pro_OK;		//���ݴ�����ɱ�־λ
u8  xdata g_IRcord[4];  	//�����ĺ����룬�ֱ��� �ͻ��룬�ͻ��룬�����룬�����뷴��
u8  xdata HL_LevelPeriodArr[33]; //33���ߵ͵�ƽ������

void IrcordPro(void)
{ 
  	u8 uiVal,ujVal;
  	u8 ByteVal;				// һ���ֽڣ������ַ�롢���ݷ���ȣ�
  	u8 CordVal;				// ��ʱ��Ÿߵ͵�ƽ����ʱ��
	u8 uCounter;			// ��Ӧ33������
	uCounter = 1;				// ������Ϊ���ж����ݣ���ʾ�ܿ���һ�������룬ֱ�Ӵӡ�1����ʼ
	for(uiVal = 0;uiVal < 4;uiVal++)      	// ����4���ֽڣ������ǵ�ַ�롢��ַ���롢//�����롢���ݷ���
	{
		for(ujVal = 0;ujVal < 8;ujVal++) 	// ����1���ֽڵ�8λ
		{
			CordVal = HL_LevelPeriodArr[uCounter];
			// ���ݸߵ͵�ƽ����ʱ��ĳ������ж��ǡ�0�������ǡ�1�� ��0��->1.12ms  ��1��->2.25ms
			// ����Ϊ���жϣ�ȡ1.12��2.25���м�ֵ��1.685Ϊ�жϱ�׼
			// 1.685ms/(256*12/11.0592)us��6 ��ֵ������һ�����
			if(CordVal > 6)				// ����1.685ms��Ϊ�߼���1��	
				ByteVal = ByteVal | 0x80;
			else 						// С��1.685ms��Ϊ�߼���0��
				ByteVal = ByteVal;
			if(ujVal < 7)				// ǰ���7����Ҫ�ƣ���8�β����ľͲ����ˣ��Ѿ������λ�ˣ�
			{							// ��NECЭ���֪��LSB��ǰ�����Բ�����һλ�������һλ
				ByteVal >>= 1;			// �������Ȳ�����LSBλ�ͷ��������ݵ����λ
			}
			uCounter++;					// ���δ�����32λ
		}
		g_IRcord[uiVal] = ByteVal;		// ������õ��ĸ��ֽڷֱ�浽��ֵg_IRcord��
		ByteVal = 0;					// �塰0�����Ա㴢����һ�ֽ�     
	} 
}

/********************* INT0�жϺ��� *************************/
void Ext_INT0 (void) interrupt INT0_VECTOR		//���ж�ʱ�Ѿ������־
{
	static u8 uCounter;				// 1��������+32��λ��16λ��ַ��+16λ����λ������33λ
	static bit StartFlag;           	// �Ƿ�ʼ�����־λ����1����ʼ����0��δ��ʼ��
	EX0 = 0;							// �ر��жϣ���ֹ����
	if(!StartFlag)						// �״ν���StartFlagΪ��0��,��ִ��if���
	{
		g_uIR_Time = 0;					// �������ֵ�塰0��
		StartFlag = 1;					// ��ʼ������־λ�á�1��
	}
	else if(StartFlag)					// ��2~34�ν���ִ�д�if���                         
	{
		if(g_uIR_Time < 50 && g_uIR_Time >= 32)		// �����룬9ms+4.5ms
			uCounter = 0;
		/* 9ms/(256*12/11.0592)us��32   9+4.5ms/(256*12/11.0592)us��50 */
		HL_LevelPeriodArr[uCounter] = g_uIR_Time;	// �洢ÿ����ƽ�����ڣ������Ժ��ж���0����1
		g_uIR_Time = 0;								// �塰0�����Ա����һ�����ڵ�ʱ��
		uCounter++;									// ���δ�����33������
		if(33 == uCounter)
		{
			g_IR_OK = 1;								// ������ɱ�־λ�á�1������ʾ����OK
			uCounter = 0;
			StartFlag = 0;
		}
	}
	EX0 = 1;							// �������жϣ��Ա������һ����ֵ
}

/********************* INT1�жϺ��� *************************/
void Ext_INT1 (void) interrupt INT1_VECTOR		//���ж�ʱ�Ѿ������־
{
	;
}

/********************* INT2�жϺ��� *************************/
void Ext_INT2 (void) interrupt INT2_VECTOR	//
{
	;
}

/********************* INT3�жϺ��� *************************/
void Ext_INT3 (void) interrupt INT3_VECTOR
{
	;
}

/********************* INT4�жϺ��� *************************/
void Ext_INT4 (void) interrupt INT4_VECTOR
{
	;
}

//========================================================================
// ����: u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
// ����: �ⲿ�жϳ�ʼ������.
// ����: INTx: �ṹ����,��ο�Exti.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2012-10-22
// ע�⣺���� �½����ж�ֻ����INT0 1; INT234���������ж���,��Ϊ�ǹ̶����½���
//========================================================================
u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
{
	if(EXT >  EXT_INT4)	return 1;	//�ղ���
	
	if(EXT == EXT_INT0)	//���ж�0
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX0 = 1;	//�����ж�
		else									EX0 = 0;	//��ֹ�ж�
		if(INTx->EXTI_Polity == PolityHigh)		PX0 = 1;	//�����ȼ��ж�
		else									PX0 = 0;	//�����ȼ��ж�
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT0 = 1;	//�½����ж�
		else									IT0 = 0;	//����,�½����ж�
		return	0;		//�ɹ�
	}

	if(EXT == EXT_INT1)	//���ж�1
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX1 = 1;	//�����ж�
		else									EX1 = 0;	//��ֹ�ж�
		if(INTx->EXTI_Polity == PolityHigh)		PX1 = 1;	//�����ȼ��ж�
		else									PX1 = 0;	//�����ȼ��ж�
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT1 = 1;	//�½����ж�
		else									IT1 = 0;	//����,�½����ж�
		return	0;		//�ɹ�
	}

	if(EXT == EXT_INT2)		//���ж�2, �̶�Ϊ�½��ص����ȼ��ж�
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 4);	//�����ж�	
		else								INT_CLKO &= ~(1 << 4);	//��ֹ�ж�
		return	0;		//�ɹ�
	}

	if(EXT == EXT_INT3)		//���ж�3, �̶�Ϊ�½��ص����ȼ��ж�
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 5);	//�����ж�	
		else								INT_CLKO &= ~(1 << 5);	//��ֹ�ж�
		return	0;		//�ɹ�
	}

	if(EXT == EXT_INT4)		//���ж�4, �̶�Ϊ�½��ص����ȼ��ж�
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 6);	//�����ж�	
		else								INT_CLKO &= ~(1 << 6);	//��ֹ�ж�
		return	0;		//�ɹ�
	}
	return 2;	//ʧ��
}
