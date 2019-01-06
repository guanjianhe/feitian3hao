#ifndef	__FsBSP_KEY_H__
#define	__FsBSP_KEY_H__

#include "STC15.h"


#define uChar8 unsigned char
#define uInt16 unsigned int

#define KEYPORT	 P4			  	//¼üÅÌ½ÓÈë¶Ë¿Ú

extern unsigned char g_ucKeyNum;
extern void ScanKey(void);



#endif