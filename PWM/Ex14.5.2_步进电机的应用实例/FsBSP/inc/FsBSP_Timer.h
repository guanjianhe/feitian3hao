#ifndef __FsBSP_Timer_H__
#define __FsBSP_Timer_H__

#include "STC15.h"

#define     Timer0_Rate     25000       //�ж�Ƶ��
#define     Timer0_Reload   (65536UL -(MAIN_Fosc / Timer0_Rate))        //Timer 0 ��װֵ
#define     PWM_DUTY_MAX    250 // 0~255    PWM����, ���255
#define     PWM_ON          1   // ����ռ�ձȵĵ�ƽ, 1 �� 0
#define     PWM_OFF         (!PWM_ON)
#define     PWM_ALL_ON      (0xff * PWM_ON)

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

extern u8     pwm_duty;       //���ڼ���ֵ
extern u8     bdata PWM_temp0,PWM_temp2;       //Ӱ��һ��RAM����λѰַ�����ʱͬ��ˢ��
extern u8     pwm[16];
extern bit    B_1ms;
extern u8     cnt_1ms;
extern u8     cnt_20ms;

extern  void Timer0_Init(void);

#endif