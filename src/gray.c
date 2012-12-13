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
	unsigned char *colors;
	int i = 0;
	head_read(bmp_in);

	if(BITS_1==bih.bitcount || BITS_4==bih.bitcount || BITS_8==bih.bitcount)	/* other color BMP */
	{
		bmp_gl(	bmp_out,
			bmp_in,
			bfh.offBits-BITCOUNT(bih.bitcount),
			BITCOUNT(bih.bitcount));
		memcpy(	&bmp_out[bfh.offBits],
			&bmp_in[bfh.offBits],
			bih.width*bih.height*(bih.bitcount>>3));
	}

	if(24==bih.bitcount)	/* 24 bits BMP, first convert to 8bits BMP */
	{
		colors = malloc(sizeof(struct BMP_colors)*CCOUNT8);
		bfh.offBits += sizeof(struct BMP_colors)*CCOUNT8;

		while(i<CCOUNT8)	/* build gray color table */ 
		{
			colors[sizeof(struct BMP_colors)*i] = i;	
			colors[sizeof(struct BMP_colors)*i+1] = i;	
			colors[sizeof(struct BMP_colors)*i+2] = i;	
			colors[sizeof(struct BMP_colors)*i+3] = 0;	
			i++;
		}

		memcpy(&bmp_out[HEAD_SIZE],colors,sizeof(struct BMP_colors)*CCOUNT8);

		bfh.size = bfh.offBits + bih.width*bih.height;
		bih.bitcount = BITS_8;

		bmp_ct(bmp_out,bmp_in,bfh.offBits,bih.width*bih.height);
		free(colors);
	}


	head_cpy(bmp_out);

	return 0;
}

/*
* convert 24bits BMP to 8 bits gray BMP
*/
static void bmp_ct(unsigned char *out,const unsigned char *in,unsigned int index,unsigned int length)
{
	int i = 0;
	unsigned int b_in = HEAD_SIZE;

	while(i++<length)
	{
		out[index++] = (unsigned char)(
				pRED*in[b_in] +
				pGREEN*in[b_in+1] +
				pBLUE*in[b_in+2]);
		b_in += 3;
	}
	return;
}

/*
* gray change the color table
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
		
		index += sizeof(struct BMP_colors);
		i++;	
	}
	return;
}

