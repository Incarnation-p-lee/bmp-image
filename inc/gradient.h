/*
* Author:	incarnation.p.lee
* Date:		12/9/12
* Description:	gradient
* Change Log:
*/

#ifndef GRADINET_H
#define GRADINET_H
#include "udglobal.h"

#define XD 0x55
#define YD 0xAA


signed int gradient(unsigned char *,unsigned char *);
static void gdt_xy(unsigned char*,unsigned char*,unsigned int,unsigned int);
static signed char matrix(unsigned char *,unsigned int,int,int,unsigned int);
static int Sx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1},};
static int Sy[3][3] = {{-1,-2,1},{0,0,0},{1,2,1},};

#define INDEX(s,w,i,j) (unsigned int)((s)+((w)*((i)+1)+(j)+1)*3)

#endif
  
