#ifndef	__FsBSP_UART_H__
#define	__FsBSP_UART_H__

#include "STC15.h"


#define uChar8 unsigned char
#define uInt16 unsigned int

extern bit bStatusFlag;

extern void ConfigUART_9600(void);
extern void UartWrite(unsigned char *buf, unsigned char len);
extern unsigned char UartRead(unsigned char *buf, unsigned char len);
extern void UartRxMonitor(unsigned char ms);
extern void UartDriver();
extern void UartAction(unsigned char *buf, unsigned char len);
#endif