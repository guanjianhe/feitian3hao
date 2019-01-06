/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : stc15_pwm.H
 * �ļ����� : STCϵ�е�Ƭ��ͷ�ļ�
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

#ifndef	__STC15_PWM_H__
#define	__STC15_PWM_H__

#include	"STC15_ClkConfig.h"

//u8 PWM_N,
#define	PWM_2			0		
#define	PWM_3			1
#define	PWM_4			2
#define	PWM_5			3
#define	PWM_6			4
#define	PWM_7			5

#define PWM_HIGHT  1
#define PWM_LOW    0


#define	PWM_Clock_NT        0
#define	PWM_Clock_Timer2_OF 1

#define PWM_SELECT_N        0
#define PWM_SELECT_N_2      1

///////////////////////////////////////////////
//PWM�ܿ���
#define PWM_ALL_EN        PWMCR|=(1<<7);
#define PWM_ALL_NO        PWMCR&=(~(1<<7))

///////////////////////////////////////////////////////////////////////
//PWM�Ĵ�������ʹ�� �����ֹ�Ļ� ���ǹ���PWM�ļĴ��������ܲ���
#define PWM_UNLOCK    P_SW2|=0X80      /*ʹ��*/
#define PWM_LOCK      P_SW2&=(~0X80)   /*��ֹ*/

///////////////////////////////////////////////
//PWM��Ӧ�ܽų�ʼֵ
//i=PWM_2~PWM_7
#define PWM_INIT_HIGHT(i)        PWMCFG|=(1<<(i));
#define PWM_INIT_LOW(i)          PWMCFG&=(~(1<<(i)))

typedef struct
{
	u8 PWM_GOTO_ADC;            //ENABLE=����������ʱ ����ADC
	u8 PWM_V_INIT;              //PWM_HIGHT=��ʼ�ߵ�ƽ 	PWM_LOW=��ʼ�͵�ƽ 
    u8 PWM_0ISR_EN;             //ENABLE=ʹ��PWM�����������ж�  DISABLE=�ر�PWM�����������ж� �� CBIF��Ȼ�ᱻӲ����λ
    u8 PWM_OUT_EN;              //ENABLE=PWMͨ��x�Ķ˿�ΪPWM��������� ��PWM���η���������
    u8 PWM_UNUSUAL_EN;          //ENABLE=ʹ��PWM���ⲿ�쳣��⹦��
    u8 PWM_UNUSUAL_OUT;         //ENABLE=�����쳣ʱ��PWM��Ӧ������ڻ��� ��������ģʽ
    u8 PWM_UNUSUAL_ISR_EN;      //ENABLE=ʹ���쳣����ж� DISABLE=�ر��쳣����ж� ��FDIF��Ȼ�ᱻӲ����λ
    u8 PWM_UNUSUAL_CMP0_EN;     //ENABLE=�쳣���ԴΪ�Ƚ�������� ���ȽϽ��Ϊ��ʱ ����PWM�쳣
    u8 PWM_UNUSUAL_P24_EN;      //ENABLE=�쳣���ԴΪP24/PWMFLT ��P24=1 ����PWM�쳣
    u8 PWM_CLOCK;               //PWM_Clock_NT=PWM��ʱ��Դ��ϵͳʱ�Ӿ���Ƶ���ʱ��  PWM_Clock_Timer2_OF=PWM��ʱ��Դ��TMER2���������
    u8 PWM_CLOCK_DIV;           //��PWM_CLOCK=PWM_Clock_NTʱ PWM��ʱ��Դ��ϵͳʱ��/(PS[3:0]+1)
    u8 PWM_SELECTx_IO;          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
    u8 PWM_ISRx_EN;             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
    u8 PWM_T1x_EN;              //ENABLE=ʹ�ܵ�һ��ת�ж�
    u8 PWM_T2x_EN;              //ENABLE=ʹ�ܵڶ���ת�ж�
    u8 PWM_EN;                  //ENABLE=PWMʹ�� ������PWM�������úú�������� ������رպ��ڴ򿪣���PWM���������´�0����   
} PWM_InitTypeDef;

extern void PWM_Inilize(u8 PWM_N,PWM_InitTypeDef *PWMx);
extern u8   PWM_SET_PERIOD      (u16 period);
extern u8   PWM_SET_T12_PERIOD  (u8 PWM_N,u16 period1,u16 period2);

#endif
