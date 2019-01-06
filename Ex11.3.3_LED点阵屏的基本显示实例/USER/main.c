/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : 点阵屏的基本应用实例
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-09-04
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_LedScreen.h"
#include "FsBSP_Delay.h"

/* ******************************************************************
* 函数名称：void main()
* 入口参数：无
* 出口参数：无
* 函数功能：点阵屏的基本应用实例-实现点亮第一行和第一列点阵屏
****************************************************************** */
void main()
{
    while (1)
		{
			LedScreen_WrOneByte(0x00,0x01);//设置C1~C8为低电平,设置COM0为高电平，则显示结果就是第一行被点亮
			DelayMS(1000);
			LedScreen_WrOneByte(0xFE,0xFF);//设置C1为低电平,C2~C8为高电平,设置COM1~COM7为高电平，则显示结果就是第一列被点亮
			DelayMS(1000);
		}
}

/* *********************************** End of File *********************************** */
