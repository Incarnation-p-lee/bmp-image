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
#include "externs.h"
  

signed int gradient(unsigned char *bmp_out,const unsigned char *bmp_in,unsigned char director)
{
	head_cpy(bmp_out);
	
	if(24!=bih.bitcount)
		memcpy(bmp_out,bmp_in,bfh.offBits - HEAD_SIZE);
	
	gdt_xy(bmp_out,bmp_in,director);

	return 0;
}

/*
* flag = 0x55,x directory
* flag = 0xaa,y directory
*/
static void gdt_xy(unsigned char *out,const unsigned char *in,unsigned char director)
{
	unsigned int handle_h = bih.height - 2;
	unsigned int handle_w = bih.width - 2;
	int i = 0,j = 0;
	
	while(i<handle_h)
	{
		while(j<handle_w)
		{
			out[point_to_bytes(i,j)] = (unsigned char)sqrt(pow(matrix(in,i,j,XD),2)+
				 pow(matrix(in,i,j,YD),2));
			j++;
		}
		i++;
		j = 0;
	}
	return;
}


static unsigned int point_to_bytes(unsigned int i,unsigned int j)
{
	return (unsigned int)(bfh.offBits + (bih.width*(i+1) + j + 1)*(bih.bitcount>>3));
}


signed int matrix(const unsigned char *in,unsigned int i,unsigned int j,unsigned char director)
{
	signed int result = 0;
	if(0x55==director)
	{
		result = Sx[0][2]*in[point_to_bytes(i-1,j+1)] + Sx[0][0]*in[point_to_bytes(i-1,j-1)]+
			Sx[1][2]*in[point_to_bytes(i,j+1)] + Sx[1][0]*in[point_to_bytes(i,j-1)]+ 
			Sx[2][2]*in[point_to_bytes(i+1,j+1)] + Sx[2][0]*in[point_to_bytes(i+1,j-1)];
	}

	if(0xAA==director)	
	{
		result = Sy[2][0]*in[point_to_bytes(i+1,j-1)] + Sy[0][0]*in[point_to_bytes(i-1,j-1)]+
			Sy[2][1]*in[point_to_bytes(i+1,j)] + Sy[0][1]*in[point_to_bytes(i-1,j)]+
			Sy[2][2]*in[point_to_bytes(i+1,j+1)] + Sy[0][2]*in[point_to_bytes(i-1,j+1)];
	}

	return result;
}
