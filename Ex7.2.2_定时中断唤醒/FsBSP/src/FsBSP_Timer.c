/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : FsBSP_TIMRR.c
 * 文件描述 : 定时器初始化设置函数
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-07-29
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 
 * Copyright (C), 2014-2015, 兰州文轩电子科技有限公司
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_Timer.h"

/* ******************************************************************
* 函数名称：SetWakeUpTime(u16 SetTime)
* 入口参数：SetTime（唤醒需要的时间，单位为ms）
* 出口参数：无
* 函数功能：通过设置相应的寄存器的值，掉电唤醒的时间设置的函数程序
****************************************************************** */

void  SetWakeUpTime(u16 SetTime)
{
    SetTime = (u16)((32768UL * (u32)SetTime) / 16000);  //重装值 = Fwkt/16 * SetTime/1000 = Fwkt * SetTime / 16000
    if(SetTime > 0) SetTime--;
    WKTCL = (u8)SetTime;
    WKTCH = (u8)(SetTime >> 8) | 0x80;
}

