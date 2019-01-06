/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : stc15_cmp.H
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

#ifndef	__stc15_cmp_H__
#define	__stc15_cmp_H__

#include	"STC15_ClkConfig.h"

//u8  CmpV;	�Ƚ�����������
//ֻ���ǱȽ�������ѡP55


//u8  CmpG; �Ƚ�����������
#define	CMP_CMPG_P54		1       /*�Ƚ�������ѡP54*/ 
#define	CMP_CMPG_BGV        0       /*�Ƚ�������ѡBGV 1.27V����*/ 

//u8	CmpoResult;	//������ѡ��
#define CMP_CMPO_P12NOR   1          /*�Ƚ�������������P12*/ 
#define CMP_CMPO_P12INV   2          /*�Ƚ������ȡ�������P12*/ 
#define CMP_CMPO_NO       3          /*�Ƚ��������������ⲿ�ܽ�P12*/ 

//CMP�жϱ�־����
#define CMP_IF_CLR     CMPCR1&=(~(1<<6))

typedef struct
{	
    u8  Power;      //ENABLE=ʹ��CMP  DISABLE=��ֹCMP
    u8  Rise;       //ENABLE=�������ж�
    u8  Fall;	    //ENABLE=�½����ж�
    u8  CmpG;	    //�Ƚ�����������
    u8  Disflt;	    //ENABLE=�ص��Ƚ��������0.1us Filter   DISABLE=�Ƚ��������0.1us Filter
    u8	CmpoResult;	//������ѡ��
    u8	Lcdty5;	    //�Ƚ�������� �����غ�ά�ֵ�ƽʱ��ѡ�� ��λһ��ʱ������
} CMP_InitTypeDef;

extern u8	CMP_Inilize     (CMP_InitTypeDef *CMP);
extern u8   CMP_ReadResult  (void);

#endif
