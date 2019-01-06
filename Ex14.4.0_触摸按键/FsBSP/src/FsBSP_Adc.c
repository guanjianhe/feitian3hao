/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : FsBSP_Timer.c
 * 文件描述 : ADC的驱动程序
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-09-19
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 兰州文轩电子科技有限公司/清华大学出版社
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#include  "BSP_Include.h"
u16	idata adc[TOUCH_CHANNEL];			//当前ADC值
u16	idata adc_prev[TOUCH_CHANNEL];		//上一个ADC值
u16	idata TouchZero[TOUCH_CHANNEL];		//0点ADC值
u8	idata TouchZeroCnt[TOUCH_CHANNEL];	//0点自动跟踪计数

/*************  ADC初始化函数 *****************/
void  ADC_init(void)
{
	P1ASF = 0xff;		//8路ADC
	ADC_CONTR = 0x80;	//允许ADC
}
//========================================================================
// 函数: u16	Get_ADC10bitResult(u8 channel)
// 描述: 查询法读一次ADC结果.
// 参数: channel: 选择要转换的ADC.
// 返回: 10位ADC结果.
// 版本: V1.0, 2012-10-22
//========================================================================
u16	Get_ADC10bitResult(u8 channel)	//channel = 0~7
{
	ADC_RES  = 0;
	ADC_RESL = 0;
	ADC_CONTR = 0x80 | ADC_90T | ADC_START | channel; //触发ADC
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	while((ADC_CONTR & ADC_FLAG) == 0)	;	//等待ADC转换结束
	ADC_CONTR = 0x80;		//清除标志
	return(((u16)ADC_RES << 2) | ((u16)ADC_RESL & 3));	//返回ADC结果
}
/********************* 自动0点跟踪函数 *************************/
void	AutoZero(void)		//250ms调用一次 这是使用相邻2个采样的差的绝对值之和来检测。
{
	u8	i;
	u16	j,k;

	for(i=0; i<TOUCH_CHANNEL; i++)		//处理8个通道
	{
		j = adc[i];
		k = j - adc_prev[i];			//减前一个读数
		F0 = 0;								//按下
		if(k & 0x8000)	F0 = 1,	k = 0 - k;	//释放	求出两次采样的差值
		if(k >= 20)	//变化比较大
		{
			TouchZeroCnt[i] = 0;			//如果变化比较大，则清0计数器
			if(F0)	TouchZero[i] = j;		//如果是释放，并且变化比较大，则直接替代
		}
		else		//变化比较小，则蠕动，自动0点跟踪
		{
			if(++TouchZeroCnt[i] >= 20)		//连续检测到小变化20次/4 = 5秒.
			{
				TouchZeroCnt[i] = 0;
				TouchZero[i] = adc_prev[i];	//变化缓慢的值作为0点
			}
		}
		adc_prev[i] = j;	//保存这一次的采样值
	}
}
/********************* 获取触摸信息函数 50ms调用1次 *************************/
u8	check_adc(u8 index)		//判断键按下或释放,有回差控制
{
	u16	delta;
	adc[index] = 1023 - Get_ADC10bitResult(index);	//获取ADC值, 转成按下键, ADC值增加
	if(adc[index] < TouchZero[index])	return	0;	//比0点还小的值，则认为是键释放
	delta = adc[index] - TouchZero[index];
	if(delta >= 40)	return 1;	//键按下
	if(delta <= 20)	return 0;	//键释放
	return	2;		//保持原状态
}
