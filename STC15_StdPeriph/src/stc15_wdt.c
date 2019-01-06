/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : stc15_wdt.c
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

#include	"stc15_wdt.h"

//========================================================================
//u8	Wdt_Inilize(WDT_InitTypeDef *WDTx)
// 描述: 看门狗初始化程序.
// 参数: WDTx: 结构参数,请参考wdt.h里的定义.
// 返回: 成功返回0, 错误返回2
//========================================================================
u8	Wdt_Inilize(WDT_InitTypeDef *WDTx)
{
   if(IDLE_Count==WDTx->WDT_IDLE)
   {
        WDT_CONTR|=(1<<3);      //IDLE模式计数 
   }
   else if(IDLE_Stop==WDTx->WDT_IDLE)
   {
        WDT_CONTR&=(~(1<<3));   //IDLE模式不计数 
   } 
   else
   {
        return 2;
   }  
   
   if(7>=WDTx->WDT_CLOCK)
   {
        WDT_CONTR&=(~0x07);
        WDT_CONTR|=WDTx->WDT_CLOCK;  //设定看门狗计数器的预分频值  
   }
   else
   {
        return 2;
   }   

   if(ENABLE==WDTx->WDT_EN)
   {
        WDT_CONTR|=(1<<5);      //允许看门狗
   }
   else if(DISABLE==WDTx->WDT_EN)
   {
        WDT_CONTR&=(~(1<<5));   //禁止看门狗
   } 
   else
   {
        return 2;
   }       

   return	0;		//成功
}


//========================================================================
//void	Wdt_EnOrNo(u8 theFlag)
// 描述: 看门狗允许/禁止函数
//形式参数 u8 theFlag 0=禁止  1=允许
//========================================================================
void	Wdt_EnOrNo(u8 theFlag)
{
   if(1==theFlag)
   {
        WDT_CONTR|=(1<<5);      //允许看门狗
   }
   else
   {
        WDT_CONTR&=(~(1<<5));   //禁止看门狗
   } 
}

//========================================================================
//void	Wdt_EnOrNo(u8 theFlag)
// 描述: 看门狗允许/禁止函数
//形式参数 u8 theFlag 0=禁止  1=允许
//========================================================================
void Wdt_Feed(void)
{
    WDT_CONTR|=(1<<4);      //喂狗
}



