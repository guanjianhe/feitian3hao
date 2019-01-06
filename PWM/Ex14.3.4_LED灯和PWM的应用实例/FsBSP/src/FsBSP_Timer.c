/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : FsBSP_Timer.c
 * 文件描述 : 定时器和中断驱动程序
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-07-11
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 
 * Copyright (C), 2014-2015, 兰州文轩电子科技有限公司
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */
#include "BSP_Include.h"
//************** PWM8 变量和常量以及IO口定义 ***************
//********************  8通道8 bit 软PWM    ********************
u8 bdata PWM_temp0,PWM_temp2;       //影射一个RAM，可位寻址，输出时同步刷新
sbit    P_PWM0  =   PWM_temp0^0;    //  定义影射RAM每位对应的IO
sbit    P_PWM1  =   PWM_temp0^1;
sbit    P_PWM2  =   PWM_temp0^2;
sbit    P_PWM3  =   PWM_temp0^3;
sbit    P_PWM4  =   PWM_temp0^4;
sbit    P_PWM5  =   PWM_temp0^5;
sbit    P_PWM6  =   PWM_temp0^6;
sbit    P_PWM7  =   PWM_temp0^7;
sbit    P_PWM8  =   PWM_temp2^0;
sbit    P_PWM9  =   PWM_temp2^1;
sbit    P_PWM10 =   PWM_temp2^2;
sbit    P_PWM11 =   PWM_temp2^3;
sbit    P_PWM12 =   PWM_temp2^4;
sbit    P_PWM13 =   PWM_temp2^5;
sbit    P_PWM14 =   PWM_temp2^6;
sbit    P_PWM15 =   PWM_temp2^7;

u8    pwm_duty;       //周期计数值
u8    pwm[16];        //pwm0~pwm15 为0至15路PWM的宽度值
bit     B_1ms;
u8      cnt_1ms;
u8      cnt_20ms;
/* ******************************************************************
* 函数名称： Timer0_Init()
* 入口参数：无
* 出口参数：无
* 函数功能：初始化定时器 0
****************************************************************** */
void Timer0_Init(void)
{
		AUXR |=  (1<<7);    			// Timer0 set as 1T mode
    TMOD &= ~(1<<2);    				// Timer0 set as Timer
    TMOD &= ~0x03;      				// Timer0 set as 16 bits Auto Reload
    TH0 = Timer0_Reload / 256;  //Timer0 Load
    TL0 = Timer0_Reload % 256;
    ET0 = 1;        //Timer0 Interrupt Enable
    PT0 = 1;        //高优先级
    TR0 = 1;        //Timer0 Run
    EA = 1;         //打开总中断
}
/* ******************************************************************
* 函数名称：timer0 (void) interrupt 1
* 入口参数：无
* 出口参数：无
* 函数功能：定时器0的中断函数_Timer0 1ms中断函数
****************************************************************** */
void timer0 (void) interrupt 1
{
    P0 = PWM_temp0;         //影射RAM输出到实际的PWM端口
    P2 = PWM_temp2;
 
    if(++pwm_duty == PWM_DUTY_MAX)      //PWM周期结束，重新开始新的周期
    {
        pwm_duty = 0;
        PWM_temp0 = PWM_ALL_ON; 
        PWM_temp2 = PWM_ALL_ON; 
    }
    ACC = pwm_duty;
    if(ACC == pwm[0])       P_PWM0  = PWM_OFF;  //判断PWM占空比是否结束
    if(ACC == pwm[1])       P_PWM1  = PWM_OFF;
    if(ACC == pwm[2])       P_PWM2  = PWM_OFF;
    if(ACC == pwm[3])       P_PWM3  = PWM_OFF;
    if(ACC == pwm[4])       P_PWM4  = PWM_OFF;
    if(ACC == pwm[5])       P_PWM5  = PWM_OFF;
    if(ACC == pwm[6])       P_PWM6  = PWM_OFF;
    if(ACC == pwm[7])       P_PWM7  = PWM_OFF;
    if(ACC == pwm[8])       P_PWM8  = PWM_OFF;
    if(ACC == pwm[9])       P_PWM9  = PWM_OFF;
    if(ACC == pwm[10])      P_PWM10 = PWM_OFF;
    if(ACC == pwm[11])      P_PWM11 = PWM_OFF;
    if(ACC == pwm[12])      P_PWM12 = PWM_OFF;
    if(ACC == pwm[13])      P_PWM13 = PWM_OFF;
    if(ACC == pwm[14])      P_PWM14 = PWM_OFF;
    if(ACC == pwm[15])      P_PWM15 = PWM_OFF;

    if(--cnt_1ms == 0)
    {
        cnt_1ms = Timer0_Rate / 1000;
        B_1ms = 1;      // 1ms标志
    }
}
