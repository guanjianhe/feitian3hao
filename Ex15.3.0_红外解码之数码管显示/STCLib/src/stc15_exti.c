/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : stc15_exti.c
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-08-29
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 刘平（xymbmcu@163.com）/清华大学出版社/STC MCU International Limited
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include	"stc15_exti.h"

extern u8 g_uIR_Time;	//变量在stc15_timer.c 中定义

bit g_IR_OK;			//解码完成标志位
bit g_IR_Pro_OK;		//数据处理完成标志位
u8  xdata g_IRcord[4];  	//处理后的红外码，分别是 客户码，客户码，数据码，数据码反码
u8  xdata HL_LevelPeriodArr[33]; //33个高低电平的周期

void IrcordPro(void)
{ 
  	u8 uiVal,ujVal;
  	u8 ByteVal;				// 一个字节（例如地址码、数据反码等）
  	u8 CordVal;				// 零时存放高低电平持续时间
	u8 uCounter;			// 对应33个数据
	uCounter = 1;				// 这里是为了判断数据，所示避开第一个引导码，直接从“1”开始
	for(uiVal = 0;uiVal < 4;uiVal++)      	// 处理4个字节，依次是地址码、地址反码、//数据码、数据反码
	{
		for(ujVal = 0;ujVal < 8;ujVal++) 	// 处理1个字节的8位
		{
			CordVal = HL_LevelPeriodArr[uCounter];
			// 根据高低电平持续时间的长短来判定是“0”、或是“1” “0”->1.12ms  “1”->2.25ms
			// 这里为了判断，取1.12和2.25的中间值：1.685为判断标准
			// 1.685ms/(256*12/11.0592)us≈6 此值可以有一定误差
			if(CordVal > 6)				// 大于1.685ms则为逻辑“1”	
				ByteVal = ByteVal | 0x80;
			else 						// 小于1.685ms则为逻辑“0”
				ByteVal = ByteVal;
			if(ujVal < 7)				// 前面的7次需要移，第8次操作的就不移了（已经是最高位了）
			{							// 由NEC协议可知，LSB在前，所以操作完一位后后右移一位
				ByteVal >>= 1;			// 这样最先操作的LSB位就放在了数据的最低位
			}
			uCounter++;					// 依次处理这32位
		}
		g_IRcord[uiVal] = ByteVal;		// 将处理好的四个字节分别存到数值g_IRcord中
		ByteVal = 0;					// 清“0”，以便储存下一字节     
	} 
}

/********************* INT0中断函数 *************************/
void Ext_INT0 (void) interrupt INT0_VECTOR		//进中断时已经清除标志
{
	static u8 uCounter;				// 1个引导码+32个位（16位地址码+16位数据位），共33位
	static bit StartFlag;           	// 是否开始处理标志位（“1”开始、“0”未开始）
	EX0 = 0;							// 关闭中断，防止干扰
	if(!StartFlag)						// 首次进来StartFlag为“0”,故执行if语句
	{
		g_uIR_Time = 0;					// 间隔计数值清“0”
		StartFlag = 1;					// 开始采样标志位置“1”
	}
	else if(StartFlag)					// 第2~34次进来执行此if语句                         
	{
		if(g_uIR_Time < 50 && g_uIR_Time >= 32)		// 引导码，9ms+4.5ms
			uCounter = 0;
		/* 9ms/(256*12/11.0592)us≈32   9+4.5ms/(256*12/11.0592)us≈50 */
		HL_LevelPeriodArr[uCounter] = g_uIR_Time;	// 存储每个电平的周期，用于以后判断是0还是1
		g_uIR_Time = 0;								// 清“0”，以便存下一个周期的时间
		uCounter++;									// 依次存入这33个周期
		if(33 == uCounter)
		{
			g_IR_OK = 1;								// 解码完成标志位置“1”，表示解码OK
			uCounter = 0;
			StartFlag = 0;
		}
	}
	EX0 = 1;							// 继续打开中断，以便解码下一个键值
}

/********************* INT1中断函数 *************************/
void Ext_INT1 (void) interrupt INT1_VECTOR		//进中断时已经清除标志
{
	;
}

/********************* INT2中断函数 *************************/
void Ext_INT2 (void) interrupt INT2_VECTOR	//
{
	;
}

/********************* INT3中断函数 *************************/
void Ext_INT3 (void) interrupt INT3_VECTOR
{
	;
}

/********************* INT4中断函数 *************************/
void Ext_INT4 (void) interrupt INT4_VECTOR
{
	;
}

//========================================================================
// 函数: u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
// 描述: 外部中断初始化程序.
// 参数: INTx: 结构参数,请参考Exti.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
// 版本: V1.0, 2012-10-22
// 注意：上升 下降沿中断只适用INT0 1; INT234不用设置中断沿,因为是固定的下降沿
//========================================================================
u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
{
	if(EXT >  EXT_INT4)	return 1;	//空操作
	
	if(EXT == EXT_INT0)	//外中断0
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX0 = 1;	//允许中断
		else									EX0 = 0;	//禁止中断
		if(INTx->EXTI_Polity == PolityHigh)		PX0 = 1;	//高优先级中断
		else									PX0 = 0;	//低优先级中断
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT0 = 1;	//下降沿中断
		else									IT0 = 0;	//上升,下降沿中断
		return	0;		//成功
	}

	if(EXT == EXT_INT1)	//外中断1
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX1 = 1;	//允许中断
		else									EX1 = 0;	//禁止中断
		if(INTx->EXTI_Polity == PolityHigh)		PX1 = 1;	//高优先级中断
		else									PX1 = 0;	//低优先级中断
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT1 = 1;	//下降沿中断
		else									IT1 = 0;	//上升,下降沿中断
		return	0;		//成功
	}

	if(EXT == EXT_INT2)		//外中断2, 固定为下降沿低优先级中断
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 4);	//允许中断	
		else								INT_CLKO &= ~(1 << 4);	//禁止中断
		return	0;		//成功
	}

	if(EXT == EXT_INT3)		//外中断3, 固定为下降沿低优先级中断
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 5);	//允许中断	
		else								INT_CLKO &= ~(1 << 5);	//禁止中断
		return	0;		//成功
	}

	if(EXT == EXT_INT4)		//外中断4, 固定为下降沿低优先级中断
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 6);	//允许中断	
		else								INT_CLKO &= ~(1 << 6);	//禁止中断
		return	0;		//成功
	}
	return 2;	//失败
}
