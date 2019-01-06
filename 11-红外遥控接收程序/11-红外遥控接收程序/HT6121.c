
/*---------------------------------------------------------------------*/
/* --- STC MCU International Limited ----------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ���˺꾧�Ƽ������ϼ�����   */
/*---------------------------------------------------------------------*/



/*************	����˵��	**************

������ճ����������г�����������HT6121/6122�������IC�ı��롣

�û������� "HT6121.h" �ļ���ָ���û���.

�û��ײ���򰴹̶���ʱ����(60~125us)���� "IR_RX_HT6121()"����.

Ӧ�ò��ѯ B_IR_Press��־Ϊ,���ѽ��յ�һ���������IR_code��, 

ͬʱB_IrUserCodeErrָʾ����UserCode�е��û����Ƿ��"HT6121.h" �ļ���ָ�����û������,0Ϊ���(�û�����ȷ),1Ϊ�����(�û������).

�������, ��ؽ�B_IR_Press��־��0.

******************************************/

#include	"HT6121.h"



/*************	���س�������	**************/



/*************	���ر�������	**************/

sbit	P_IR_RX	= P3^2;			//��������������IO��

u8	IR_SampleCnt;		//��������
u8	IR_BitCnt;			//����λ��
u8	IR_UserH;			//�û���(��ַ)���ֽ�
u8	IR_UserL;			//�û���(��ַ)���ֽ�
u8	IR_data;			//����ԭ��
u8	IR_DataShit;		//������λ

bit	P_IR_RX_temp;		//Last sample
bit	B_IR_Sync;			//���յ�ͬ����־
bit	B_IrUserCodeErr;	//User code error flag
bit	B_IR_Press;			//������������
u8	IR_code;			//�������
u16	UserCode;			//�û���

/*************	���غ�������	**************/


/*************  �ⲿ�����ͱ������� *****************/



//*******************************************************************
//*********************** IR Remote Module **************************
//*********************** By ���� (Coody) 2002-8-24 *****************
//*********************** IR Remote Module **************************
//this programme is used for Receive IR Remote (HT6121).

//data format: Synchro,AddressH,AddressL,data,/data, (total 32 bit).

//send a frame(85ms), pause 23ms, send synchro of another frame, pause 94ms

//data rate: 108ms/Frame


//Synchro:low=9ms,high=4.5/2.25ms,low=0.5626ms
//Bit0:high=0.5626ms,low=0.5626ms
//Bit1:high=1.6879ms,low=0.5626ms
//frame space = 23 ms or 96 ms

/******************** �������ʱ��궨��, �û���Ҫ�����޸�	*******************/

#define IR_SAMPLE_TIME		(1000000UL/SysTick)			//��ѯʱ����, us, �������Ҫ����60us~250us֮��
#if ((IR_SAMPLE_TIME <= 250) && (IR_SAMPLE_TIME >= 60))
	#define	D_IR_sample			IR_SAMPLE_TIME		//�������ʱ�䣬��60us~250us֮��
#endif

#define D_IR_SYNC_MAX		(15000/D_IR_sample)	//SYNC max time
#define D_IR_SYNC_MIN		(9700 /D_IR_sample)	//SYNC min time
#define D_IR_SYNC_DIVIDE	(12375/D_IR_sample)	//decide data 0 or 1
#define D_IR_DATA_MAX		(3000 /D_IR_sample)	//data max time
#define D_IR_DATA_MIN		(600  /D_IR_sample)	//data min time
#define D_IR_DATA_DIVIDE	(1687 /D_IR_sample)	//decide data 0 or 1
#define D_IR_BIT_NUMBER		32					//bit number

//*******************************************************************************************
//**************************** IR RECEIVE MODULE ********************************************

void IR_RX_HT6121(void)
{
	u8	SampleTime;

	IR_SampleCnt++;							//Sample + 1

	F0 = P_IR_RX_temp;						//Save Last sample status
	P_IR_RX_temp = P_IR_RX;					//Read current status
	if(F0 && !P_IR_RX_temp)					//Pre-sample is high��and current sample is low, so is fall edge
	{
		SampleTime = IR_SampleCnt;			//get the sample time
		IR_SampleCnt = 0;					//Clear the sample counter

			 if(SampleTime > D_IR_SYNC_MAX)		B_IR_Sync = 0;	//large the Maxim SYNC time, then error
		else if(SampleTime >= D_IR_SYNC_MIN)					//SYNC
		{
			if(SampleTime >= D_IR_SYNC_DIVIDE)
			{
				B_IR_Sync = 1;					//has received SYNC
				IR_BitCnt = D_IR_BIT_NUMBER;	//Load bit number
			}
		}
		else if(B_IR_Sync)						//has received SYNC
		{
			if(SampleTime > D_IR_DATA_MAX)		B_IR_Sync=0;	//data samlpe time too large
			else
			{
				IR_DataShit >>= 1;					//data shift right 1 bit
				if(SampleTime >= D_IR_DATA_DIVIDE)	IR_DataShit |= 0x80;	//devide data 0 or 1
				if(--IR_BitCnt == 0)				//bit number is over?
				{
					B_IR_Sync = 0;					//Clear SYNC
					if(~IR_DataShit == IR_data)		//�ж�����������
					{
						UserCode = ((u16)IR_UserH << 8) + IR_UserL;
						IR_code      = IR_data;
						if(UserCode == D_USER_CODE)
								B_IrUserCodeErr = 0;	//User code is righe
						else	B_IrUserCodeErr = 1;	//user code is wrong
						B_IR_Press   = 1;			//������Ч
					}
				}
				else if((IR_BitCnt & 7)== 0)		//one byte receive
				{
					IR_UserL = IR_UserH;			//Save the User code high byte
					IR_UserH = IR_data;				//Save the User code low byte
					IR_data  = IR_DataShit;			//Save the IR data byte
				}
			}
		}
	}
}

