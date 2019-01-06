/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : main.c
 * �ļ����� : 1602Һ���Ļ���Ӧ��ʵ��
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-08-30
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, �����������ӿƼ����޹�˾/�廪��ѧ������
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

/////////////////////////////////
//ͷ�ļ�
#include	"BSP_Include.h"

/////////////////////////////////
//LED�ܽ�Ԥ����
#define     LED1    P70
#define     LED2    P71
#define     LED3    P72   
#define     LED4    P73  
/*************	����˵��	**************
��תADC��ť 
4��LED����ݵ�ѹ�Ĵ�С ����ʾ4λʮ�����Ƶ���������
LED1�����λ LED4�����λ
����ť����ѹԽ��LED1234���ֵ�4λʮ����������Խ��
LCD1602��һ�л���ʾ10λ��ʵ�Ĳ���ֵ
LCD1602�ڶ��л���ʾ�Ŵ�10�������ʵ��ѹֵ
******************************************/

void	GPIO_config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.Mode=GPIO_OUT_PP;
    GPIO_InitStructure.Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
    GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);//LED��IO��ʼ��

    GPIO_InitStructure.Mode=GPIO_OUT_PP;
    GPIO_InitStructure.Pin=GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
    GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);//1602Һ�����ƹܽ�IO��ʼ��
	
	GPIO_InitStructure.Mode=GPIO_PullUp;
    GPIO_InitStructure.Pin=GPIO_Pin_All;
    GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);//1602Һ��DB�ܽ�IO��ʼ��
    
    GPIO_InitStructure.Mode=GPIO_HighZ;
    GPIO_InitStructure.Pin=GPIO_Pin_6;
    GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);//ADC�ܽ�IO��ʼ��
}

void	ADC_config(void)
{
	ADC_InitTypeDef		ADC_InitStructure;				//�ṹ����
	ADC_InitStructure.ADC_Px        = ADC_P15 ;	        //����Ҫ��ADC��IO
	ADC_InitStructure.ADC_Speed     = ADC_360T;			//ADC�ٶ�			ADC_90T,ADC_180T,ADC_360T,ADC_540T
	ADC_InitStructure.ADC_Power     = DISABLE;			//ADC��������/�ر�	ENABLE,DISABLE
	ADC_InitStructure.ADC_AdjResult = ADC_RES_H8L2;		//ADC�������,	ADC_RES_H2L8,ADC_RES_H8L2
	ADC_InitStructure.ADC_Polity    = PolityLow;		//���ȼ�����	PolityHigh,PolityLow
	ADC_InitStructure.ADC_Interrupt = DISABLE;			//�ж�����		ENABLE,DISABLE
	ADC_Inilize(&ADC_InitStructure);					//��ʼ��
	ADC_PowerControl(ENABLE);							//������ADC��Դ��������, ENABLE��DISABLE
}
/**********************************************/
void main(void)
{		
	u8	j;
	u16 k;
	ADC_config();
	Delay_ms(100);
	GPIO_config();
	Delay_ms(100);
	Dispaly_1602();   //1602����ʾ����
	Delay_ms(100);
	while (1)
	{	  
			
        k = Get_ADC10bitResult(5);	//����0~7,��ѯ��ʽ��һ��ADC, ����ֵ���ǽ��, == 1024 Ϊ����
		Delay_ms(100);
	    display_num(k);//1602����ʾ����-1024��ʵ�Ĳ���ֵ
        Delay_ms(100);
	    display_Voltage_value(k);//1602����ʾ����-�Ŵ�ʮ������ʵ������ѹֵ
		Delay_ms(100);
        j=k>>6;//���Ҷ�������ݱ��4λ����ֵ--ȡ����ǰ4λ 
        if(1==(j&0x01))
        {
            LED1=0;
        } 
        else
        {
            LED1=1;
        }
      
        if(0X02==(j&0x02))
        {
            LED2=0;
        } 
        else
        {
            LED2=1;
        }
     
        if(0X04==(j&0x04))
        {
            LED3=0;
        } 
        else
        {
            LED3=1;
        }
       
        if(0X08==(j&0x08))
        {
            LED4=0;
        } 
        else
        {
            LED4=1;
        }
        Delay_ms(200);
	}
}

/* *********************************** End of File *********************************** */

