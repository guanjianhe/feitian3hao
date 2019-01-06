/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : stc15_wdt.H
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-08-29
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, ��ƽ��xymbmcu@163.com��/�廪��ѧ������/STC MCU International Limited
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#ifndef	__STC15_WDT_H__
#define	__STC15_WDT_H__

#include	"STC15_ClkConfig.h"

#define IDLE_Count 1 
#define IDLE_Stop  0

#define WDT_CLOCK_2T    0	
#define WDT_CLOCK_4T    1	
#define WDT_CLOCK_8T	2
#define WDT_CLOCK_16T	3
#define WDT_CLOCK_32T	4
#define WDT_CLOCK_64T	5
#define WDT_CLOCK_128T  6
#define WDT_CLOCK_256T  7


typedef struct
{
	u8 WDT_EN;                  //���Ź��Ƿ����� 						ENABLE,DISABLE
	u8 WDT_IDLE;                //���Ź���IDLEģʽλ�Ƿ����            IDLE_Count, IDLE_ Stop
    u8 WDT_CLOCK;              //���Ź���������Ԥ��Ƶ                  WDT_CLOCK_2T,	WDT_CLOCK_4T,	WDT_CLOCK_6T,	
                                                                      //WDT_CLOCK_8T,WDT_CLOCK_16T,	WDT_CLOCK_32T,	
                                                                      //WDT_CLOCK_64T,	WDT_CLOCK_128T,WDT_CLOCK_256T
} WDT_InitTypeDef;


extern u8	Wdt_Inilize(WDT_InitTypeDef *WDTx);
extern void	Wdt_EnOrNo(u8 theFlag);
extern void Wdt_Feed(void);

#endif
