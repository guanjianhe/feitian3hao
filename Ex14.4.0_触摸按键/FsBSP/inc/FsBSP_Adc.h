#ifndef	__FsBSP_ADC_H__
#define	__FsBSP_ADC_H__

/*************	���س�������	**************/
#define	TOUCH_CHANNEL	8	//ADCͨ����
#define ADC_90T		(3<<5)	//ADCʱ�� 90T
#define ADC_180T	(2<<5)	//ADCʱ�� 180T
#define ADC_360T	(1<<5)	//ADCʱ�� 360T
#define ADC_540T	0		//ADCʱ�� 540T
#define ADC_FLAG	(1<<4)	//�����0
#define ADC_START	(1<<3)	//�Զ���0
extern u16	idata adc[TOUCH_CHANNEL];			//��ǰADCֵ
extern u16	idata adc_prev[TOUCH_CHANNEL];		//��һ��ADCֵ
extern u16	idata TouchZero[TOUCH_CHANNEL];		//0��ADCֵ
extern u8	idata TouchZeroCnt[TOUCH_CHANNEL];	//0���Զ����ټ���
extern void  ADC_init(void);
extern u16	Get_ADC10bitResult(u8 channel)	;//channel = 0~7
extern void	AutoZero(void)	;	//250ms����һ�� ����ʹ������2�������Ĳ�ľ���ֵ֮������⡣
extern u8	check_adc(u8 index)	;	//�жϼ����»��ͷ�,�лز����
#endif