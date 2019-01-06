/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : stc15_cmp.c
 * �ļ����� : STCϵ�е�Ƭ��ͷ�ļ�
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

#include	"stc15_cmp.h"

//========================================================================
// ����: u8	CMP_Inilize(CMP_InitTypeDef *CMP)
// ����: ��ʼ����ѹ�Ƚ���
// ����:CMP: �ṹ����,��ο�cmp.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1
//========================================================================
u8	CMP_Inilize(CMP_InitTypeDef *CMP)
{   
    CMP_IF_CLR;                  //CMP�жϱ�־����
    
    if(0x20 > CMP->Lcdty5)
    {
         CMPCR2 &= (~0x1F);
         CMPCR2 |= CMP->Lcdty5;    //�Ƚ�������� �����غ�ά�ֵ�ƽʱ��ѡ�� ��λһ��ʱ������
    }
    else
    {
        return 1;                           //ʧ��?
    }    
    
    CMPCR1 &= (~(1 << 3));  //�Ƚ�������ֻ��ѡP55
      
    if(CMP_CMPG_P54 == CMP->CmpG)
    {
        CMPCR1 |= 1 << 3;       //�Ƚ�������ѡP54
    }
    else if(CMP_CMPG_BGV == CMP->CmpG)
    {
        CMPCR1 &= (~(1 << 3));  //�Ƚ�������ѡBGV 1.27V����
    }
    else
    {
        return 1;           //ʧ��?
    }
    
    if(ENABLE == CMP->Rise)    //�������ж�
    {
        CMPCR1 |= 1 << 5;                   //ʹ��
    }
    else if(DISABLE == CMP->Rise)   
    {
        CMPCR1 &= (~(1<<5));              //��ֹ
    }
    else
    {
        return 1;                       //ʧ��?
    }
    
    if(ENABLE == CMP->Fall)    //�½����ж�
    {
        CMPCR1 |= 1 << 4;                   //ʹ��
    }
    else if(DISABLE == CMP->Fall)
    {
        CMPCR1 &= (~(1 << 4));              //��ֹ
    }
    else
    {
        return 1;                       //ʧ��?
    }
    
    if(ENABLE == CMP->Disflt)  //����0.1us Filter
    {
        CMPCR2 |= 1 << 6;                   //�ص��Ƚ��������0.1us Filter
    }
    else if(DISABLE==CMP->Disflt)
    {
        CMPCR2 &= (~(1 << 6));              //�Ƚ��������0.1us Filter
    }
    else
    {
        return 1;                       	//ʧ��
    }

    switch (CMP->CmpoResult)
    {           
        case CMP_CMPO_P12NOR:  //�Ƚ�������������P12
        CMPCR2 &= (~(1 << 7));
        CMPCR1 |= 1 << 1;
        break;
        
        case CMP_CMPO_P12INV:   //�Ƚ������ȡ�������P12
        CMPCR2 |= 1 << 7;
        CMPCR1 |= 1 << 1;      
        break;
          
        case CMP_CMPO_NO:       //�Ƚ��������������ⲿ�ܽ�P12
        CMPCR1 &= (~(1 << 1));
        break;
                 
        default:
        return 1;               //ʧ��?
        break;
    }
    
	if(ENABLE == CMP->Power)
    {
        CMPCR1 |= 1 << 7;           //����CMP �����Ƚ�����Դ
    }
    else if(DISABLE == CMP->Power)
    {
        CMPCR1 &= (~(1 << 7));      //��ֹCMP �رձȽ�����Դ
    }
    else
    {
        return 1; 		//ʧ��
    }
    
	return 0;			//�ɹ�
}


///////////////////////////////
//��CMP�ȽϽ��
//���رȽϽ�� 
//1=CMP+ > CMP-
//0=CMP+ < CMP-
u8 CMP_ReadResult(void)
{
    if(0x01 == (CMPCR1 & (0x01)))
    {
        return 1;
    }
    else
    { 
        return 0;
    }        
}

void CMP_ISR(void) interrupt CMP_VECTOR
{
	CMP_IF_CLR;
}

