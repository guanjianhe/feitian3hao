/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : stc15_iic.h
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
#ifndef __STC15_IIC_H__
#define __STC15_IIC_H__

#include	"STC15_ClkVarType.h"

/* ***************************************************** */
// 请根据自行的硬件平台自行修改
// 这里以FSST15-v1.0开发板为例
/* ***************************************************** */
sbit SCL = P2^0;	 // EEPROM时钟线
sbit SDA = P2^2;	 // EEPROM数据线
/* ***************************************************** */

#define IIC_WRITE 0
#define IIC_READ  1

extern void Delay5US(void);
extern void IIC_Start(void);
extern void IIC_Stop(void);
extern void IIC_Ack(void);
extern u8 IIC_RdAck(void);
extern void IIC_Nack(void);
extern u8 OutputOneByte(void);
extern void InputOneByte(u8 uByteVal);
extern u8 IIC_WrDevAddAndDatAdd(u8 uDevAdd,u8 uDatAdd);
extern void IIC_WrDatToAdd(u8 uDevID, u8 uStaAddVal, u8 *p, u8 ucLenVal);
extern void IIC_RdDatFromAdd(u8 uDevID, u8 uStaAddVal, u8 *p, u8 uiLenVal);

#endif
