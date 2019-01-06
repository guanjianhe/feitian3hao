#ifndef	__FsBSP_UART_H__
#define	__FsBSP_UART_H__

#include "STC15.h"
#include <stdio.h>

extern void ConfigUART(unsigned long int baud);
extern void UART_SendString(unsigned char *upStr);
extern void UART_SendOneByte(unsigned char uDat);
extern unsigned char  UART_RecDat();
extern void UART_SendDat();

#endif