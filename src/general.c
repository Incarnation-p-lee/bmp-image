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


void head_cpy(unsigned char *out)
{
	if(NULL==out)
		return;
	
	memcpy(out,&bfh.type,sizeof(bfh.type));
	memcpy(&out[sizeof(bfh.type)],&bfh.size,sizeof(bfh)-sizeof(bfh.type)-2);
	memcpy(&out[sizeof(bfh)-2],&bih,sizeof(bih));
	return;
}

void head_read(const unsigned char *bmp_in)
{
	unsigned int index = 0;

	bfh.type = CTV(bmp_in[1],bmp_in[0]);
	index = 2;
	memcpy(&bfh.size,&bmp_in[index],
		sizeof(struct BMP_file_head)-sizeof(unsigned int));
	index += sizeof(struct BMP_file_head)-sizeof(unsigned int);
	memcpy(&bih,&bmp_in[index],sizeof(struct BMP_info_head));
	
	return;
}

void mark_point(unsigned char *out,int *mask)
{
	int i = 0, j = 0;
	while(i<bih.height)
	{
		while(j<bih.width)
		{
			if(CORN_FLAG==mask[ct_index(i,j)])
				mark_paint(out,i,j);
			j++;
		}
		j = 0;
		i++;
	}
	return;
}

static void mark_paint(unsigned char *out,int i,int j)
{
	int n = -MARK_W; 
	while(n<=MARK_W)	/* 0d44fd rgb*/
	{
		out[HEAD_SIZE + 3*ct_index(i,j+n)] = 0xFD;		/* B */
		out[HEAD_SIZE + 3*ct_index(i,j+n) + 1] = 0xD6;	/* G */
		out[HEAD_SIZE + 3*ct_index(i,j+n) + 2] = 0x1C;	/* R */
		n++;
	}
	
	n = -MARK_W;
	while(n<=MARK_W)	
	{
		out[HEAD_SIZE + 3*ct_index(i+n,j)] = 0xFD;
		out[HEAD_SIZE + 3*ct_index(i+n,j) + 1] = 0xD6;
		out[HEAD_SIZE + 3*ct_index(i+n,j) + 2] = 0x1C;
		n++;
	}
	return;
}

unsigned int ct_index(int m,int n)
{
	return (unsigned int)(point_to_bytes(m,n) - bfh.offBits);
}

unsigned int point_to_bytes(int m,int n)
{
	int i = m, j = n;

	if(0>i)		/* if out of range set to  zero */
		i = 0;
	if(0>j)
		j = 0;
	if(bih.height<=i)
		i = bih.height - 1;
	if(bih.width<=j)
		i = bih.width - 1;

	return (unsigned int)(bfh.offBits + (bih.height - i - 1)*bih.width + j);
}
