/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : stc15_pca.H
 * 文件描述 : STC系列单片机头文件
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

#ifndef	__STC15_PCA_H__
#define	__STC15_PCA_H__

#include  "STC15_CLKVARTYPE.H"

/***************************用户宏定义*******************************************************/
//#define		PWM_DUTY		10		//定义PWM的周期，数值为PCA所选择的时钟脉冲个数。

extern u16	PWM_DUTY;

//限制PWM输出的最小占空比
#define		PWM_HIGH_MIN	1	
//限制PWM输出的最大占空比
#define		PWM_HIGH_MAX	(PWM_DUTY - PWM_HIGH_MIN)	

/********************************************************************************************/

#define	PCA0			0
#define	PCA1			1
#define	PCA2			2
#define	PCA_Counter		3
#define	PCA_P12_P11_P10_P37	(0<<4)
#define	PCA_P34_P35_P36_P37	(1<<4)
#define	PCA_P24_P25_P26_P27	(2<<4)
#define	PCA_Mode_PWM				0x42	//B0100_0010
#define	PCA_Mode_Capture			0
#define	PCA_Mode_SoftTimer			0x48	//B0100_1000
#define	PCA_Mode_HighPulseOutput	0x4c	//B0100_1100
#define	PCA_Clock_1T	(4<<1)
#define	PCA_Clock_2T	(1<<1)
#define	PCA_Clock_4T	(5<<1)
#define	PCA_Clock_6T	(6<<1)
#define	PCA_Clock_8T	(7<<1)
#define	PCA_Clock_12T	(0<<1)
#define	PCA_Clock_Timer0_OF	(2<<1)
#define	PCA_Clock_ECI	(3<<1)
#define	PCA_Rise_Active	(1<<5)
#define	PCA_Fall_Active	(1<<4)
#define	PCA_PWM_8bit	(0<<6)
#define	PCA_PWM_7bit	(1<<6)
#define	PCA_PWM_6bit	(2<<6)


typedef struct
{
	u8	PCA_IoUse;	//PCA_P12_P11_P10_P37, PCA_P34_P35_P36_P37, PCA_P24_P25_P26_P27
	u8	PCA_Clock;	//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	u8	PCA_Mode;	//PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_HighPulseOutput
	u8	PCA_PWM_Wide;	//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit
	u8	PCA_Interrupt_Mode;	//PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
	u8	PCA_Polity;	//优先级设置	PolityHigh,PolityLow
	u16	PCA_Value;
	u8	PCA_RUN;	//ENABLE, DISABLE
} PCA_InitTypeDef;

extern	bit		B_Capture0,B_Capture1,B_Capture2;
extern	u8		PCA0_mode,PCA1_mode,PCA2_mode;
extern	u16		CCAP0_tmp,PCA_Timer0;
extern	u16		CCAP1_tmp,PCA_Timer1;
extern	u16		CCAP2_tmp,PCA_Timer2;
void	PCA_Init(u8 PCA_id, PCA_InitTypeDef *PCAx);
void	UpdatePwm(u8 PCA_id, u8 pwm_value);
void 	PWMn_Update(u8 PCA_id, u16 high);


#endif

