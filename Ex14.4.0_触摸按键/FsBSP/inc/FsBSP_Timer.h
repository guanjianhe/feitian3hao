#ifndef __FsBSP_Timer_H__
#define __FsBSP_Timer_H__

#define	Timer0_Reload	(65536UL -(MAIN_Fosc / 600000))		//Timer 0 ��װֵ�� ��Ӧ300KHZ

extern void Timer0_Init(void);

#endif