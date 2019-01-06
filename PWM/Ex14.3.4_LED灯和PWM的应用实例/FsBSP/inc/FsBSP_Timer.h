#ifndef __FsBSP_Timer_H__
#define __FsBSP_Timer_H__

#include "STC15.h"

#define     Timer0_Rate     25000       //中断频率
#define     Timer0_Reload   (65536UL -(MAIN_Fosc / Timer0_Rate))        //Timer 0 重装值
#define     PWM_DUTY_MAX    250 // 0~255    PWM周期, 最大255
#define     PWM_ON          1   // 定义占空比的电平, 1 或 0
#define     PWM_OFF         (!PWM_ON)
#define     PWM_ALL_ON      (0xff * PWM_ON)

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

extern u8     pwm_duty;       //周期计数值
extern u8     bdata PWM_temp0,PWM_temp2;       //影射一个RAM，可位寻址，输出时同步刷新
extern u8     pwm[16];
extern bit    B_1ms;
extern u8     cnt_1ms;
extern u8     cnt_20ms;

extern  void Timer0_Init(void);

#endif