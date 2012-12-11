/*
* Author:	incarnation.p.lee
* Date:		12/11/12
* Description:	gray the bmp
* Change Log:
*/

  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "bmp_format.h"
#include "general.h"
#include "udglobal.h"


void head_cpy(unsigned char *out,const unsigned char *in)
{
	if(NULL==out||NULL==in)
		return;
	
	memcpy(out,in,bfh.offBits);
	return;
}

void head_read(const unsigned char *bmp_in)
{
	unsigned int index = 0;

	bfh.type = CTV(bmp_in[0],bmp_in[1]);
	index = 2;
	memcpy(&bfh.size,&bmp_in[index],
		sizeof(struct BMP_file_head)-sizeof(unsigned int));
	index += sizeof(struct BMP_file_head)-sizeof(unsigned int);
	memcpy(&bih,&bmp_in[index],sizeof(struct BMP_info_head));
	
	return;
}




