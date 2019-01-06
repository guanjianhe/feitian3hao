#ifndef	__FsBSP_1602_H__
#define	__FsBSP_1602_H__

#include "STC15_FS.h"

#define  uChar8 unsigned char
#define  uInt16 unsigned int

/* ***************************************************** */
// λ����
/* ***************************************************** */
sbit RS = P3^3;				//����/����ѡ���(H/L)
sbit RW = P3^4;			//��/дѡ���(H/L)
sbit EN = P3^5;		//ʹ���ź�
extern uChar8 code TAB1[];
extern uChar8 code TAB2[];
#define DB P0
extern void LcdAreaClear(unsigned char x, unsigned char y, unsigned char len);
extern void LcdShowStr(uChar8 x, uChar8 y, uChar8 *str);
extern void LCD_Init(void);
extern void Dispaly_1602(void);

extern void display_num(unsigned int num);
extern void display_Voltage_value(unsigned int num);

#endif
