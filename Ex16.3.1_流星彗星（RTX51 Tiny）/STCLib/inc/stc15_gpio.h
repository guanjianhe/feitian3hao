/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : STC15_GPIO.h
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-08-11
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * �ļ�˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, ��ƽ��xymbmcu@163.com��/�廪��ѧ������/STC MCU Limited
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#ifndef	__STC15_GPIO_H__
#define	__STC15_GPIO_H__

#include  "STC15_CLKVARTYPE.H"

/* ********************************************************
 * I/O����ѡ�񣬷ֱ��Ӧ���ֹ���ģʽ
 ******************************************************* */
#define	GPIO_PullUp		0		// ����׼˫���
#define	GPIO_HighZ		1		// ��������
#define	GPIO_OUT_OD		2		// ��©���
#define	GPIO_OUT_PP		3		// �������
/* ********************************************************
 * �˿�λѡ�񣬷ֱ��Ӧ9��ģʽ
 ******************************************************* */
#define	GPIO_Pin_0		0x01	// IO���� Px.0
#define	GPIO_Pin_1		0x02	// IO���� Px.1
#define	GPIO_Pin_2		0x04	// IO���� Px.2
#define	GPIO_Pin_3		0x08	// IO���� Px.3
#define	GPIO_Pin_4		0x10	// IO���� Px.4
#define	GPIO_Pin_5		0x20	// IO���� Px.5
#define	GPIO_Pin_6		0x40	// IO���� Px.6
#define	GPIO_Pin_7		0x80	// IO���� Px.7
#define	GPIO_Pin_All	0xFF	// IO��������
/* ********************************************************
 * �˿�ѡ�񣬷ֱ��Ӧ8���˿�
 ******************************************************* */	
#define	GPIO_P0		0		
#define	GPIO_P1		1
#define	GPIO_P2		2
#define	GPIO_P3		3
#define	GPIO_P4		4
#define	GPIO_P5		5
#define	GPIO_P6		6
#define	GPIO_P7		7
/* ********************************************************
 * ѡ��PWM�˿ڣ���Ӧ6��PWM����˿�
 ******************************************************* */	
#define	GPIO_PWM2       2
#define	GPIO_PWM3       3
#define	GPIO_PWM4       4
#define	GPIO_PWM5       5
#define	GPIO_PWM6       6
#define	GPIO_PWM7       7

typedef struct
{
	uint8	Mode;	// IO��Ӧ���֣�GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP��ģʽ
	uint8	Pin;	// Ҫ���õĶ˿�	
} GPIO_InitTypeDef;

u8 GPIO_Init(u8 GPIO, GPIO_InitTypeDef *GPIOx);

extern uint8 GPIO_PWMInit(uint8 GPIO_PWM, uint8 PuHzOdPp);

/* ����IIC�˿ڳ�ʼ��Ϊ׼˫��� */
void GPIO_ConfigInit(void);

#endif
