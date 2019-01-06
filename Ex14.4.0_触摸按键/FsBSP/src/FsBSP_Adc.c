/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : FsBSP_Timer.c
 * �ļ����� : ADC����������
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-09-19
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, �����������ӿƼ����޹�˾/�廪��ѧ������
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#include  "BSP_Include.h"
u16	idata adc[TOUCH_CHANNEL];			//��ǰADCֵ
u16	idata adc_prev[TOUCH_CHANNEL];		//��һ��ADCֵ
u16	idata TouchZero[TOUCH_CHANNEL];		//0��ADCֵ
u8	idata TouchZeroCnt[TOUCH_CHANNEL];	//0���Զ����ټ���

/*************  ADC��ʼ������ *****************/
void  ADC_init(void)
{
	P1ASF = 0xff;		//8·ADC
	ADC_CONTR = 0x80;	//����ADC
}
//========================================================================
// ����: u16	Get_ADC10bitResult(u8 channel)
// ����: ��ѯ����һ��ADC���.
// ����: channel: ѡ��Ҫת����ADC.
// ����: 10λADC���.
// �汾: V1.0, 2012-10-22
//========================================================================
u16	Get_ADC10bitResult(u8 channel)	//channel = 0~7
{
	ADC_RES  = 0;
	ADC_RESL = 0;
	ADC_CONTR = 0x80 | ADC_90T | ADC_START | channel; //����ADC
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	while((ADC_CONTR & ADC_FLAG) == 0)	;	//�ȴ�ADCת������
	ADC_CONTR = 0x80;		//�����־
	return(((u16)ADC_RES << 2) | ((u16)ADC_RESL & 3));	//����ADC���
}
/********************* �Զ�0����ٺ��� *************************/
void	AutoZero(void)		//250ms����һ�� ����ʹ������2�������Ĳ�ľ���ֵ֮������⡣
{
	u8	i;
	u16	j,k;

	for(i=0; i<TOUCH_CHANNEL; i++)		//����8��ͨ��
	{
		j = adc[i];
		k = j - adc_prev[i];			//��ǰһ������
		F0 = 0;								//����
		if(k & 0x8000)	F0 = 1,	k = 0 - k;	//�ͷ�	������β����Ĳ�ֵ
		if(k >= 20)	//�仯�Ƚϴ�
		{
			TouchZeroCnt[i] = 0;			//����仯�Ƚϴ�����0������
			if(F0)	TouchZero[i] = j;		//������ͷţ����ұ仯�Ƚϴ���ֱ�����
		}
		else		//�仯�Ƚ�С�����䶯���Զ�0�����
		{
			if(++TouchZeroCnt[i] >= 20)		//������⵽С�仯20��/4 = 5��.
			{
				TouchZeroCnt[i] = 0;
				TouchZero[i] = adc_prev[i];	//�仯������ֵ��Ϊ0��
			}
		}
		adc_prev[i] = j;	//������һ�εĲ���ֵ
	}
}
/********************* ��ȡ������Ϣ���� 50ms����1�� *************************/
u8	check_adc(u8 index)		//�жϼ����»��ͷ�,�лز����
{
	u16	delta;
	adc[index] = 1023 - Get_ADC10bitResult(index);	//��ȡADCֵ, ת�ɰ��¼�, ADCֵ����
	if(adc[index] < TouchZero[index])	return	0;	//��0�㻹С��ֵ������Ϊ�Ǽ��ͷ�
	delta = adc[index] - TouchZero[index];
	if(delta >= 40)	return 1;	//������
	if(delta <= 20)	return 0;	//���ͷ�
	return	2;		//����ԭ״̬
}
