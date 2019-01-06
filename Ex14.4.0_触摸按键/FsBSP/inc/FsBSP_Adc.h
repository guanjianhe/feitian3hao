#ifndef	__FsBSP_ADC_H__
#define	__FsBSP_ADC_H__

/*************	本地常量声明	**************/
#define	TOUCH_CHANNEL	8	//ADC通道数
#define ADC_90T		(3<<5)	//ADC时间 90T
#define ADC_180T	(2<<5)	//ADC时间 180T
#define ADC_360T	(1<<5)	//ADC时间 360T
#define ADC_540T	0		//ADC时间 540T
#define ADC_FLAG	(1<<4)	//软件清0
#define ADC_START	(1<<3)	//自动清0
extern u16	idata adc[TOUCH_CHANNEL];			//当前ADC值
extern u16	idata adc_prev[TOUCH_CHANNEL];		//上一个ADC值
extern u16	idata TouchZero[TOUCH_CHANNEL];		//0点ADC值
extern u8	idata TouchZeroCnt[TOUCH_CHANNEL];	//0点自动跟踪计数
extern void  ADC_init(void);
extern u16	Get_ADC10bitResult(u8 channel)	;//channel = 0~7
extern void	AutoZero(void)	;	//250ms调用一次 这是使用相邻2个采样的差的绝对值之和来检测。
extern u8	check_adc(u8 index)	;	//判断键按下或释放,有回差控制
#endif