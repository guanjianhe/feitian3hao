#include "stc15.h"
#include "intrins.h"

sbit LED9  = P5^4;
sbit LED10 = P5^5;
sbit LED11 = P3^6;
sbit LED12 = P3^7;

void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
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
	
	P3M0 = 0x00;				// 设置其P3口为准双向I/O口
    P3M1 = 0x00;
	
	while(1)
	{
		P7 = 0xFE;				// 点亮LED1
		Delay100ms();			// 延时一小会
		for (i = 0; i < 7; i++)	// 循环7次
		{						// 依次点亮LED2~LED8
			P7 = _crol_(P7,1) ;	// 调用移位函数
			Delay100ms();		// 延时一小会
		}
		P7 = 0xFF;			// 熄灭LED1~LED8
		
		LED9  = 0;			// 点亮LED9
		Delay100ms();		// 延时一小会
		LED9  = 1;			// 熄灭LED9
		LED10 = 0;			// 点亮LED10
		Delay100ms();		// 延时一小会
		LED10 = 1;			// 熄灭LED10
		LED11 = 0;			// 点亮LED11
		Delay100ms();		// 延时一小会
		LED11 = 1;			// 熄灭LED11
		LED12 = 0;			// 点亮LED12
		Delay100ms();		// 延时一小会
		LED12 = 1;			// 熄灭LED12
	}
}