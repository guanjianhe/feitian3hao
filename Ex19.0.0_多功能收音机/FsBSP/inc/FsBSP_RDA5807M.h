/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 ：FsBSP_RDA5807M.h
 * 文件描述 ：RDA5807M收音机头文件
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号 ：V1.0 	   					
 * 修改日期 ：2015-09-16
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#ifndef __FSBSP_RDA5807M_H__
#define __FSBSP_RDA5807M_H__

#include "stc15_delay.h"
#include "stc15_iic.h"

#define RDA5807M_WrDevAddr		0x20
#define RDA5807M_RdDevAddr		0x21

extern void RDA5807M_PowerOnAndInit(void);
extern void RDA5807M_AutoSeek(bit bUpAndDown);
extern void RDA5807M_SetVolume(bit bUpAndDown);

#endif