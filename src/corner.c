/*
* Author:	incarnation.p.lee
* Date:		12/13/12
* Description:	corner detect
* Change Log:
*/

  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "bmp_format.h"
#include "corner.h"
#include "externs.h"
#include "udglobal.h"
  

void corner(unsigned char *out,const unsigned char *in)
{
	signed int *I2x,*I2y,*Ixy,*I2x_g,*I2y_g,*Ixy_g;
	float *rps;
	unsigned char *Ix;
	unsigned char *Iy;
	int length = bih.width*bih.height,i = 0,j = 0;
	int handle_w = bih.width;
	int handle_h = bih.height;
	int *result,counts = 0;;

	Ix = (unsigned char *)malloc(length*sizeof(unsigned char));
	Iy = (unsigned char *)malloc(length*sizeof(unsigned char));
	I2x = (signed int*)malloc(length*sizeof(signed int));
	I2y = (signed int*)malloc(length*sizeof(signed int));
	Ixy = (signed int*)malloc(length*sizeof(signed int));
	I2x_g = (signed int*)malloc(length*sizeof(signed int));
	I2y_g = (signed int*)malloc(length*sizeof(signed int));
	Ixy_g = (signed int*)malloc(length*sizeof(signed int));
	rps = (float*)malloc(length*sizeof(float));
	result = (int*)malloc(length*sizeof(int));

	memcpy(Ix,&in[bfh.offBits],length);
	memcpy(Iy,&in[bfh.offBits],length);
	memset(I2x,0,sizeof(signed int)*length);
	memset(I2y,0,sizeof(signed int)*length);
	memset(Ixy,0,sizeof(signed int)*length);
	memset(I2x_g,0,sizeof(signed int)*length);
	memset(I2y_g,0,sizeof(signed int)*length);
	memset(Ixy_g,0,sizeof(signed int)*length);
	memset(rps,0,sizeof(float)*length);
	memset(result,0,sizeof(int)*length);

	while(i<handle_h-2)		/* compute Ix,Iy */
	{
		while(j<handle_w-2)
		{
			Ix[ct_index(i,j)] = matrix(in,i,j,XD);
			Iy[ct_index(i,j)] = matrix(in,i,j,YD);
			j++;
		}
		j = 0;
		i++;
	}

	i = 0;
	while(i<length)			/* compute I2x,I2y,Ixy */
	{
		I2x[i] = (signed int)Ix[i] * (signed int)Ix[i];
		I2y[i] = (signed int)Iy[i] * (signed int)Iy[i];
		Ixy[i] = (signed int)Ix[i] * (signed int)Iy[i];
		i++;
	}

	Gaussian(I2x_g,I2x);			/* Gaussian */
	Gaussian(I2y_g,I2y);
	Gaussian(Ixy_g,Ixy);

	i = 0;
	while(i<length)				/* compute the response function */
	{					/* A = I2x_g, B = I2y_g, C = Ixy_g */
		rps[i] = (float)(I2x_g[i] * I2y_g[i] - Ixy_g[i] * Ixy_g[i])/
			(I2x_g[i] + I2y_g[i] + 0.000001);
		
		i++;				/* M = [A,C,C,B] ,R = AB-C^2-k(A+B)^2 */
	}

#if 0
	i = 0;
	while(i<length)				/* get the max rps value */
	{
		if(rps[i]>rp_max)	
			rp_max = rps[i];
		i++;
	}
#endif

	i = 0;
	j = 0;
	while(i<handle_h-2)
	{
		while(j<handle_w-2)
		{
			if(rps[ct_index(i,j)]>THRESH && LOCAL_MAX==local_max(rps,i,j))
			{
				result[ct_index(i,j)] = CORN_FLAG;		
				counts++;
				fprintf(stdout,"==total %d==(%d,%d)\n",counts,i,j);
				out[ct_index(i,j)] = 0xFF;
			}
			j++;
		}
		j = 0;
		i++;
	}
	
	free(Ix);
	free(Iy);
	free(I2x);
	free(I2y);
	free(Ixy);
	free(I2x_g);
	free(I2y_g);
	free(Ixy_g);
	free(rps);
	free(result);

	return;
}

static void Gaussian(signed int *out,const signed int *in)
{
	int handle_w = bih.width - 2;	
	int handle_h = bih.height - 2;
	int i = 0,j = 0;

	while(i<handle_h)
	{
		while(j<handle_w)
		{
			out[ct_index(i,j)] = NORMAL*(in[ct_index(i-1,j-1)]*gauss_m[0][0] + 
						in[ct_index(i-1,j)]*gauss_m[0][1] +
						in[ct_index(i-1,j+1)]*gauss_m[0][2] +
						in[ct_index(i,j-1)]*gauss_m[1][0] +
						in[ct_index(i,j)]*gauss_m[1][1] +
						in[ct_index(i,j+1)]*gauss_m[1][2] +
						in[ct_index(i+1,j-1)]*gauss_m[2][0] +
						in[ct_index(i+1,j)]*gauss_m[2][1] +
						in[ct_index(i+1,j+1)]*gauss_m[2][2]);
			j++;
		}
		
		j = 0;
		i++;
	}
	return;
}

static int local_max(float *rps,int i,int j)
{
#if 1
	int depth = WINDOW_W;
	signed int n = -WINDOW_W,m = -WINDOW_W;
	while(n<=depth)
	{
		while(m<=depth)
		{
			if(0==m && 0 ==n)
			{		
				m++;
				continue;
			}
			if(rps[ct_index(i,j)]-rps[ct_index(i+n,j+m)]<=0.000001)
				return 0;
			m++;
		}
		m = -WINDOW_W;
		n++;
	}
	return LOCAL_MAX;
#else
	if(	rps[ct_index(i,j)] + 0.00001 > rps[ct_index(i-2,j-2)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i-2,j-1)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i-2,j)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i-2,j+1)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i-2,j+2)] &&

		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i-1,j-2)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i-1,j-1)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i-1,j)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i-1,j+1)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i-1,j+2)] &&

		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i,j-2)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i,j-1)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i,j+1)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i,j+2)] &&

		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i+1,j-2)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i+1,j-1)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i+1,j)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i+1,j+1)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i+1,j+2)] &&

		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i+2,j-2)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i+2,j-1)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i+2,j)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i+2,j+1)] &&
		rps[ct_index(i,j)] + 0.00001> rps[ct_index(i+2,j+2)])

		return LOCAL_MAX;
	return 0;
#endif
}

static int ct_index(int i,int j)
{
	return (int)((i+1)*bih.width + j + 1);
}

static void index_ct(int *i,int *j,int index)
{
	*i = (int)((index - 1)/bih.width) - 1;
	*j = (index - 1)%bih.width;
	return;
}
