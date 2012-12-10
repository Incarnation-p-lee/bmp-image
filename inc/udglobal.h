/*
* Author:	incarnation.p.lee
* Date:		12/9/12
* Description:	define all the global varibale and define
* Change Log:
*/

#ifndef UGLOABL_H
#define UGLOABL_H

#include "bmp_format.h"


#define BITCOUNT(n)	((unsigned int)1<<(n))

#define CTV(x,y) (unsigned short)(((unsigned short)(x)<<8)+(unsigned short)(y))
#define LSV(x) (unsigned char)((x)&0x00FF)
#define HSV(x) (unsigned char)(((x)&FF00)>>8)

struct BMP_file_head bfh;
struct BMP_info_head bih;

#endif

 
