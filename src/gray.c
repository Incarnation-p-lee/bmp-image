/*
* Author:	incarnation.p.lee
* Date:		12/2/12
* Description:	gray the bmp
* Change Log:
*/

  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "bmp_format.h"
#include "gray.h"
#include "udglobal.h"
#include "externs.h"

/*
* out-		output image
* in-		input image
*/
signed int gray(unsigned char *bmp_out,const unsigned char *bmp_in)
{
	head_read(bmp_in);
	head_cpy(bmp_out,bmp_in);

	if(24==bih.bitcount)	/* 24 bits BMP */
		bmp_gl(bmp_out,bmp_in,bfh.offBits,bih.width*bih.height);

	if(1==bih.bitcount || 4==bih.bitcount || 8==bih.bitcount)	/* other color BMP */
	{
		bmp_gl(bmp_out,
				bmp_in,
				bfh.offBits-BITCOUNT(bih.bitcount),
				BITCOUNT(bih.bitcount));
		memcpy(&bmp_out[bfh.offBits],&bmp_in[bfh.offBits],bih.width*bih.height);
	}

	return 0;
}

/*
* out-		output image
* in-		input image
* index-	where data begins, bytes
* length-	how many pixels it will handle, 
*/
static void bmp_gl(unsigned char *out,const unsigned char *in,unsigned int index,unsigned int length)
{
	int i = 0;
	unsigned char rgb_tmp;

	while(i<length)
	{
		rgb_tmp = (unsigned char)(
				pRED*in[index] +
				pGREEN*in[index+1] +
				pBLUE*in[index+2]);
		out[index] = rgb_tmp;	/* R gray */
		out[index+1] = rgb_tmp;	/* R gray */
		out[index+2] = rgb_tmp;	/* B gray */
		
		if(1==length || 4==length || 8==length)	/* other color BMP */
			index += 4;
		else
			index += 3;
		i++;	
	}
	return;
}

