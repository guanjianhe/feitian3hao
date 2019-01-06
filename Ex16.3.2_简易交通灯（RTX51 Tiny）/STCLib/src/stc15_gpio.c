/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : STC15_GPIO.c
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-08-12
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 文件说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 刘平（xymbmcu@163.com）/清华大学出版社/STC MCU Limited
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "stc15_gpio.h"

//========================================================================
// 函数: u8	GPIO_Inilize(u8 GPIO, GPIO_InitTypeDef *GPIOx)
// 描述: 初始化IO口.
// 参数: GPIOx: 结构参数,请参考gpio.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
// 版本: V1.0, 2012-10-22
//========================================================================
u8	GPIO_Inilize(u8 GPIO, GPIO_InitTypeDef *GPIOx)
{
	if(GPIO > GPIO_P7)				return 1;	//空操作
	if(GPIOx->Mode > GPIO_OUT_PP)	return 2;	//错误

	if(GPIO == GPIO_P0)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P0M1 &= ~GPIOx->Pin,	P0M0 &= ~GPIOx->Pin;	 //上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P0M1 |=  GPIOx->Pin,	P0M0 &= ~GPIOx->Pin;	 //浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P0M1 |=  GPIOx->Pin,	P0M0 |=  GPIOx->Pin;	 //开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P0M1 &= ~GPIOx->Pin,	P0M0 |=  GPIOx->Pin;	 //推挽输出
	}
	if(GPIO == GPIO_P1)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P1M1 &= ~GPIOx->Pin,	P1M0 &= ~GPIOx->Pin;	 //上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P1M1 |=  GPIOx->Pin,	P1M0 &= ~GPIOx->Pin;	 //浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P1M1 |=  GPIOx->Pin,	P1M0 |=  GPIOx->Pin;	 //开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P1M1 &= ~GPIOx->Pin,	P1M0 |=  GPIOx->Pin;	 //推挽输出
	}
	if(GPIO == GPIO_P2)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P2M1 &= ~GPIOx->Pin,	P2M0 &= ~GPIOx->Pin;	 //上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P2M1 |=  GPIOx->Pin,	P2M0 &= ~GPIOx->Pin;	 //浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P2M1 |=  GPIOx->Pin,	P2M0 |=  GPIOx->Pin;	 //开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P2M1 &= ~GPIOx->Pin,	P2M0 |=  GPIOx->Pin;	 //推挽输出
	}
	if(GPIO == GPIO_P3)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P3M1 &= ~GPIOx->Pin,	P3M0 &= ~GPIOx->Pin;	 //上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P3M1 |=  GPIOx->Pin,	P3M0 &= ~GPIOx->Pin;	 //浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P3M1 |=  GPIOx->Pin,	P3M0 |=  GPIOx->Pin;	 //开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P3M1 &= ~GPIOx->Pin,	P3M0 |=  GPIOx->Pin;	 //推挽输出
	}
	if(GPIO == GPIO_P4)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P4M1 &= ~GPIOx->Pin,	P4M0 &= ~GPIOx->Pin;	 //上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P4M1 |=  GPIOx->Pin,	P4M0 &= ~GPIOx->Pin;	 //浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P4M1 |=  GPIOx->Pin,	P4M0 |=  GPIOx->Pin;	 //开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P4M1 &= ~GPIOx->Pin,	P4M0 |=  GPIOx->Pin;	 //推挽输出
	}
	if(GPIO == GPIO_P5)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P5M1 &= ~GPIOx->Pin,	P5M0 &= ~GPIOx->Pin;	 //上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P5M1 |=  GPIOx->Pin,	P5M0 &= ~GPIOx->Pin;	 //浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P5M1 |=  GPIOx->Pin,	P5M0 |=  GPIOx->Pin;	 //开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P5M1 &= ~GPIOx->Pin,	P5M0 |=  GPIOx->Pin;	 //推挽输出
	}
	if(GPIO == GPIO_P6)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P6M1 &= ~GPIOx->Pin,	P6M0 &= ~GPIOx->Pin;	 //上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P6M1 |=  GPIOx->Pin,	P6M0 &= ~GPIOx->Pin;	 //浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P6M1 |=  GPIOx->Pin,	P6M0 |=  GPIOx->Pin;	 //开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P6M1 &= ~GPIOx->Pin,	P6M0 |=  GPIOx->Pin;	 //推挽输出
	}
	if(GPIO == GPIO_P7)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P7M1 &= ~GPIOx->Pin,	P7M0 &= ~GPIOx->Pin;	 //上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P7M1 |=  GPIOx->Pin,	P7M0 &= ~GPIOx->Pin;	 //浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P7M1 |=  GPIOx->Pin,	P7M0 |=  GPIOx->Pin;	 //开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P7M1 &= ~GPIOx->Pin,	P7M0 |=  GPIOx->Pin;	 //推挽输出
	}
	
	return 0;	//成功
}

/* ****************************************************************************
 * 函数名称：GPIO_PWMInit()
 * 入口参数：GPIO_PWM(PWM端口号：2~7)，PuHzOdPp（端口的状态）
 * 出口参数：函数操作返回值（成功返回0, 空操作返回1）
 * 函数功能：初始化PWM端口(说明：PWM有关的IO口上电后都是高阻输入态)
**************************************************************************** */
u8 GPIO_PWMInit(u8 GPIO_PWM,u8 PuHzOdPp)
{
    GPIO_InitTypeDef	GPIO_InitStructure;		        //结构定义

    switch(GPIO_PWM)
    {
        case GPIO_PWM2:
        GPIO_InitStructure.Pin  = GPIO_Pin_7;
        GPIO_InitStructure.Mode = PuHzOdPp;		            //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	        
        break;
        case GPIO_PWM3:
        GPIO_InitStructure.Pin  = GPIO_Pin_1;
        GPIO_InitStructure.Mode = PuHzOdPp;		            //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);	        
        break;
        case GPIO_PWM4:
        GPIO_InitStructure.Pin  = GPIO_Pin_2;
        GPIO_InitStructure.Mode = PuHzOdPp;		            //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);	        
        break;
        case GPIO_PWM5:
        GPIO_InitStructure.Pin  = GPIO_Pin_3;
        GPIO_InitStructure.Mode = PuHzOdPp;		            //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);	        
        break;
        case GPIO_PWM6:
        GPIO_InitStructure.Pin  = GPIO_Pin_6;
        GPIO_InitStructure.Mode = PuHzOdPp;		            //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);	        
        break;
        case GPIO_PWM7:
        GPIO_InitStructure.Pin  = GPIO_Pin_7;
        GPIO_InitStructure.Mode = PuHzOdPp;		            //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);	        
        break;
        
        default:
        return 1;
        break;
    }
    return 0;
}

/* 将其IIC端口初始化为准双向口 */
void GPIO_ConfigInit(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		        //结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;	//0 2 管脚
	GPIO_InitStructure.Mode = GPIO_PullUp;		        //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5,&GPIO_InitStructure);	        //初始化
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);
}
