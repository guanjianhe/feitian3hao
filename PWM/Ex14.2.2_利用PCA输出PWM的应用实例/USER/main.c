/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : PWM应用实例-脉冲宽度调制模式PCA输出8/7位PWM
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-09-09
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "BSP_Include.h"
#include "STC15_FS.h"

#define CCP_S0 0x10                 //P_SW1.4
#define CCP_S1 0x20                 //P_SW1.5

void main(void)
{
	ACC = P_SW1;
	ACC &= ~(CCP_S0 | CCP_S1);      //CCP_S0=1 CCP_S1=0
	ACC |= CCP_S0;                  //P3.5/CCP0_2、P3.6/CCP1_2，stc15w4k58s4系列只有6路PWM分为三组，每组2路
	P_SW1 = ACC;  

    CCON = 0;                       //初始化PCA控制寄存器/PCA定时器停止/清除CF标志/清除模块中断标志
	
    CL = 0;                         //复位PCA寄存器
    CH = 0;

    CMOD = 0x02;                    //设置PCA时钟源
                                    //禁止PCA定时器溢出中断

    PCA_PWM0 = 0x00;                //PCA模块0工作于8位PWM
    CCAP0H = CCAP0L = 0x20;         //PWM0的占空比为87.5% ((100H-20H)/100H)
    CCAPM0 = 0x42;                  //PCA模块0为8位PWM模式

    PCA_PWM1 = 0x40;                //PCA模块1工作于7位PWM
    CCAP1H = CCAP1L = 0x20;         //PWM1的占空比为75% ((80H-20H)/80H)
    CCAPM1 = 0x42;                  //PCA模块1为7位PWM模式

    CR = 1;                         //PCA定时器开始工作	
	while(1);
}

/* *********************************** End of File *********************************** */
