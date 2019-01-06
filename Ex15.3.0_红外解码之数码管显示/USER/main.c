/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : main.c
 * �ļ����� : ������� + �����
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-09-09
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, �����������ӿƼ����޹�˾/�廪��ѧ������
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#include "BSP_Include.h"

extern bit g_IR_OK;				// stc15_exti.c �ļ��ж��壬����ֻ������
extern u8  xdata g_IRcord[4];	// stc15_exti.c �ļ��ж��壬����ֻ������

unsigned char  Bit_Tab[] = 
{0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};		//λѡ����

unsigned char  Disp_Tab[] = 
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void Timer_ConfigInit(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//�ṹ����

	TIM_InitStructure.TIM_Mode      = TIM_8BitAutoReload;	//ָ������ģʽ,   TIM_8BitAutoReload
	TIM_InitStructure.TIM_Polity    = PolityLow;			//ָ���ж����ȼ�, PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//ָ��ʱ��Դ,     TIM_CLOCK_12T
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, DISABLE
	TIM_InitStructure.TIM_Value     = 0;					//��ֵ
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//��ʼ��Timer0
}

void Interrupt_ConfigInit(void)
{
	EXTI_InitTypeDef	EXTI_InitStructure;					//�ṹ����
    
	EXTI_InitStructure.EXTI_Mode      = EXT_MODE_Fall;	    //�ж�ģʽ,  EXT_MODE_Fall
	EXTI_InitStructure.EXTI_Polity    = PolityHigh;			//�ж����ȼ�, PolityHigh
	EXTI_InitStructure.EXTI_Interrupt = ENABLE;				//�ж�����,   ENABLE
	Ext_Inilize(EXT_INT0,&EXTI_InitStructure);				//��ʼ��INT0	EXT_INT0
}

/* ***************************************************** */
// �������ƣ�LedDisplay()
// �������ܣ��������ʾ
// ��ڲ���������ʾ����(ByteVal[])
// ���ڲ�������
/* ***************************************************** */
void LedDisplay(u8 ByteVal[])
{
	u8  *Dis_ByteVal = ByteVal;
	
	P6 = Bit_Tab[0];					// ��λѡ����
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+0)/16]);	// �Ͷ�ѡ����
	HC595_WrOneByte(0x00);				// ������Ӱ����
	P6 = Bit_Tab[1];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+0)%16]);
	HC595_WrOneByte(0x00);
	
	P6 = Bit_Tab[2];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+1)/16]);
	HC595_WrOneByte(0x00);
	P6 = Bit_Tab[3];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+1)%16]);
	HC595_WrOneByte(0x00);
	
	P6 = Bit_Tab[4];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+2)/16]);
	HC595_WrOneByte(0x00);
	P6 = Bit_Tab[5];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+2)%16]);
	HC595_WrOneByte(0x00);
	
	P6 = Bit_Tab[6];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+3)/16]);
	HC595_WrOneByte(0x00);
	P6 = Bit_Tab[7];
	HC595_WrOneByte(Disp_Tab[*(Dis_ByteVal+3)%16]);
	HC595_WrOneByte(0x00);
}

void main(void)
{
	Delay_ms(100);		// ���ϵ��ȶ�
	
	EA = 1;				// �����ж�
	
	GPIO_ConfigInit();
	Timer_ConfigInit();
	Interrupt_ConfigInit();
	
	for(;;)
	{
		if(g_IR_OK)         	//������պ��˽��к��⴦��
		{   
			IrcordPro();
			g_IR_OK=0;
		}
		LedDisplay(g_IRcord);
	}
}

/* *********************************** End of File *********************************** */
