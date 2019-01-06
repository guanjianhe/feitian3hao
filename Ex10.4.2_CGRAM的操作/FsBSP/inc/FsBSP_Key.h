#ifndef	__FsBSP_KEY_H__
#define	__FsBSP_KEY_H__

#include "STC15.h"


#define uChar8 unsigned char
#define uInt16 unsigned int

#define KEYPORT	 P4			  	//键盘接入端口

sbit Key0 = P4^0;
 
sbit KEY1 = P4^4;

/* ***************************************************** */
// 枚举类型
/* ***************************************************** */ 
enum KeyState{StateInit,StateAffirm,StateSingle,StateRepeat};


extern unsigned char g_ucKeyNum;

extern void ExecuteKeyNum();


#endif