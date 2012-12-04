/*
* Author:	incarnation.p.lee
* Date:		12/2/12
* Description:	
* Change Log:
*/

#ifndef GRAY_H
#define GRAY_H

#define pRED 0.114
#define pGREEN 0.587
#define pBLUE 0.299
#define BITCOUNT(n)	((unsigned int)1<<(n))

#define CTV(x,y) (unsigned short)(((unsigned short)(x)<<8)+(unsigned short)(y))
#define LSV(x) (unsigned char)((x)&0x00FF)
#define HSV(x) (unsigned char)(((x)&FF00)>>8)

signed int gray(unsigned char *,unsigned char *);
static void bmp_gl(unsigned char *,unsigned char *,unsigned int,unsigned int);

#endif


