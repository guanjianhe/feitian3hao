/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : FsBSP_Timer.c
 * �ļ����� : ��ʱ�����ж���������
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-07-11
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 
 * Copyright (C), 2014-2015, �����������ӿƼ����޹�˾
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */
#include "BSP_Include.h"
//************** PWM8 �����ͳ����Լ�IO�ڶ��� ***************
//********************  8ͨ��8 bit ��PWM    ********************
u8 bdata PWM_temp0,PWM_temp2;       //Ӱ��һ��RAM����λѰַ�����ʱͬ��ˢ��
sbit    P_PWM0  =   PWM_temp0^0;    //  ����Ӱ��RAMÿλ��Ӧ��IO
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

u8    pwm_duty;       //���ڼ���ֵ
u8    pwm[16];        //pwm0~pwm15 Ϊ0��15·PWM�Ŀ��ֵ
bit     B_1ms;
u8      cnt_1ms;
u8      cnt_20ms;
/* ******************************************************************
* �������ƣ� Timer0_Init()
* ��ڲ�������
* ���ڲ�������
* �������ܣ���ʼ����ʱ�� 0
****************************************************************** */
void Timer0_Init(void)
{
		AUXR |=  (1<<7);    			// Timer0 set as 1T mode
    TMOD &= ~(1<<2);    				// Timer0 set as Timer
    TMOD &= ~0x03;      				// Timer0 set as 16 bits Auto Reload
    TH0 = Timer0_Reload / 256;  //Timer0 Load
    TL0 = Timer0_Reload % 256;
    ET0 = 1;        //Timer0 Interrupt Enable
    PT0 = 1;        //�����ȼ�
    TR0 = 1;        //Timer0 Run
    EA = 1;         //�����ж�
}
/* ******************************************************************
* �������ƣ�timer0 (void) interrupt 1
* ��ڲ�������
* ���ڲ�������
* �������ܣ���ʱ��0���жϺ���_Timer0 1ms�жϺ���
****************************************************************** */
void timer0 (void) interrupt 1
{
    P0 = PWM_temp0;         //Ӱ��RAM�����ʵ�ʵ�PWM�˿�
    P2 = PWM_temp2;
 
    if(++pwm_duty == PWM_DUTY_MAX)      //PWM���ڽ��������¿�ʼ�µ�����
    {
        pwm_duty = 0;
        PWM_temp0 = PWM_ALL_ON; 
        PWM_temp2 = PWM_ALL_ON; 
    }
    ACC = pwm_duty;
    if(ACC == pwm[0])       P_PWM0  = PWM_OFF;  //�ж�PWMռ�ձ��Ƿ����
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
        B_1ms = 1;      // 1ms��־
    }
}
