
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



/*************	本程序功能说明	**************

红外接收程序。适用于市场上用量最大的HT6121/6122及其兼容IC的编码。

用户可以在 "HT6121.h" 文件中指定用户码.

用户底层程序按固定的时间间隔(60~125us)调用 "IR_RX_HT6121()"函数.

应用层查询 B_IR_Press标志为,则已接收到一个键码放在IR_code中, 

同时B_IrUserCodeErr指示放在UserCode中的用户码是否跟""HT6121.h" 文件中指定的用户码相等,0为相等(用户码正确),1为不相等(用户码错误).

数码管左起4位显示用户码, 最右边两位显示数据, 均为十六进制.

******************************************/

#include	"config.H"
#include	"HT6121.h"


/****************************** 用户定义宏 ***********************************/

#define		LED_TYPE	0x00	//定义LED类型, 0x00--共阴, 0xff--共阳

#define	Timer0_Reload	(65536UL - ((MAIN_Fosc + SysTick/2) / SysTick))		//Timer 0 中断频率, 在config.h中指定系统滴答频率, 在4000~16000之间.

/*****************************************************************************/





/*************	本地常量声明	**************/
u8 code t_display[]={						//标准字库
//	 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black	 -     H    J	 K	  L	   N	o   P	 U     t    G    Q    r   M    y
	0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
	0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};	//0. 1. 2. 3. 4. 5. 6. 7. 8. 9. -1

u8 code T_COM[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};		//位码


/*************	IO口定义	**************/
sbit	P_HC595_SER   = P5^0;	//pin 14	SER		data input
sbit	P_HC595_RCLK  = P5^2;	//pin 12	RCLk	store (latch) clock
sbit	P_HC595_SRCLK = P5^3;	//pin 11	SRCLK	Shift data clock

/*************	本地变量声明	**************/

u8 	LED8[8];		//显示缓冲
u8	display_index;	//显示位索引
bit	B_1ms;			//1ms标志

u8	cnt_1ms;		//1ms基本计时


/*************	本地函数声明	**************/


/****************  外部函数声明和外部变量声明 *****************/



/********************** 主函数 ************************/
void main(void)
{
	u8	i;
	
	display_index = 0;

	Timer0_1T();
	Timer0_AsTimer();
	Timer0_16bitAutoReload();
	Timer0_Load(Timer0_Reload);
	Timer0_InterruptEnable();
	Timer0_Run();
	cnt_1ms = SysTick / 1000;
	EA = 1;						//打开总中断
	
	
	for(i=0; i<8; i++)	LED8[i] = DIS_;	//上电显示-
	LED8[4] = DIS_BLACK;
	LED8[5] = DIS_BLACK;

	while(1)
	{
		if(B_1ms)	//1ms到
		{
			B_1ms = 0;
			
			if(B_IR_Press)		//检测到收到红外键码
			{
				B_IR_Press = 0;
				
				LED8[0] = (u8)((UserCode >> 12) & 0x0f);	//用户码高字节的高半字节
				LED8[1] = (u8)((UserCode >> 8)  & 0x0f);	//用户码高字节的低半字节
				LED8[2] = (u8)((UserCode >> 4)  & 0x0f);	//用户码低字节的高半字节
				LED8[3] = (u8)(UserCode & 0x0f);			//用户码低字节的低半字节
				LED8[6] = IR_code >> 4;
				LED8[7] = IR_code & 0x0f;
			}
		}
	}
} 
/**********************************************/





/**************** 向HC595发送一个字节函数 ******************/
void Send_595(u8 dat)
{		
	u8	i;
	for(i=0; i<8; i++)
	{
		dat <<= 1;
		P_HC595_SER   = CY;
		P_HC595_SRCLK = 1;
		P_HC595_SRCLK = 0;
	}
}

/********************** 显示扫描函数 ************************/
void DisplayScan(void)
{	
	P6=(~LED_TYPE ^ T_COM[display_index]);				//输出位码
	Send_595( LED_TYPE ^ t_display[LED8[display_index]]);	//输出段码

	P_HC595_RCLK = 1;
	P_HC595_RCLK = 0;							//锁存输出数据
	if(++display_index >= 8)	display_index = 0;	//8位结束回0
}


/********************** Timer0 1ms中断函数 ************************/
void timer0 (void) interrupt TIMER0_VECTOR
{

	IR_RX_HT6121();
	if(--cnt_1ms == 0)
	{
		cnt_1ms = SysTick / 1000;
		B_1ms = 1;		//1ms标志
		DisplayScan();	//1ms扫描显示一位
	}

}


