/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : stc15_pwm.c
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
#include	"stc15_pwm.h"

//========================================================================
//u8	PWM_Inilize(PWM_InitTypeDef *PWM)
// ����:PWM��ʼ������
// ����:u8 PWM_N:PWM·�����(2~7) PWM: �ṹ����,��ο�pwm.h��Ķ���.
// ����: �ɹ�����0, ���󷵻�1
//========================================================================
void PWM_Inilize(u8 PWM_N,PWM_InitTypeDef *PWMx)
{
    P_SW2|=0X80;
    
    if(ENABLE==PWMx->PWM_GOTO_ADC)            //ENABLE=����������ʱ ����ADC
    {
        PWMCFG|=(1<<7);
    }
    else
    {
        PWMCFG&=(~(1<<7));
    }    
    
    if(PWM_HIGHT==PWMx->PWM_V_INIT)              //PWM_HIGHT=��ʼ�ߵ�ƽ 	PWM_LOW=��ʼ�͵�ƽ 
    {
         PWMCFG|=(1<<PWM_N);
    }
    else
    {
         PWMCFG&=(~(1<<PWM_N));
    }    
    if(ENABLE==PWMx->PWM_0ISR_EN)             //ENABLE=ʹ��PWM�����������ж�  DISABLE=�ر�PWM�����������ж� �� CBIF��Ȼ�ᱻӲ����λ
    {
        PWMCR|=(1<<6);
    }
    else
    {
        PWMCR&=(~(1<<6));
    }    
    if(ENABLE==PWMx->PWM_OUT_EN)              //ENABLE=PWMͨ��x�Ķ˿�ΪPWM��������� ��PWM���η���������
    {
         PWMCR|=(1<<PWM_N);
    }
    else
    {
         PWMCR&=(~(1<<PWM_N));
    }    
    
    if(ENABLE==PWMx->PWM_UNUSUAL_EN)          //ENABLE=ʹ��PWM���ⲿ�쳣��⹦��
    {
         PWMFDCR=(1<<5);
    }
    else
    {
         PWMFDCR&=(~(1<<5));
    }    
    
    if(ENABLE==PWMx->PWM_UNUSUAL_OUT)         //ENABLE=�����쳣ʱ��PWM��Ӧ������ڻ��� ��������ģʽ
    {
         PWMFDCR=(1<<4);
    }
    else
    {
         PWMFDCR&=(~(1<<4));
    }    
    if(ENABLE==PWMx->PWM_UNUSUAL_ISR_EN)      //ENABLE=ʹ���쳣����ж� DISABLE=�ر��쳣����ж� ��FDIF��Ȼ�ᱻӲ����λ
   {
         PWMFDCR=(1<<3);
    }
    else
    {
         PWMFDCR&=(~(1<<3));
    }    
    if(ENABLE==PWMx->PWM_UNUSUAL_CMP0_EN)     //ENABLE=�쳣���ԴΪ�Ƚ�������� ���ȽϽ��Ϊ��ʱ ����PWM�쳣
    {
         PWMFDCR=(1<<2);
    }
    else
    {
         PWMFDCR&=(~(1<<2));
    }    
    if(ENABLE==PWMx->PWM_UNUSUAL_P24_EN)      //ENABLE=�쳣���ԴΪP24/PWMFLT ��P24=1 ����PWM�쳣
    {
         PWMFDCR=(1<<1);
    }
    else
    {
         PWMFDCR&=(~(1<<1));
    }  
    
    PWMCKS=0;
    if(PWM_Clock_NT==PWMx->PWM_CLOCK)               //PWM_Clock_NT=PWM��ʱ��Դ��ϵͳʱ�Ӿ���Ƶ���ʱ��  PWM_Clock_Timer2_OF=PWM��ʱ��Դ��TMER2���������
    {
        PWMCKS&=(~(1<<4));
    }
    else
    {
       PWMCKS|=(1<<4);
    }       
    
    PWMCKS|=PWMx->PWM_CLOCK_DIV;           //��PWM_CLOCK=PWM_Clock_NTʱ PWM��ʱ��Դ��ϵͳʱ��/(PS[3:0]+1)
    switch(PWM_N)
    {
        case PWM_2:      
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
        {
             PWM2CR&=(~(1<<3));
        }
        else
        {
             PWM2CR|=(1<<3);
        }   
        
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
        {
            PWM2CR|=(1<<2);
        }  
        else
        {
             PWM2CR&=(~(1<<2));
        }           
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
        {
            PWM2CR|=(1<<1);
        }  
        else
        {
             PWM2CR&=(~(1<<1));
        }           
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
        {
            PWM2CR|=(1<<0);
        }  
        else
        {
             PWM2CR&=(~(1<<0));
        }           
        break;
        
        case PWM_3:      
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
        {
             PWM3CR&=(~(1<<3));
        }
        else
        {
             PWM3CR|=(1<<3);
        }   
        
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
        {
            PWM3CR|=(1<<2);
        }  
        else
        {
             PWM3CR&=(~(1<<2));
        }           
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
        {
            PWM3CR|=(1<<1);
        }  
        else
        {
             PWM3CR&=(~(1<<1));
        }           
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
        {
            PWM3CR|=(1<<0);
        }  
        else
        {
             PWM3CR&=(~(1<<0));
        }           
        break;
        
        case PWM_4:      
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
        {
             PWM4CR&=(~(1<<3));
        }
        else
        {
             PWM4CR|=(1<<3);
        }   
        
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
        {
            PWM4CR|=(1<<2);
        }  
        else
        {
             PWM4CR&=(~(1<<2));
        }           
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
        {
            PWM4CR|=(1<<1);
        }  
        else
        {
            PWM4CR&=(~(1<<1));
        }           
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
        {
            PWM4CR|=(1<<0);
        }  
        else
        {
            PWM4CR&=(~(1<<0));
        }           
        break;
        
        case PWM_5:      
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
        {
             PWM5CR&=(~(1<<3));
        }
        else
        {
             PWM5CR|=(1<<3);
        }   
        
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
        {
            PWM5CR|=(1<<2);
        }  
        else
        {
             PWM5CR&=(~(1<<2));
        }           
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
        {
            PWM5CR|=(1<<1);
        }  
        else
        {
             PWM5CR&=(~(1<<1));
        }           
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
        {
            PWM5CR|=(1<<0);
        }  
        else
        {
            PWM5CR&=(~(1<<0));
        }           
        break;
        
        case PWM_6:      
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
        {
             PWM6CR&=(~(1<<3));
        }
        else
        {
             PWM6CR|=(1<<3);
        }   
        
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
        {
            PWM6CR|=(1<<2);
        }  
        else
        {
             PWM6CR&=(~(1<<2));
        }           
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
        {
            PWM6CR|=(1<<1);
        }  
        else
        {
            PWM6CR&=(~(1<<1));
        }           
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
        {
            PWM6CR|=(1<<0);
        }  
        else
        {
            PWM6CR&=(~(1<<0));
        }           
        break;
        
        case PWM_7:      
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
        {
             PWM7CR&=(~(1<<3));
        }
        else
        {
             PWM7CR|=(1<<3);
        }   
        
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
        {
            PWM7CR|=(1<<2);
        }  
        else
        {
            PWM7CR&=(~(1<<2));
        }           
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
        {
            PWM7CR|=(1<<1);
        }  
        else
        {
            PWM7CR&=(~(1<<1));
        }           
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
        {
            PWM7CR|=(1<<0);
        }  
        else
        {
            PWM7CR&=(~(1<<0));
        }           
        break;
        
        default:
        break;
    }
    
    if(ENABLE==PWMx->PWM_EN)                  //ENABLE=PWMʹ�� ������PWM�������úú�������� ������رպ��ڴ򿪣���PWM���������´�0����   
    {
        PWMCR|=(1<<7);
    }  
    else
    {
        PWMCR&=(~(1<<7));
    }         
}

/////////////////////////////////////////
//����PWM����
u8 PWM_SET_PERIOD(u16 period)
{
    if(0x8000>period)
    {      
        PWMCL=(u8)(period);
        PWMCH=(u8)(period>>8);
        return 0;
    }
    else
    {
        return 1;
    }    
}

/////////////////////////////////////////
//����PWM��һ�κ͵ڶ��η�ת����
u8 PWM_SET_T12_PERIOD(u8 PWM_N,u16 period1,u16 period2)
{
    switch(PWM_N)
    {
        case PWM_2:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
        
        case PWM_3:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
         
        case PWM_4:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
          
        case PWM_5:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
           
        case PWM_6:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
            
        case PWM_7:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
             
        default:
        return 1;
        break;
    }
}




