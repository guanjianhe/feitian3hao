#include "stc15.h"
#include "intrins.h"

sbit LED9  = P5^4;
sbit LED10 = P5^5;
sbit LED11 = P3^6;
sbit LED12 = P3^7;

void Delay100ms()		//@22.1184MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 9;
	j = 104;
	k = 139;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main(void)
{
	unsigned char i = 0;
	
	P3M0 = 0x00;
    P3M1 = 0x00;
	
	while(1)
	{
		P7 = 0xFF;
		LED9  = 1;
		LED10 = 1;
		LED11 = 1;
		LED12 = 1;
		Delay100ms();
		for (i = 0; i < 8; i++)
		{
			P7 <<= 1;
			Delay100ms();
		}
		LED9  = 0;Delay100ms();
		LED10 = 0;Delay100ms();
		LED11 = 0;Delay100ms();
		LED12 = 0;Delay100ms();
	}
}