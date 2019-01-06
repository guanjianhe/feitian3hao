#ifndef	__FsBSP_UART_H__
#define	__FsBSP_UART_H__

#include "STC15.h"


extern void UART1_Init();
extern void UART_SendString(unsigned char *upStr);
extern void UART_SendOneByte(unsigned char uDat);


#endif