/*
* Author:	incarnation.p.lee
* Date:		12/9/12
* Description:	gradient
* Change Log:
*/

#ifndef GRADINET_H
#define GRADINET_H
#include "udglobal.h"


signed int gradient(unsigned char *,const unsigned char *,unsigned char);
static void gdt_xy(unsigned char*,const unsigned char*,unsigned char);
signed int matrix(const unsigned char *,unsigned int,unsigned int,unsigned char);
unsigned int point_to_bytes(int,int);

#if 1
static int Sx[3][3] = {{-1,0,2},{-1,0,3},{-1,0,2},};
#else
static int Sx[3][3] = {{-1,0,1},{-1,0,1},{-1,0,1},};
#endif
static int Sy[3][3] = {{-1,-1,1},{0,0,0},{1,1,1},};



#endif

