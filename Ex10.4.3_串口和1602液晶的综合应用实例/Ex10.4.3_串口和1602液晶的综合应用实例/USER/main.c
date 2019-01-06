/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : main.c
 * 文件描述 : 串口和1602液晶的综合应用实例
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-08-30
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include "FsBSP_AllLedFlash.h"
#include "FsBSP_1602.h"
#include "FsBSP_Delay.h"
#include "FsBSP_Uart.h"
#include "FsBSP_Timer.h"

bit flagBuzzAndLedOn = 0;   //蜂鸣器启动标志

/* ******************************************************************
* 函数名称：bit CmpMemory(unsigned char *ptr1, unsigned char *ptr2, unsigned char len)
* 入口参数：ptr1-待比较指针1，ptr2-待比较指针2，len-待比较长度
* 出口参数：两段内存数据完全相同时返回1，不同返回0
* 函数功能：内存比较函数，比较两个指针所指向的内存数据是否相同
****************************************************************** */
bit CmpMemory(unsigned char *ptr1, unsigned char *ptr2, unsigned char len)
{
    while (len--)
    {
        if (*ptr1++ != *ptr2++)  //遇到不相等数据时即刻返回0
        {
            return 0;
        }
    }
    return 1;  //比较完全部长度数据都相等则返回1
}
/* ******************************************************************
* 函数名称：void UartAction(unsigned char *buf, unsigned char len)
* 入口参数：buf-接收到的命令帧指针，len-命令帧长度
* 出口参数：无
* 函数功能：串口动作函数，根据接收到的命令帧执行响应的动作
****************************************************************** */
void UartAction(unsigned char *buf, unsigned char len)
{
    unsigned char i;
    unsigned char code cmd0[] = "led and buzz on";   //LED和蜂鸣器开命令
    unsigned char code cmd1[] = "led and buzz off";  //LED和蜂鸣器关命令
    unsigned char code cmdLen[] = 
								{          //命令长度汇总表
										sizeof(cmd0)-1, sizeof(cmd1)-1, 
								};
    unsigned char code *cmdPtr[] =
								{         //命令指针汇总表
										&cmd0[0],  &cmd1[0],  
								};

    for (i=0; i<sizeof(cmdLen); i++)  //遍历命令列表，查找相同命令
    {
        if (len >= cmdLen[i])  //首先接收到的数据长度要不小于命令长度
        {
            if (CmpMemory(buf, cmdPtr[i], cmdLen[i]))  //比较相同时退出循环
            {
                break;
            }
        }
    }
    switch (i)  //循环退出时i的值即是当前命令的索引值
    {
        case 0:
            flagBuzzAndLedOn = 1; //开启蜂鸣器和LED灯
			WrComLCD(0x01);			// 清1602液晶屏
			LcdShowStr(0, 0, cmd0);//在1602液晶上第一行第一列开始显示cmd0[]的内容
            break;
        case 1:
            flagBuzzAndLedOn = 0; //关闭蜂鸣器和LED灯
			WrComLCD(0x01);
			LcdShowStr(0, 0, cmd1);//在1602液晶上第一行第一列开始显示cmd1[]的内容
            break;
        default:   //未找到相符命令时，给上机发送“错误命令”的提示
            UartWrite("bad command.\r\n", sizeof("bad command.\r\n")-1);
            return;
    }
    buf[len++] = '\r';  //有效命令被执行后，在原命令帧之后添加
    buf[len++] = '\n';  //回车换行符后返回给上位机，表示已执行
    UartWrite(buf, len);
}
/* ******************************************************************
* 函数名称：void main()
* 入口参数：无
* 出口参数：无
* 函数功能：主函数实现串口和1602的综合应用
****************************************************************** */
void main()
{
	LedGPIO_Init();
	LCD_Init();
    EA = 1;            //开总中断
    Timer0_1ms();      //配置T0定时1ms
    ConfigUART_9600();  //配置波特率为9600
    while (1)
    {
        UartDriver();  //调用串口驱动
    }
}

/* *********************************** End of File *********************************** */
