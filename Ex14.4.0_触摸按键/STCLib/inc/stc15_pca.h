/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : stc15_pca.H
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

#ifndef	__STC15_PCA_H__
#define	__STC15_PCA_H__

#include  "STC15_CLKVARTYPE.H"

/***************************�û��궨��*******************************************************/
//#define		PWM_DUTY		10		//����PWM�����ڣ���ֵΪPCA��ѡ���ʱ�����������

extern u16	PWM_DUTY;

//����PWM�������Сռ�ձ�
#define		PWM_HIGH_MIN	1	
//����PWM��������ռ�ձ�
#define		PWM_HIGH_MAX	(PWM_DUTY - PWM_HIGH_MIN)	

/********************************************************************************************/

#define	PCA0			0
#define	PCA1			1
#define	PCA2			2
#define	PCA_Counter		3
#define	PCA_P12_P11_P10_P37	(0<<4)
#define	PCA_P34_P35_P36_P37	(1<<4)
#define	PCA_P24_P25_P26_P27	(2<<4)
#define	PCA_Mode_PWM				0x42	//B0100_0010
#define	PCA_Mode_Capture			0
#define	PCA_Mode_SoftTimer			0x48	//B0100_1000
#define	PCA_Mode_HighPulseOutput	0x4c	//B0100_1100
#define	PCA_Clock_1T	(4<<1)
#define	PCA_Clock_2T	(1<<1)
#define	PCA_Clock_4T	(5<<1)
#define	PCA_Clock_6T	(6<<1)
#define	PCA_Clock_8T	(7<<1)
#define	PCA_Clock_12T	(0<<1)
#define	PCA_Clock_Timer0_OF	(2<<1)
#define	PCA_Clock_ECI	(3<<1)
#define	PCA_Rise_Active	(1<<5)
#define	PCA_Fall_Active	(1<<4)
#define	PCA_PWM_8bit	(0<<6)
#define	PCA_PWM_7bit	(1<<6)
#define	PCA_PWM_6bit	(2<<6)


typedef struct
{
	u8	PCA_IoUse;	//PCA_P12_P11_P10_P37, PCA_P34_P35_P36_P37, PCA_P24_P25_P26_P27
	u8	PCA_Clock;	//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	u8	PCA_Mode;	//PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_HighPulseOutput
	u8	PCA_PWM_Wide;	//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit
	u8	PCA_Interrupt_Mode;	//PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
	u8	PCA_Polity;	//���ȼ�����	PolityHigh,PolityLow
	u16	PCA_Value;
	u8	PCA_RUN;	//ENABLE, DISABLE
} PCA_InitTypeDef;

extern	bit		B_Capture0,B_Capture1,B_Capture2;
extern	u8		PCA0_mode,PCA1_mode,PCA2_mode;
extern	u16		CCAP0_tmp,PCA_Timer0;
extern	u16		CCAP1_tmp,PCA_Timer1;
extern	u16		CCAP2_tmp,PCA_Timer2;
void	PCA_Init(u8 PCA_id, PCA_InitTypeDef *PCAx);
void	UpdatePwm(u8 PCA_id, u8 pwm_value);
void 	PWMn_Update(u8 PCA_id, u16 high);


#endif

