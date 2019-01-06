/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : stc15_pwm.c
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
#include	"stc15_pwm.h"

//========================================================================
//u8	PWM_Inilize(PWM_InitTypeDef *PWM)
// 描述:PWM初始化程序
// 参数:u8 PWM_N:PWM路数标号(2~7) PWM: 结构参数,请参考pwm.h里的定义.
// 返回: 成功返回0, 错误返回1
//========================================================================
void PWM_Inilize(u8 PWM_N,PWM_InitTypeDef *PWMx)
{
    P_SW2|=0X80;
    
    if(ENABLE==PWMx->PWM_GOTO_ADC)            //ENABLE=计数器归零时 触发ADC
    {
        PWMCFG|=(1<<7);
    }
    else
    {
        PWMCFG&=(~(1<<7));
    }    
    
    if(PWM_HIGHT==PWMx->PWM_V_INIT)              //PWM_HIGHT=初始高电平 	PWM_LOW=初始低电平 
    {
         PWMCFG|=(1<<PWM_N);
    }
    else
    {
         PWMCFG&=(~(1<<PWM_N));
    }    
    if(ENABLE==PWMx->PWM_0ISR_EN)             //ENABLE=使能PWM计数器归零中断  DISABLE=关闭PWM计数器归零中断 但 CBIF仍然会被硬件置位
    {
        PWMCR|=(1<<6);
    }
    else
    {
        PWMCR&=(~(1<<6));
    }    
    if(ENABLE==PWMx->PWM_OUT_EN)              //ENABLE=PWM通道x的端口为PWM波形输出口 受PWM波形发生器控制
    {
         PWMCR|=(1<<PWM_N);
    }
    else
    {
         PWMCR&=(~(1<<PWM_N));
    }    
    
    if(ENABLE==PWMx->PWM_UNUSUAL_EN)          //ENABLE=使能PWM的外部异常检测功能
    {
         PWMFDCR=(1<<5);
    }
    else
    {
         PWMFDCR&=(~(1<<5));
    }    
    
    if(ENABLE==PWMx->PWM_UNUSUAL_OUT)         //ENABLE=发生异常时，PWM对应的输出口会变成 高阻输入模式
    {
         PWMFDCR=(1<<4);
    }
    else
    {
         PWMFDCR&=(~(1<<4));
    }    
    if(ENABLE==PWMx->PWM_UNUSUAL_ISR_EN)      //ENABLE=使能异常检测中断 DISABLE=关闭异常检测中断 但FDIF仍然会被硬件置位
   {
         PWMFDCR=(1<<3);
    }
    else
    {
         PWMFDCR&=(~(1<<3));
    }    
    if(ENABLE==PWMx->PWM_UNUSUAL_CMP0_EN)     //ENABLE=异常检测源为比较器的输出 当比较结果为高时 触发PWM异常
    {
         PWMFDCR=(1<<2);
    }
    else
    {
         PWMFDCR&=(~(1<<2));
    }    
    if(ENABLE==PWMx->PWM_UNUSUAL_P24_EN)      //ENABLE=异常检测源为P24/PWMFLT 当P24=1 触发PWM异常
    {
         PWMFDCR=(1<<1);
    }
    else
    {
         PWMFDCR&=(~(1<<1));
    }  
    
    PWMCKS=0;
    if(PWM_Clock_NT==PWMx->PWM_CLOCK)               //PWM_Clock_NT=PWM的时钟源是系统时钟经分频后的时钟  PWM_Clock_Timer2_OF=PWM的时钟源是TMER2的溢出脉冲
    {
        PWMCKS&=(~(1<<4));
    }
    else
    {
       PWMCKS|=(1<<4);
    }       
    
    PWMCKS|=PWMx->PWM_CLOCK_DIV;           //当PWM_CLOCK=PWM_Clock_NT时 PWM的时钟源是系统时钟/(PS[3:0]+1)
    switch(PWM_N)
    {
        case PWM_2:      
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
        {
             PWM2CR&=(~(1<<3));
        }
        else
        {
             PWM2CR|=(1<<3);
        }   
        
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
        {
            PWM2CR|=(1<<2);
        }  
        else
        {
             PWM2CR&=(~(1<<2));
        }           
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=使能第一翻转中断
        {
            PWM2CR|=(1<<1);
        }  
        else
        {
             PWM2CR&=(~(1<<1));
        }           
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=使能第二翻转中断
        {
            PWM2CR|=(1<<0);
        }  
        else
        {
             PWM2CR&=(~(1<<0));
        }           
        break;
        
        case PWM_3:      
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
        {
             PWM3CR&=(~(1<<3));
        }
        else
        {
             PWM3CR|=(1<<3);
        }   
        
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
        {
            PWM3CR|=(1<<2);
        }  
        else
        {
             PWM3CR&=(~(1<<2));
        }           
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=使能第一翻转中断
        {
            PWM3CR|=(1<<1);
        }  
        else
        {
             PWM3CR&=(~(1<<1));
        }           
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=使能第二翻转中断
        {
            PWM3CR|=(1<<0);
        }  
        else
        {
             PWM3CR&=(~(1<<0));
        }           
        break;
        
        case PWM_4:      
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
        {
             PWM4CR&=(~(1<<3));
        }
        else
        {
             PWM4CR|=(1<<3);
        }   
        
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
        {
            PWM4CR|=(1<<2);
        }  
        else
        {
             PWM4CR&=(~(1<<2));
        }           
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=使能第一翻转中断
        {
            PWM4CR|=(1<<1);
        }  
        else
        {
            PWM4CR&=(~(1<<1));
        }           
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=使能第二翻转中断
        {
            PWM4CR|=(1<<0);
        }  
        else
        {
            PWM4CR&=(~(1<<0));
        }           
        break;
        
        case PWM_5:      
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
        {
             PWM5CR&=(~(1<<3));
        }
        else
        {
             PWM5CR|=(1<<3);
        }   
        
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
        {
            PWM5CR|=(1<<2);
        }  
        else
        {
             PWM5CR&=(~(1<<2));
        }           
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=使能第一翻转中断
        {
            PWM5CR|=(1<<1);
        }  
        else
        {
             PWM5CR&=(~(1<<1));
        }           
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=使能第二翻转中断
        {
            PWM5CR|=(1<<0);
        }  
        else
        {
            PWM5CR&=(~(1<<0));
        }           
        break;
        
        case PWM_6:      
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
        {
             PWM6CR&=(~(1<<3));
        }
        else
        {
             PWM6CR|=(1<<3);
        }   
        
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
        {
            PWM6CR|=(1<<2);
        }  
        else
        {
             PWM6CR&=(~(1<<2));
        }           
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=使能第一翻转中断
        {
            PWM6CR|=(1<<1);
        }  
        else
        {
            PWM6CR&=(~(1<<1));
        }           
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=使能第二翻转中断
        {
            PWM6CR|=(1<<0);
        }  
        else
        {
            PWM6CR&=(~(1<<0));
        }           
        break;
        
        case PWM_7:      
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
        {
             PWM7CR&=(~(1<<3));
        }
        else
        {
             PWM7CR|=(1<<3);
        }   
        
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
        {
            PWM7CR|=(1<<2);
        }  
        else
        {
            PWM7CR&=(~(1<<2));
        }           
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=使能第一翻转中断
        {
            PWM7CR|=(1<<1);
        }  
        else
        {
            PWM7CR&=(~(1<<1));
        }           
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=使能第二翻转中断
        {
            PWM7CR|=(1<<0);
        }  
        else
        {
            PWM7CR&=(~(1<<0));
        }           
        break;
        
        default:
        break;
    }
    
    if(ENABLE==PWMx->PWM_EN)                  //ENABLE=PWM使能 在其他PWM参数设置好后最后设置 如果被关闭后在打开，则PWM计数器重新从0计数   
    {
        PWMCR|=(1<<7);
    }  
    else
    {
        PWMCR&=(~(1<<7));
    }         
}

/////////////////////////////////////////
//设置PWM周期
u8 PWM_SET_PERIOD(u16 period)
{
    if(0x8000>period)
    {      
        PWMCL=(u8)(period);
        PWMCH=(u8)(period>>8);
        return 0;
    }
    else
    {
        return 1;
    }    
}

/////////////////////////////////////////
//设置PWM第一次和第二次翻转周期
u8 PWM_SET_T12_PERIOD(u8 PWM_N,u16 period1,u16 period2)
{
    switch(PWM_N)
    {
        case PWM_2:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
        
        case PWM_3:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
         
        case PWM_4:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
          
        case PWM_5:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
           
        case PWM_6:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
            
        case PWM_7:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
             
        default:
        return 1;
        break;
    }
}




