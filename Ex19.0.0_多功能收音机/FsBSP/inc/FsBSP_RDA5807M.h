/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� ��FsBSP_RDA5807M.h
 * �ļ����� ��RDA5807M������ͷ�ļ�
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾���� ��V1.0 	   					
 * �޸����� ��2015-09-16
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, �����������ӿƼ����޹�˾/�廪��ѧ������
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#ifndef __FSBSP_RDA5807M_H__
#define __FSBSP_RDA5807M_H__

#include "stc15_delay.h"
#include "stc15_iic.h"

#define RDA5807M_WrDevAddr		0x20
#define RDA5807M_RdDevAddr		0x21

extern void RDA5807M_PowerOnAndInit(void);
extern void RDA5807M_AutoSeek(bit bUpAndDown);
extern void RDA5807M_SetVolume(bit bUpAndDown);

#endif