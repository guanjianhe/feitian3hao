/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : STC15_GPIO.h
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-08-11
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 文件说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 刘平（xymbmcu@163.com）/清华大学出版社/STC MCU Limited
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#ifndef	__STC15_GPIO_H__
#define	__STC15_GPIO_H__

#include  "STC15_CLKVARTYPE.H"

/* ********************************************************
 * I/O类型选择，分别对应四种工作模式
 ******************************************************* */
#define	GPIO_PullUp		0		// 上拉准双向口
#define	GPIO_HighZ		1		// 浮空输入
#define	GPIO_OUT_OD		2		// 开漏输出
#define	GPIO_OUT_PP		3		// 推挽输出
/* ********************************************************
 * 端口位选择，分别对应9种模式
 ******************************************************* */
#define	GPIO_Pin_0		0x01	// IO引脚 Px.0
#define	GPIO_Pin_1		0x02	// IO引脚 Px.1
#define	GPIO_Pin_2		0x04	// IO引脚 Px.2
#define	GPIO_Pin_3		0x08	// IO引脚 Px.3
#define	GPIO_Pin_4		0x10	// IO引脚 Px.4
#define	GPIO_Pin_5		0x20	// IO引脚 Px.5
#define	GPIO_Pin_6		0x40	// IO引脚 Px.6
#define	GPIO_Pin_7		0x80	// IO引脚 Px.7
#define	GPIO_Pin_All	0xFF	// IO所有引脚
/* ********************************************************
 * 端口选择，分别对应8个端口
 ******************************************************* */	
#define	GPIO_P0		0		
#define	GPIO_P1		1
#define	GPIO_P2		2
#define	GPIO_P3		3
#define	GPIO_P4		4
#define	GPIO_P5		5
#define	GPIO_P6		6
#define	GPIO_P7		7
/* ********************************************************
 * 选择PWM端口，对应6个PWM输出端口
 ******************************************************* */	
#define	GPIO_PWM2       2
#define	GPIO_PWM3       3
#define	GPIO_PWM4       4
#define	GPIO_PWM5       5
#define	GPIO_PWM6       6
#define	GPIO_PWM7       7

typedef struct
{
	uint8	Mode;	// IO对应四种（GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP）模式
	uint8	Pin;	// 要设置的端口	
} GPIO_InitTypeDef;

u8 GPIO_Init(u8 GPIO, GPIO_InitTypeDef *GPIOx);

extern uint8 GPIO_PWMInit(uint8 GPIO_PWM, uint8 PuHzOdPp);

/* 将其IIC端口初始化为准双向口 */
void GPIO_ConfigInit(void);

#endif
