#include "reg52.h"

sfr  P7   = 0xF8;
sbit LED1 = P7^0;

void main(void)
{
	LED1 = 0;
	while(1);
}