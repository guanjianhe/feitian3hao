/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : main.c
 * �ļ����� : ������� + �����
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-09-14
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, �����������ӿƼ����޹�˾/�廪��ѧ������
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#include "BSP_Include.h"

#define BAUDRATE 9600

u8 t, r;
u8 xdata Buf[256];

extern bit TxSta;			// ���Ϳ�ʼ��־λ
extern bit TxEnd,RxEnd;		// ���͡����ս�����־λ
extern u8 TxBuf,RxBuf;		// �����͡����ջ�������

void Timer_ConfigInit(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//�ṹ����
	
	u16 Timer0InitVal;
	Timer0InitVal = (65536 - MAIN_Fosc / BAUDRATE / 4);		//�����ʼֵ,��4���Ĳ����ʽ��в���

	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload
	TIM_InitStructure.TIM_Polity    = PolityHigh;			//ָ���ж����ȼ�, PolityHigh
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//ָ��ʱ��Դ,     TIM_CLOCK_1T
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, DISABLE
	TIM_InitStructure.TIM_Value     = Timer0InitVal;		//��ֵ
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//��ʼ��Timer0
}

void main(void)
{
	Delay_ms(10);		// ���ϵ��ȶ�
	EA = 1;				// �����ж�
	Timer_ConfigInit();	// ��ʼ����ʱ��
	USART_Init();		// ��ʼ������
	
	for(;;)
	{
        if(RxEnd)					// ������ɣ��ȵ�������
        {
            RxEnd = 0;
            Buf[r++] = RxBuf;		// ���յ������ݴ浽Buf��
        }
        if(TxEnd)
        {
            if (t != r)				// ������յ������ݣ��� t ������ r
            {
                TxEnd = 0;			// ���ͽ���������־λ��0��Ҳ����ʼ��������
                TxBuf = Buf[t++];	// ��������
                TxSta = 1;			// ������λ��������������
            }
        }
	}
}

/* *********************************** End of File *********************************** */
