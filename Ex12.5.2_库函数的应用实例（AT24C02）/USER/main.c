/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : main.c
 * �ļ����� : AT24CC02 + ����
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-08-30
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, �����������ӿƼ����޹�˾/�廪��ѧ������
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#include "BSP_Include.h"

u8 code InputData[4] = {0x12,0x34,0x56,0xab};
u8  OutputData[4] = {0};

static void	UART_ConfigInit(void)
{
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����	
	       
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//ģʽ,       UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//ʹ�ò�����,   BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
	COMx_InitStructure.UART_Interrupt = ENABLE;				//�ж�����,   ENABLE��DISABLE
	COMx_InitStructure.UART_Polity    = PolityLow;			//�ж����ȼ�, PolityLow,PolityHigh
	COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(����ʹ���ڲ�ʱ��)
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;		//�ڲ���·RXD��TXD, ���м�, ENABLE,DISABLE
	USART_Configuration(USART1, &COMx_InitStructure);		//��ʼ������1 USART1
	
	EA = 1; 												//�����ж�
}

static void AT24C02_Demo(void)
{
	u8 i = 0;
	//u8 *sp;
	IIC_WrDatToAdd(0xa0,0x28,InputData,4);
	Delay_ms(10);
	IIC_RdDatFromAdd(0xa0,0x28,OutputData,4);
	
	#if 0		// �����ã�������֮���൱����բ��ֱ�ӹرա�
	sp = &InputData[0];
    for(i=0;i<4;i++)
    {
        TX1_write2buff(*sp);
        sp++;
    }    
	
	Delay_ms(10);
	
	sp = &OutputData[0];
    for(i=0;i<4;i++)
    {
        TX1_write2buff(*sp);
        sp++;
    }
	#endif
		
	for(i = 0; i < 4; i++)				// �Ƚ�д��Ͷ����������Ƿ���ͬ
	{
		if(InputData[i] == OutputData[i])
		{
			PrintString1("\r /* Test OK... */ \r\n" );
			Delay_ms(10);
		}
		else 
		{
			PrintString1("\r /* Test ERROR... */ \r\n" );	
			Delay_ms(10);
		}
	}
}

void main(void)
{
	Delay_ms(100);		// ���ϵ��ȶ�
	
	UART_ConfigInit();
	GPIO_ConfigInit();
	
	Delay_ms(10);
	PrintString1("\r /* =========================================== */ \r\n" );	Delay_ms(10);
	PrintString1("\r ��ӭʹ���w����̖��FSST15��������.............. \r\n" );		Delay_ms(10);
	PrintString1("\r �������������鼮��������STC15��Ƭ��ǣ�ֵ���Щ�꡷ \r\n" );	Delay_ms(10);
	PrintString1("\r ��������������Ƶ����������ǳ����תSTC15��Ƭ���� \r\n" );		Delay_ms(10);
	PrintString1("\r /* =========================================== */ \r\n" );	Delay_ms(10);
	
	AT24C02_Demo();
	
	while(1);
}

/* *********************************** End of File *********************************** */
