#ifndef	__FSBSP_PWM_H
#define	__FSBSP_PWM_H
#include	"BSP_Include.h"
#define		PWM_DeadZone	12	/* ����ʱ����, 6 ~ 24֮��  */
extern unsigned int code T_SinTable[200];
typedef struct
{ 
	u8	id;				//���ں�

	u8	TX_read;		//���Ͷ�ָ��
	u8	TX_write;		//����дָ��
	u8	B_TX_busy;		//æ��־

	u8 	RX_Cnt;			//�����ֽڼ���
	u8	RX_TimeOut;		//���ճ�ʱ
	u8	B_RX_OK;		//���տ����
} PWMx_Define; 
typedef struct
{
	u16	FirstEdge;				// ��һ����ת����, 1~32767
	u16	SecondEdge;				// �ڶ�����ת����, 1~32767
	u8	Start_IO_Level;			// ����PWM����˿ڵĳ�ʼ��ƽ, 0��1
	u8	PWMx_IO_Select;			// PWM���IOѡ��. PWM2_P37,PWM2_P27,PWM3_P21,PWM3_P45,PWM4_P22,PWM4_P44,PWM5_P23,PWM5_P42,PWM6_P16,PWM6_P07,PWM7_P17,PWM7_P06
	u8	PWMx_Interrupt;			// �ж�����,   ENABLE,DISABLE
	u8	FirstEdge_Interrupt;	// ��һ����ת�ж�����, ENABLE,DISABLE
	u8	SecondEdge_Interrupt;	// �ڶ�����ת�ж�����, ENABLE,DISABLE
} PWMx_InitDefine; 
void	PWM_SourceClk_Duty(u8 PWM_SourceClk, u16 init_duty);
void	PWMx_Configuration(u8 PWM_id, PWMx_InitDefine *PWMx);
void	PWMx_SetPwmWide(u8 PWM_id, u16 FirstEdge, u16 SecondEdge);

#endif
