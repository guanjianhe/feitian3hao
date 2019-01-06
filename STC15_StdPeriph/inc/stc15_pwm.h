/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : stc15_pwm.H
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

#ifndef	__STC15_PWM_H__
#define	__STC15_PWM_H__

#include	"STC15_ClkConfig.h"

//u8 PWM_N,
#define	PWM_2			0		
#define	PWM_3			1
#define	PWM_4			2
#define	PWM_5			3
#define	PWM_6			4
#define	PWM_7			5

#define PWM_HIGHT  1
#define PWM_LOW    0


#define	PWM_Clock_NT        0
#define	PWM_Clock_Timer2_OF 1

#define PWM_SELECT_N        0
#define PWM_SELECT_N_2      1

///////////////////////////////////////////////
//PWM总开关
#define PWM_ALL_EN        PWMCR|=(1<<7);
#define PWM_ALL_NO        PWMCR&=(~(1<<7))

///////////////////////////////////////////////////////////////////////
//PWM寄存器操作使能 如果禁止的话 凡是关于PWM的寄存器都不能操作
#define PWM_UNLOCK    P_SW2|=0X80      /*使能*/
#define PWM_LOCK      P_SW2&=(~0X80)   /*禁止*/

///////////////////////////////////////////////
//PWM对应管脚初始值
//i=PWM_2~PWM_7
#define PWM_INIT_HIGHT(i)        PWMCFG|=(1<<(i));
#define PWM_INIT_LOW(i)          PWMCFG&=(~(1<<(i)))

typedef struct
{
	u8 PWM_GOTO_ADC;            //ENABLE=计数器归零时 触发ADC
	u8 PWM_V_INIT;              //PWM_HIGHT=初始高电平 	PWM_LOW=初始低电平 
    u8 PWM_0ISR_EN;             //ENABLE=使能PWM计数器归零中断  DISABLE=关闭PWM计数器归零中断 但 CBIF仍然会被硬件置位
    u8 PWM_OUT_EN;              //ENABLE=PWM通道x的端口为PWM波形输出口 受PWM波形发生器控制
    u8 PWM_UNUSUAL_EN;          //ENABLE=使能PWM的外部异常检测功能
    u8 PWM_UNUSUAL_OUT;         //ENABLE=发生异常时，PWM对应的输出口会变成 高阻输入模式
    u8 PWM_UNUSUAL_ISR_EN;      //ENABLE=使能异常检测中断 DISABLE=关闭异常检测中断 但FDIF仍然会被硬件置位
    u8 PWM_UNUSUAL_CMP0_EN;     //ENABLE=异常检测源为比较器的输出 当比较结果为高时 触发PWM异常
    u8 PWM_UNUSUAL_P24_EN;      //ENABLE=异常检测源为P24/PWMFLT 当P24=1 触发PWM异常
    u8 PWM_CLOCK;               //PWM_Clock_NT=PWM的时钟源是系统时钟经分频后的时钟  PWM_Clock_Timer2_OF=PWM的时钟源是TMER2的溢出脉冲
    u8 PWM_CLOCK_DIV;           //当PWM_CLOCK=PWM_Clock_NT时 PWM的时钟源是系统时钟/(PS[3:0]+1)
    u8 PWM_SELECTx_IO;          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
    u8 PWM_ISRx_EN;             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
    u8 PWM_T1x_EN;              //ENABLE=使能第一翻转中断
    u8 PWM_T2x_EN;              //ENABLE=使能第二翻转中断
    u8 PWM_EN;                  //ENABLE=PWM使能 在其他PWM参数设置好后最后设置 如果被关闭后在打开，则PWM计数器重新从0计数   
} PWM_InitTypeDef;

extern void PWM_Inilize(u8 PWM_N,PWM_InitTypeDef *PWMx);
extern u8   PWM_SET_PERIOD      (u16 period);
extern u8   PWM_SET_T12_PERIOD  (u8 PWM_N,u16 period1,u16 period2);

#endif
