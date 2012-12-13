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
static unsigned int point_to_bytes(unsigned int,unsigned int);

static int Sx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1},};
static int Sy[3][3] = {{-1,-2,1},{0,0,0},{1,2,1},};



#endif

