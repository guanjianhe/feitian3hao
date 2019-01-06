/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : stc15_cmp.c
 * 文件描述 : STC系列单片机头文件
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

#include	"stc15_cmp.h"

//========================================================================
// 函数: u8	CMP_Inilize(CMP_InitTypeDef *CMP)
// 描述: 初始化电压比较器
// 参数:CMP: 结构参数,请参考cmp.h里的定义.
// 返回: 成功返回0, 空操作返回1
//========================================================================
u8	CMP_Inilize(CMP_InitTypeDef *CMP)
{   
    CMP_IF_CLR;                  //CMP中断标志清零
    
    if(0x20 > CMP->Lcdty5)
    {
         CMPCR2 &= (~0x1F);
         CMPCR2 |= CMP->Lcdty5;    //比较器输出端 跳变沿后维持电平时间选择 单位一个时钟周期
    }
    else
    {
        return 1;                           //失败?
    }    
    
    CMPCR1 &= (~(1 << 3));  //比较器正极只能选P55
      
    if(CMP_CMPG_P54 == CMP->CmpG)
    {
        CMPCR1 |= 1 << 3;       //比较器负极选P54
    }
    else if(CMP_CMPG_BGV == CMP->CmpG)
    {
        CMPCR1 &= (~(1 << 3));  //比较器负极选BGV 1.27V附近
    }
    else
    {
        return 1;           //失败?
    }
    
    if(ENABLE == CMP->Rise)    //上升沿中断
    {
        CMPCR1 |= 1 << 5;                   //使能
    }
    else if(DISABLE == CMP->Rise)   
    {
        CMPCR1 &= (~(1<<5));              //禁止
    }
    else
    {
        return 1;                       //失败?
    }
    
    if(ENABLE == CMP->Fall)    //下降沿中断
    {
        CMPCR1 |= 1 << 4;                   //使能
    }
    else if(DISABLE == CMP->Fall)
    {
        CMPCR1 &= (~(1 << 4));              //禁止
    }
    else
    {
        return 1;                       //失败?
    }
    
    if(ENABLE == CMP->Disflt)  //关于0.1us Filter
    {
        CMPCR2 |= 1 << 6;                   //关掉比较器输出的0.1us Filter
    }
    else if(DISABLE==CMP->Disflt)
    {
        CMPCR2 &= (~(1 << 6));              //比较器输出有0.1us Filter
    }
    else
    {
        return 1;                       	//失败
    }

    switch (CMP->CmpoResult)
    {           
        case CMP_CMPO_P12NOR:  //比较器结果正常输出P12
        CMPCR2 &= (~(1 << 7));
        CMPCR1 |= 1 << 1;
        break;
        
        case CMP_CMPO_P12INV:   //比较器结果取反再输出P12
        CMPCR2 |= 1 << 7;
        CMPCR1 |= 1 << 1;      
        break;
          
        case CMP_CMPO_NO:       //比较器结果不输出到外部管脚P12
        CMPCR1 &= (~(1 << 1));
        break;
                 
        default:
        return 1;               //失败?
        break;
    }
    
	if(ENABLE == CMP->Power)
    {
        CMPCR1 |= 1 << 7;           //开启CMP 开启比较器电源
    }
    else if(DISABLE == CMP->Power)
    {
        CMPCR1 &= (~(1 << 7));      //禁止CMP 关闭比较器电源
    }
    else
    {
        return 1; 		//失败
    }
    
	return 0;			//成功
}


///////////////////////////////
//读CMP比较结果
//返回比较结果 
//1=CMP+ > CMP-
//0=CMP+ < CMP-
u8 CMP_ReadResult(void)
{
    if(0x01 == (CMPCR1 & (0x01)))
    {
        return 1;
    }
    else
    { 
        return 0;
    }        
}

void CMP_ISR(void) interrupt CMP_VECTOR
{
	CMP_IF_CLR;
}

