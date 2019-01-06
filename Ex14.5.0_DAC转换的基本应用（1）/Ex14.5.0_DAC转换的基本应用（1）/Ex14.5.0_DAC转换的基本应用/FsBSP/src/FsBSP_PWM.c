/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : FsBSP_PWM.c
 * 文件描述 : IAP15W4K58S4的PWM程序
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-09-23
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 
 * Copyright (C), 2014-2015, 兰州文轩电子科技有限公司
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */
#include	"BSP_Include.h"
u8	PWM_Index;	//SPWM查表索引
//========================================================================
// 函数: void	PWM_SourceClk_Duty(u8 PWM_SourceClk, u16 init_duty)
// 描述: 设置PWM时钟源和周期函数。
// 参数: PWM_SourceClk: PWM时钟源, 0~15对应 主时钟/(PWM_SourceClk + 1), 16为选择定时器2的溢出做时钟.
//                      PwmClk_1T,PwmClk_2T, ... PwmClk_16T, PwmClk_Timer2.
//       init_duty: PWM周期长度, 1~32767.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-8-15
// 备注: 
//========================================================================
void	PWM_SourceClk_Duty(u8 PWM_SourceClk, u16 init_duty)
{
	u8	xdata	*px;
	EAXSFR();		// 访问XFR
	px  = PWMCH;	// PWM计数器的高字节
	*px = (u8)(init_duty >> 8);
	px++;
	*px = (u8)init_duty;	// PWM计数器的低字节
	px++;			// PWMCKS, PWM时钟选择
	*px = PWM_SourceClk;
	EAXRAM();	//恢复访问XRAM
}
//========================================================================
// 函数: void	PWMx_Configuration(u8 PWM_id, PWMx_InitDefine *PWMx)
// 描述: PWM配置函数。
// 参数: PWM_id: PWM通道, PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID.
//       *PWMx:  配置结构指针.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-8-15
// 备注: 
//========================================================================
void	PWMx_Configuration(u8 PWM_id, PWMx_InitDefine *PWMx)
{
	u8	xdata	*px;

	EAXSFR();		//访问XFR
	px = PWM2T1H + (PWM_id << 4);
	*px = (u8)(PWMx->FirstEdge >> 8);	//第一个翻转计数高字节
	px++;
	*px = (u8)PWMx->FirstEdge;			//第一个翻转计数低字节
	px++;
	*px = (u8)(PWMx->SecondEdge >> 8);	//第二个翻转计数高字节
	px++;
	*px = (u8)PWMx->SecondEdge;			//第二个翻转计数低字节
	px++;
	*px = (PWMx->PWMx_IO_Select & 0x08)					// PWM输出IO选择
	    | ((PWMx->PWMx_Interrupt << 2) & 0x04)			// 中断允许
		| ((PWMx->SecondEdge_Interrupt << 1) & 0x02)	// 第二个翻转中断允许
		| (PWMx->FirstEdge_Interrupt & 0x01);			// 第一个翻转中断允许
	PWMCR |= (1 << PWM_id);	// 相应PWM通道的端口为PWM输出口，受PWM波形发生器控制
	PWMCFG = (PWMCFG & ~(1 << PWM_id)) | ((PWMx->Start_IO_Level & 1) << PWM_id);	//设置PWM输出端口的初始电平
	EAXRAM();		//恢复访问XRAM
}
/********************* PWM中断函数************************/
void PWM_int (void) interrupt PWM_VECTOR
{
	u8	xdata	*px;
	u16	j;
	u8	SW2_tmp;

	if(PWMIF & CBIF)	//PWM计数器归零中断标志
	{
		PWMIF &= ~CBIF;	//清除中断标志

		SW2_tmp = P_SW2;	//保存SW2设置
		EAXSFR();		//访问XFR
		px = PWM6T2H;	// 指向PWM3
		j = T_SinTable[PWM_Index];
		*px = (u8)(j >> 8);		//第二个翻转计数高字节
		px++;
		*px = (u8)j;			//第二个翻转计数低字节

		j += PWM_DeadZone;		//死区
		px = PWM4T2H;			// 指向PWM4
		*px = (u8)(j >> 8);		//第二个翻转计数高字节
		px++;
		*px = (u8)j;			//第二个翻转计数低字节
		P_SW2 = SW2_tmp;	//恢复SW2设置

		if(++PWM_Index >= 200)	PWM_Index = 0;
		EAXRAM();		//恢复访问XRAM
	}
}
/********************* PWM失效中断函数************************/
void PWMFD_int (void) interrupt PWMFD_VECTOR
{
	if(PWMFDCR & FDIF) 		//PWM异常检测中断标志位
	{
		PWMFDCR &= ~FDIF;	//清除中断标志
	}
}


