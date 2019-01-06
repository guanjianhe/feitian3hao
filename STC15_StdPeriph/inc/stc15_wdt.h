/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : stc15_wdt.H
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-08-29
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 刘平（xymbmcu@163.com）/清华大学出版社/STC MCU International Limited
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#ifndef	__STC15_WDT_H__
#define	__STC15_WDT_H__

#include	"STC15_ClkConfig.h"

#define IDLE_Count 1 
#define IDLE_Stop  0

#define WDT_CLOCK_2T    0	
#define WDT_CLOCK_4T    1	
#define WDT_CLOCK_8T	2
#define WDT_CLOCK_16T	3
#define WDT_CLOCK_32T	4
#define WDT_CLOCK_64T	5
#define WDT_CLOCK_128T  6
#define WDT_CLOCK_256T  7


typedef struct
{
	u8 WDT_EN;                  //看门狗是否允许 						ENABLE,DISABLE
	u8 WDT_IDLE;                //看门狗在IDLE模式位是否计数            IDLE_Count, IDLE_ Stop
    u8 WDT_CLOCK;              //看门狗计数器的预分频                  WDT_CLOCK_2T,	WDT_CLOCK_4T,	WDT_CLOCK_6T,	
                                                                      //WDT_CLOCK_8T,WDT_CLOCK_16T,	WDT_CLOCK_32T,	
                                                                      //WDT_CLOCK_64T,	WDT_CLOCK_128T,WDT_CLOCK_256T
} WDT_InitTypeDef;


extern u8	Wdt_Inilize(WDT_InitTypeDef *WDTx);
extern void	Wdt_EnOrNo(u8 theFlag);
extern void Wdt_Feed(void);

#endif
