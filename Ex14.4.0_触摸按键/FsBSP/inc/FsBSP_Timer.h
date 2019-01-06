#ifndef __FsBSP_Timer_H__
#define __FsBSP_Timer_H__

#define	Timer0_Reload	(65536UL -(MAIN_Fosc / 600000))		//Timer 0 重装值， 对应300KHZ

extern void Timer0_Init(void);

#endif