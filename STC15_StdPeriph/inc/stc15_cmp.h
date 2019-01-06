/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : stc15_cmp.H
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

#ifndef	__stc15_cmp_H__
#define	__stc15_cmp_H__

#include	"STC15_ClkConfig.h"

//u8  CmpV;	比较器正极设置
//只能是比较器正极选P55


//u8  CmpG; 比较器负极设置
#define	CMP_CMPG_P54		1       /*比较器负极选P54*/ 
#define	CMP_CMPG_BGV        0       /*比较器负极选BGV 1.27V附近*/ 

//u8	CmpoResult;	//输出结果选择
#define CMP_CMPO_P12NOR   1          /*比较器结果正常输出P12*/ 
#define CMP_CMPO_P12INV   2          /*比较器结果取反再输出P12*/ 
#define CMP_CMPO_NO       3          /*比较器结果不输出到外部管脚P12*/ 

//CMP中断标志清零
#define CMP_IF_CLR     CMPCR1&=(~(1<<6))

typedef struct
{	
    u8  Power;      //ENABLE=使能CMP  DISABLE=禁止CMP
    u8  Rise;       //ENABLE=上升沿中断
    u8  Fall;	    //ENABLE=下降沿中断
    u8  CmpG;	    //比较器负极设置
    u8  Disflt;	    //ENABLE=关掉比较器输出的0.1us Filter   DISABLE=比较器输出有0.1us Filter
    u8	CmpoResult;	//输出结果选择
    u8	Lcdty5;	    //比较器输出端 跳变沿后维持电平时间选择 单位一个时钟周期
} CMP_InitTypeDef;

extern u8	CMP_Inilize     (CMP_InitTypeDef *CMP);
extern u8   CMP_ReadResult  (void);

#endif
