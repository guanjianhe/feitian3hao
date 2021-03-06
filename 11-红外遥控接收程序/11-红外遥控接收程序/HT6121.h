
/*---------------------------------------------------------------------*/
/* --- STC MCU International Limited ----------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了宏晶科技的资料及程序   */
/*---------------------------------------------------------------------*/



#ifndef		__HT6121_H
#define		__HT6121_H

#include	"config.h"

/*************	用户配置	**************/

#define	D_USER_CODE		0xFF00		//定义红外接收用户码


/******************************************/

extern	bit	B_IrUserCodeErr;	//用户码错误标志, 0正确,   1错误
extern	bit	B_IR_Press;			//安键动作发生,   0无按键, 1有安键
extern	u8	IR_code;			//红外键码
extern	u16	UserCode;			//用户码

void IR_RX_HT6121(void);


#endif