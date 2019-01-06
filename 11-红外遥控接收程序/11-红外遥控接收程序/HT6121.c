
/*---------------------------------------------------------------------*/
/* --- STC MCU International Limited ----------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了宏晶科技的资料及程序   */
/*---------------------------------------------------------------------*/



/*************	功能说明	**************

红外接收程序。适用于市场上用量最大的HT6121/6122及其兼容IC的编码。

用户可以在 "HT6121.h" 文件中指定用户码.

用户底层程序按固定的时间间隔(60~125us)调用 "IR_RX_HT6121()"函数.

应用层查询 B_IR_Press标志为,则已接收到一个键码放在IR_code中, 

同时B_IrUserCodeErr指示放在UserCode中的用户码是否跟"HT6121.h" 文件中指定的用户码相等,0为相等(用户码正确),1为不相等(用户码错误).

处理完成, 务必将B_IR_Press标志清0.

******************************************/

#include	"HT6121.h"



/*************	本地常量声明	**************/



/*************	本地变量声明	**************/

sbit	P_IR_RX	= P3^2;			//定义红外接收输入IO口

u8	IR_SampleCnt;		//采样计数
u8	IR_BitCnt;			//编码位数
u8	IR_UserH;			//用户码(地址)高字节
u8	IR_UserL;			//用户码(地址)低字节
u8	IR_data;			//数据原码
u8	IR_DataShit;		//数据移位

bit	P_IR_RX_temp;		//Last sample
bit	B_IR_Sync;			//已收到同步标志
bit	B_IrUserCodeErr;	//User code error flag
bit	B_IR_Press;			//安键动作发生
u8	IR_code;			//红外键码
u16	UserCode;			//用户码

/*************	本地函数声明	**************/


/*************  外部函数和变量声明 *****************/



//*******************************************************************
//*********************** IR Remote Module **************************
//*********************** By 梁深 (Coody) 2002-8-24 *****************
//*********************** IR Remote Module **************************
//this programme is used for Receive IR Remote (HT6121).

//data format: Synchro,AddressH,AddressL,data,/data, (total 32 bit).

//send a frame(85ms), pause 23ms, send synchro of another frame, pause 94ms

//data rate: 108ms/Frame


//Synchro:low=9ms,high=4.5/2.25ms,low=0.5626ms
//Bit0:high=0.5626ms,low=0.5626ms
//Bit1:high=1.6879ms,low=0.5626ms
//frame space = 23 ms or 96 ms

/******************** 红外采样时间宏定义, 用户不要随意修改	*******************/

#define IR_SAMPLE_TIME		(1000000UL/SysTick)			//查询时间间隔, us, 红外接收要求在60us~250us之间
#if ((IR_SAMPLE_TIME <= 250) && (IR_SAMPLE_TIME >= 60))
	#define	D_IR_sample			IR_SAMPLE_TIME		//定义采样时间，在60us~250us之间
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
	if(F0 && !P_IR_RX_temp)					//Pre-sample is high，and current sample is low, so is fall edge
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
					if(~IR_DataShit == IR_data)		//判断数据正反码
					{
						UserCode = ((u16)IR_UserH << 8) + IR_UserL;
						IR_code      = IR_data;
						if(UserCode == D_USER_CODE)
								B_IrUserCodeErr = 0;	//User code is righe
						else	B_IrUserCodeErr = 1;	//user code is wrong
						B_IR_Press   = 1;			//数据有效
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

