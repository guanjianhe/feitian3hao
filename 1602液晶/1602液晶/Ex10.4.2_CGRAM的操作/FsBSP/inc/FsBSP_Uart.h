#ifndef	__FsBSP_UART_H__
#define	__FsBSP_UART_H__

#include "STC15.h"
#include <stdio.h>

#define uChar8 unsigned char
#define uInt16 unsigned int

extern bit bStatusFlag;

extern void ConfigUART(unsigned int baud);
extern void UART_SendString(unsigned char *upStr);
extern void UART_SendOneByte(unsigned char uDat);
extern unsigned char  UART_RecDat();
extern void UART_SendDat();

#endif