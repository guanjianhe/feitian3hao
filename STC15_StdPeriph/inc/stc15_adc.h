/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : stc15_adc.h
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-08-30
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * �ļ�˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, ��ƽ��xymbmcu@163.com��/�廪��ѧ������/STC MCU Limited
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#ifndef	__stc15_adc_H
#define	__stc15_adc_H

#include	"STC15_ClkConfig.h"

#define	ADC_P10		0x01	//IO���� Px.0
#define	ADC_P11		0x02	//IO���� Px.1
#define	ADC_P12		0x04	//IO���� Px.2
#define	ADC_P13		0x08	//IO���� Px.3
#define	ADC_P14		0x10	//IO���� Px.4
#define	ADC_P15		0x20	//IO���� Px.5
#define	ADC_P16		0x40	//IO���� Px.6
#define	ADC_P17		0x80	//IO���� Px.7
#define	ADC_P1_All	0xFF	//IO��������

#define ADC_90T		(3<<5)
#define ADC_180T	(2<<5)
#define ADC_360T	(1<<5)
#define ADC_540T	0
#define ADC_FLAG	(1<<4)	//�����0
#define ADC_START	(1<<3)	//�Զ���0
#define ADC_CH0		0
#define ADC_CH1		1
#define ADC_CH2		2
#define ADC_CH3		3
#define ADC_CH4		4
#define ADC_CH5		5
#define ADC_CH6		6
#define ADC_CH7		7

#define ADC_RES_H2L8	1
#define ADC_RES_H8L2	0


typedef struct
{
	u8	ADC_Px;			//����Ҫ��ADC��IO,	ADC_P10 ~ ADC_P17,ADC_P1_All
	u8	ADC_Speed;		//ADC�ٶ�			ADC_90T,ADC_180T,ADC_360T,ADC_540T
	u8	ADC_Power;		//ADC��������/�ر�	ENABLE,DISABLE
	u8	ADC_AdjResult;	//ADC�������,	ADC_RES_H2L8,ADC_RES_H8L2
	u8	ADC_Polity;		//���ȼ�����	PolityHigh,PolityLow
	u8	ADC_Interrupt;	//�ж�����		ENABLE,DISABLE
} ADC_InitTypeDef;

void	ADC_Inilize(ADC_InitTypeDef *ADCx);
void	ADC_PowerControl(u8 pwr);
u16		Get_ADC10bitResult(u8 channel);	//channel = 0~7

#endif
