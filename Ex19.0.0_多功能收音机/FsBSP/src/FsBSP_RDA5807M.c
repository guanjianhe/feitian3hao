/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� ��FsBSP_RDA5807M.c
 * �ļ����� ��RDA5807M����������Դ��
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾���� ��V1.0 	   					
 * �޸����� ��2015-09-16
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, �����������ӿƼ����޹�˾/�廪��ѧ������
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#include "FsBSP_RDA5807M.h"

// ��д��RDA5807M�Ĵ���������
u8 xdata RDA5807_WrRegDat[8] =
{
   0xd0,0x00,  		// 02H
   0x00,0x00,  		// 03H
   0x00,0x40,  		// 04H
   0x90,0x88,  		// 05H
};
// ������RDA5807M�Ĵ���������
u8 xdata RDA5807_RdRegDat[4] =
{
   0x00,0x00,  		// 0AH
   0x00,0x00,  		// 0BH
};

/* ***************************************************** */
// �������ƣ�RDA5807M_WrReg()
// �������ܣ�������RDA5807M��д��N������
// ��ڲ�����*p(��д�������)��ucLenValд�����ݵĸ���
// ���ڲ�������
/* ***************************************************** */
void RDA5807M_WrReg(u8 *p,u8 ucLenVal)
{
	u8 iCount;	  
	
	IIC_Start();						// ���Ϳ�ʼ�ź�
	InputOneByte(RDA5807M_WrDevAddr);	// ����������ַ(д����)   
	IIC_RdAck(); 						// ��Ӧ��λ
	for(iCount = 0;iCount < ucLenVal;iCount++)
	{
		InputOneByte(*p++);				// д������
		IIC_RdAck(); 					// ��Ӧ��λ
	}
	IIC_Stop(); 						// ����ֹͣ�ź�
}

/* ***************************************************** */
// �������ƣ�RDA5807M_RdReg()
// �������ܣ�������RDA5807M��ȡN������
// ��ڲ�����*p(������������)��ucLenVal�������ݵĸ���
// ���ڲ�������
/* ***************************************************** */
void RDA5807M_RdReg(u8 *p,u8 ucLenVal)
{
	u8 iCount;	  
	
	IIC_Start();						// ���Ϳ�ʼ�ź�
	InputOneByte(RDA5807M_RdDevAddr);	// ����������ַ   
	IIC_RdAck(); 						// ��Ӧ��λ
	for(iCount = 0;iCount < ucLenVal;iCount++)
	{
		*p++ = OutputOneByte();
	   	if(iCount != (ucLenVal - 1))	
			IIC_Ack();    
	}
	IIC_Nack();
	IIC_Stop(); 						// ����ֹͣ�ź�
}

/* ***************************************************** */
// �������ƣ�RDA5807M_PowerOnAndInit()
// �������ܣ���RDA5807M�������ϵ磬����ʼ��������
// ��ڲ�����
// ���ڲ�����
/* ***************************************************** */
void RDA5807M_PowerOnAndInit(void)
{
	Delay_ms(5);
	RDA5807_WrRegDat[0] = 0x00;
	RDA5807_WrRegDat[1] = 0x02;		// ���������λָ��
	RDA5807M_WrReg(RDA5807_WrRegDat,2);
	Delay_ms(5);
	RDA5807_WrRegDat[0] = 0xd0;
	RDA5807_WrRegDat[1] = 0x01;		// Ϊ�������ϵ磬����ʼ��
	RDA5807M_WrReg(RDA5807_WrRegDat,8);
}

/* ***************************************************** */
// �������ƣ�RDA5807M_AutoSeek()
// �������ܣ�RDA5807M�������Զ�Ѱ̨ģʽ
// ��ڲ�����bit��bUpAndDown����1������Ѱ̨   0������Ѱ̨
// ���ڲ�����
/* ***************************************************** */
void RDA5807M_AutoSeek(bit bUpAndDown)
{
	u16 CurFreqPoint;						//��ǰ����Ƶ��

	RDA5807_WrRegDat[3] &= ~(1 << 4);		//���õ�г��Tuneλ����

	if(bUpAndDown)
		RDA5807_WrRegDat[0] &= ~(1 << 1);	//�����Զ�Ѱ̨
	else
		RDA5807_WrRegDat[0] |= (1 << 1); 	//�����Զ�Ѱ̨

	RDA5807_WrRegDat[0] |= (1 << 0);      	//SEEKλ��1���ڲ��Զ�Ѱ̨ʹ��
	RDA5807M_WrReg(RDA5807_WrRegDat,4);		//�����úõ�����д��Ĵ���

	// �ȴ�STC ��־��λ
	while(0 == (RDA5807_RdRegDat[0] & 0x40))
	{
		Delay_ms(20);
		RDA5807M_RdReg(RDA5807_RdRegDat,4);	//��ȡ��ǰ����Ƶ��
	}
	
	Delay_ms(5000);							// �����������ʱֻ�����ڵ���
	Delay_ms(5000);							// ���Զ��յ���̨ʱ��ͣ��10S
	
	CurFreqPoint = RDA5807_RdRegDat[0] & 0x03;			//��ȡ��Ƶ��Ϊ��9:0��
	CurFreqPoint = RDA5807_RdRegDat[1] | (CurFreqPoint << 8);
	CurFreqPoint = CurFreqPoint << 6;					//����Ƶ��ļĴ���Ϊ��15:9��

	RDA5807_WrRegDat[2] = (CurFreqPoint >> 8) & 0xff;	//���浱ǰ����Ƶ��
	RDA5807_WrRegDat[3] = (CurFreqPoint & 0xff);
}

/* ***************************************************** */
// �������ƣ�RDA5807M_AutoSeek()
// �������ܣ�����RDA5807M������������
// ��ڲ�����bit��bUpAndDown����1����������   0��������С
// ���ڲ�����
/* ***************************************************** */
void RDA5807M_SetVolume(bit bUpAndDown)
{
	if(bUpAndDown)
	{
		if((RDA5807_WrRegDat[7] & 0x0f) < 0x0f)	// ֻ�������������ʱ���ſɼ�
		{
			RDA5807_WrRegDat[0] = 0xd0;
			RDA5807_WrRegDat[1] = 0x01;
			RDA5807_WrRegDat[3] &= ~(1 << 4);	// ���õ�г��Tuneλ����

			RDA5807_WrRegDat[7]++;	 			// ��������
			RDA5807M_WrReg(RDA5807_WrRegDat,8);
		}
	}
	else
	{
		if((RDA5807_WrRegDat[7] & 0x0f) > 0x00)	// ֻ������������Сʱ���ſɼ�
		{
			RDA5807_WrRegDat[0] = 0xd0;
			RDA5807_WrRegDat[1] = 0x01;
			RDA5807_WrRegDat[3] &= ~(1 << 4);	// ���õ�г��Tuneλ����

			RDA5807_WrRegDat[7]--;	 			// �����ݼ�
			RDA5807M_WrReg(RDA5807_WrRegDat,8);
		}
	}
}
