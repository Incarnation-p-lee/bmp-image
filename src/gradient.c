/*
* Author:	incarnation.p.lee
* Date:		12/9/12
* Description:	gradient the bmp
* Change Log:
*/

  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "bmp_format.h"
#include "gradient.h"
#include "udglobal.h"
  

signed int gradient(unsigned char *bmp_in,unsigned char *bmp_out)
{
	unsigned int begin;
	/*length = bih.width * bih.height;
		length = BITCOUNT(bih.bitcount);*/

	if(24==bih.bitcount)	/* 24 bits BMP */
		begin = sizeof(struct BMP_file_head) + sizeof(struct BMP_info_head);

	if(1==bih.bitcount || 4==bih.bitcount || 8==bih.bitcount)	/* other color BMP */
		begin = sizeof(struct BMP_file_head) + sizeof(struct BMP_info_head) + BITCOUNT(bih.bitcount);

	begin -= 2;
	gdt_xy(bmp_out,bmp_in,begin,0);

	return 0;
}

/*
* flag = 0x55,x directory
* flag = 0xaa,y directory
*/
static void gdt_xy(unsigned char *out,unsigned char *in,unsigned int begin,unsigned int flag)
{
	unsigned int handle_h = bih.height - 2;
	unsigned int handle_w = bih.width - 2;
	unsigned char tmp;
	unsigned int rst;
	int i = 0,j = 0;
	
	while(i<handle_h)
	{
		while(j<handle_w)
		{
			tmp = (unsigned char)sqrt(pow(matrix(in,begin,i,j,XD),2)+
				 pow(matrix(in,begin,i,j,YD),2));
			rst = INDEX(begin,bih.width,i,j);
			out[INDEX(begin,bih.width,i,j)] = tmp;
			out[INDEX(begin,bih.width,i,j)+1] = tmp;
			out[INDEX(begin,bih.width,i,j)+2] = tmp;
			j++;
		}
		i++;
		j = 0;
	}
	return;
}

static signed char matrix(unsigned char *in,unsigned int begin,int i,int j,unsigned int flag)
{
	signed char result = 0;
	if(0x55==flag)
	{
		result = Sx[0][2]*in[INDEX(begin,bih.width,i-1,j+1)] - Sx[0][0]*in[INDEX(begin,bih.width,i-1,j-1)]+
			2*Sx[1][2]*in[INDEX(begin,bih.width,i,j+1)] - 2*Sx[1][0]*in[INDEX(begin,bih.width,i,j-1)]+ 
			Sx[2][2]*in[INDEX(begin,bih.width,i+1,j+1)] - Sx[2][0]*in[INDEX(begin,bih.width,i+1,j-1)];
	}

	if(0xAA==flag)	
	{
		result = Sy[2][0]*in[INDEX(begin,bih.width,i-1,j-1)] - Sy[0][0]*in[INDEX(begin,bih.width,i+1,j-1)]+
			2*Sy[1][0]*in[INDEX(begin,bih.width,i-1,j-1)] - 2*Sy[0][1]*in[INDEX(begin,bih.width,i+1,j)]+
			Sy[2][0]*in[INDEX(begin,bih.width,i-1,j-1)] - Sy[2][2]*in[INDEX(begin,bih.width,i+1,j+1)];
	}

	return result;
}
