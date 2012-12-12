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

signed int gray(unsigned char *,const unsigned char *);
static void bmp_gl(unsigned char *,const unsigned char *,unsigned int,unsigned int);
static void bmp_ct(unsigned char *,const unsigned char *,unsigned int,unsigned int);

#endif


