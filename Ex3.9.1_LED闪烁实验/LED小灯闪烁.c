#include "stc15.h"			// 包含STC15的头文件
#include "intrins.h"		// 包含intrins.h头文件，以便延时函数中用

sbit LED11 = P3^6;			// LED11的位定义

void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
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
	while(1)				//	死循环
	{
		LED11 = 0;			// 点亮LED11
		Delay1000ms();		// 延时1000ms
		LED11 = 1;			// 熄灭LED11
		Delay1000ms();		// 延时1000ms
	}
}