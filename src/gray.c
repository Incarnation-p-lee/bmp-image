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

signed int gray(unsigned char *bmp_in,unsigned char *bmp_out)
{
	struct BMP_file_head bfh;
	struct BMP_info_head bih;
	unsigned int md_len = 0;
	unsigned int index = 0;

	bfh.type = CTV(bmp_in[0],bmp_in[1]);
	index = 2;
	memcpy(&bfh.size,&bmp_in[index],
		sizeof(struct BMP_file_head)-sizeof(unsigned int));
	index += sizeof(struct BMP_file_head)-sizeof(unsigned int);
	memcpy(&bih,&bmp_in[index],sizeof(struct BMP_info_head));
	index += sizeof(struct BMP_info_head);

	memcpy(bmp_out,bmp_in,index);
	md_len = bih.width * bih.height;

	if(24==bih.bitcount)	/* 24 bits BMP */
		bmp_gl(bmp_out,bmp_in,index,md_len);

	if(1==bih.bitcount || 4==bih.bitcount || 8==bih.bitcount)	/* other color BMP */
	{
		bmp_gl(bmp_out,bmp_in,index,BITCOUNT(bih.bitcount));
		index += (unsigned int)BITCOUNT(bih.bitcount);
		memcpy(&bmp_out[index],&bmp_in[index],md_len);
	}

	return 0;
}

static void bmp_gl(unsigned char *out,unsigned char *in,unsigned int index,unsigned int length)
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

