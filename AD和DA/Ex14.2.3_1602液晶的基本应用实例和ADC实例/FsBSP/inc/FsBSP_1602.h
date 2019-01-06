#ifndef	__FsBSP_1602_H__
#define	__FsBSP_1602_H__

#include "STC15_FS.h"

#define  uChar8 unsigned char
#define  uInt16 unsigned int

/* ***************************************************** */
// 位定义
/* ***************************************************** */
sbit RS = P3^3;				//数据/命令选择端(H/L)
sbit RW = P3^4;			//数/写选择端(H/L)
sbit EN = P3^5;		//使能信号
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
