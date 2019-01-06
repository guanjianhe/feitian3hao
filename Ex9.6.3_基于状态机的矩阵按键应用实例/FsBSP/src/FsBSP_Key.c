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

/* ***************************************************** */
// 函数名称：ScanKey(void)
// 函数功能：扫描按键
// 入口参数：无
// 出口参数：键值（num）
/* ***************************************************** */
uChar8 ScanKey(void)
{
	static uChar8 KeyStateTemp = 0,KeyTime = 0;
	uChar8 num;
	bit KeyPressTemp;
	Key0 = 0;
	DelayMS(5);                   //让单片机喘口气，因为STC15的速度太快啦~~
	KeyPressTemp = KEY1;					//读取I/O口的键值
	DelayMS(5);                   //让单片机喘口气，因为STC15的速度太快啦~~
	switch(KeyStateTemp)
	{
		case StateInit:						//按键初始状态
			if(!KeyPressTemp)				//当按键按下，状态切换到确认态
				KeyStateTemp = StateAffirm;
			break;
		case StateAffirm:					//按键确认态
			if(!KeyPressTemp)				//抖动已经消除
			{
				KeyTime = 0;
				KeyStateTemp = StateSingle;	//切换到单次触发态
			}
			else KeyStateTemp = StateInit; 	//还处于抖动状态，切换到初始态
			break;
		case StateSingle:					//按键单发态
			if(KeyPressTemp)				//按下时间小于1s且按键已经释放
			{ 
				KeyStateTemp = StateInit;  	//按键释放，则回到初始态
				num++;						//键值加一
				if(16 == num) 	num = 0;
			}
			else if(++KeyTime > 100)		//按下时间大于1s(100*10ms)
			{
				KeyStateTemp = StateRepeat;	//状态切换到连发态
				KeyTime = 0;	
			}
			break;
		case StateRepeat:					//按键连发态	
			if(KeyPressTemp) 
				KeyStateTemp = StateInit;	//按键释放，则进初始态
			else							//按键未释放
			{
				if(++KeyTime > 10)			//按键计时值大于100ms（10*10ms）
				{
					KeyTime = 0;	
					num++; 					//键值每过100ms加一次
					if(16 == num) 	num = 0;
				}
				break;
			}
			break;
        default:	KeyStateTemp = KeyStateTemp = StateInit; break;
	}
	return num;
}
/* ***************************************************** */
// 函数名称：ExecuteKeyNum()
// 函数功能：按键值来执行相应的动作
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void ExecuteKeyNum(void)
{
	static uChar8 KeyNum = 0;		//提个问题：这里的static能不能省略？为何？
	
	if(TF0)							//定时器是否有溢出？
	{
		TF0 = 0;
		TH0 = 0xDC; 
		TL0 = 0x00;
		KeyNum = ScanKey();			//将KeyScan()函数的返回值赋值给KeyNum。
	}
	switch(KeyNum)
	{
		
		case 0:	g_ucKeyNum = 0; break;
		case 1:	g_ucKeyNum = 1; break;
		case 2:	g_ucKeyNum = 2; break;
		case 3:	g_ucKeyNum = 3; break;
		case 4:	g_ucKeyNum = 4; break;
		case 5:	g_ucKeyNum = 5; break;
		case 6:	g_ucKeyNum = 6; break;
		case 7:	g_ucKeyNum = 7; break;
		case 8:	g_ucKeyNum = 8; break;
		case 9:	g_ucKeyNum = 9; break;
		case 10:	g_ucKeyNum = 10; break;
		case 11:	g_ucKeyNum = 11; break;
		case 12:	g_ucKeyNum = 12; break;
		case 13:	g_ucKeyNum = 13; break;
		case 14:	g_ucKeyNum = 14; break;
		case 15:	g_ucKeyNum = 15; break;
		default:	g_ucKeyNum = 16; break;
	}
	
}
