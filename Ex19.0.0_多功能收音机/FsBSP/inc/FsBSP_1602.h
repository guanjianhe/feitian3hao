#ifndef	__FsBSP_1602_H__
#define	__FsBSP_1602_H__

#include "stc15_delay.h"

/* ***************************************************** */
// λ����
/* ***************************************************** */
sbit RS = P3^3;		//����/����ѡ���(H/L)
sbit RW = P3^4;		//��/дѡ���(H/L)
sbit EN = P3^5;		//ʹ���ź�

#define DB P0
extern void WrComLCD(u8 ComVal);
extern void LcdAreaClear(u8 x, u8 y, u8 len);
extern void LcdShowStr(u8 x, u8 y, u8 *str);
extern void LCD_Init(void);

#endif
