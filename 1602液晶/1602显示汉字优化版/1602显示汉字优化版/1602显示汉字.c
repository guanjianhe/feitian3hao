#include <reg52.h>

#define LCD1602_DB  P0
sbit LCD1602_RS = P2^6;
sbit LCD1602_RW = P2^5;
sbit LCD1602_E = P2^7;

unsigned char code tab[]={
				  0x08,0x0f,0x12,0x0f,0x0a,0x1f,0x02,0x02,  //年
                  0x0f,0x09,0x0f,0x09,0x0f,0x09,0x0b,0x11,  //月
                  0x1f,0x11,0x11,0x1f,0x11,0x11,0x1f,0x00,  //日
                  0x07,0x05,0x07,0x00,0x00,0x00,0x00,0x00,   //温度符号
			   };

void InitLcdCn(unsigned char *str);
void InitLcd1602();
void LcdShowCn(unsigned char x, unsigned char y, unsigned char seat);
void LcdShowStr(unsigned char x, unsigned char y, unsigned char *str);
void main()
{
	unsigned char str[] = "Welcome to 51MCU";

	InitLcd1602();
	InitLcdCn(tab);
	LcdShowStr(0, 0, str);
	LcdShowStr(0,1,"2015-01-04- 15`C");
	LcdShowCn(4, 1, 0);		 //显示  ‘年’
	LcdShowCn(7, 1, 1);		 //显示  ‘月’
	LcdShowCn(10, 1, 2);	 //显示  ‘日’
	LcdShowCn(14, 1, 3);	 //显示  ‘·’

	while(1);		
}

void LcdWaitReady()
{
	unsigned char sta;

	LCD1602_E = 0;
	LCD1602_DB = 0xFF;
	LCD1602_RS = 0;
	LCD1602_RW = 1;
	do	{
		LCD1602_E = 1;
		sta = LCD1602_DB;
		LCD1602_E = 0;
	}while(sta & 0x80);
}

void LcdWriteCmd(unsigned char cmd)
{
	LcdWaitReady();
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DB = cmd;
	LCD1602_E = 1;
	LCD1602_E = 0;
}
void LcdWriteDat(unsigned char dat)
{
	LcdWaitReady();
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_DB = dat;
	LCD1602_E = 1;
	LCD1602_E = 0;
}
void LcdSetCursor(unsigned char x, unsigned char y)
{
	unsigned char addr;
	if(y == 0)
		addr = 0x00 + x;
	else
		addr = 0x40 + x;
	LcdWriteCmd(addr | 0x80);
}
void LcdShowStr(unsigned char x, unsigned char y, unsigned char *str)
{
	LcdSetCursor(x, y);
	while(*str != '\0')
	{
		LcdWriteDat(*str++);   
	}
}

void LcdShowCn(unsigned char x, unsigned char y, unsigned char seat)
{
	LcdSetCursor(x, y);
	LcdWriteDat(seat);

}

/*初始化汉字显示*/
void InitLcdCn(unsigned char *str)
{
	unsigned char i;

	LcdWriteCmd(0x40);
	 for(i = 0;i<32;i++)  //连续写入自定义字符串数据
    {
        LcdWriteDat(*str++);
    }
}

void InitLcd1602()
{
	LcdWriteCmd(0x38);
	LcdWriteCmd(0x0C);
	LcdWriteCmd(0x06);
	LcdWriteCmd(0x01);
}