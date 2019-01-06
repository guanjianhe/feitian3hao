/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : FsBSP_Key.c
 * 文件描述 : 独立按键或者矩阵按键的驱动程序
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-08-08
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_Key.h"
#include "FsBSP_Delay.h"

/* ****************************************************************************
 * 函数名称：LedGPIO_Init()
 * 入口参数：无
 * 出口参数：无
 * 函数功能：初始化所用端口设置为准双向口
**************************************************************************** */
void GPIO_Init(void)
{
    P4M1 = 0;   
	P4M0 = 0;   //设置为准双向口
}
/* *****************************************************
// 函数名称：ScanKey()
// 函数功能：矩阵按键扫描
// 入口参数：无
// 出口参数：无
// 函数功能：采用行扫描法监测矩阵按键
/* ***************************************************** */
void ScanKey(void)
{
	uChar8 ucTemp;

	KEYPORT = 0xfe;		  			//检测第一行
	ucTemp = KEYPORT;	  			//读取键盘端口数值
	if(ucTemp != 0xfe)		 		//若是不等于0xF0表示有按键按下
	{
		DelayMS(5);                 //去抖
		ucTemp = KEYPORT;			//读端口值
		if(ucTemp != 0xfe)			//再次判断
		{
			ucTemp = KEYPORT;		//取键值
			switch(ucTemp)			//判断键值对应键码
			{
				case 0xee:g_ucKeyNum = 0;break;
				case 0xde:g_ucKeyNum = 1;break;
				case 0xbe:g_ucKeyNum = 2;break;
				case 0x7e:g_ucKeyNum = 3;break;        
			}
			while(KEYPORT != 0xfe);	//按键释放检测
		}
	}	
	KEYPORT = 0xfd;
	ucTemp = KEYPORT;
	if(ucTemp != 0xfd)
	{
		DelayMS(5);
		ucTemp = KEYPORT;
		if(ucTemp != 0xfd)
		{
			ucTemp = KEYPORT;
			switch(ucTemp)
			{
				case 0xed:g_ucKeyNum = 4;break;
				case 0xdd:g_ucKeyNum = 5;break;
				case 0xbd:g_ucKeyNum = 6;break;
				case 0x7d:g_ucKeyNum = 7;break;        
			}
			while(KEYPORT != 0xfd);
		}
	}	
	KEYPORT = 0xfb;
	ucTemp = KEYPORT;
	if(ucTemp != 0xfb)
	{
		DelayMS(5);
		ucTemp = KEYPORT;
		if(ucTemp != 0xfb)
		{
			ucTemp = KEYPORT;
			switch(ucTemp)
			{
				case 0xeb:g_ucKeyNum = 8;break;
				case 0xdb:g_ucKeyNum = 9;break;
				case 0xbb:g_ucKeyNum = 10;break;
				case 0x7b:g_ucKeyNum = 11;break;        
			}
			while(KEYPORT != 0xfb);
		}
	}	
	KEYPORT = 0xf7;
	ucTemp = KEYPORT;
	if(ucTemp != 0xf7)
	{
		DelayMS(5);                   
		ucTemp = KEYPORT;
		if(ucTemp != 0xf7)
		{
			ucTemp = KEYPORT;
			switch(ucTemp)
			{
				case 0xe7:g_ucKeyNum = 12;break;
				case 0xd7:g_ucKeyNum = 13;break;
				case 0xb7:g_ucKeyNum = 14;break;
				case 0x77:g_ucKeyNum = 15;break;        
			}
			while(KEYPORT != 0xf7);
		}
	}
}
