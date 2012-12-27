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
#include <math.h>

#include "bmp_format.h"
#include "corner.h"
#include "externs.h"
#include "udglobal.h"
  

void corner(unsigned char *out_result,unsigned char *out_gy,const unsigned char *in)
{
	signed int *I2x,*I2y,*Ixy,*I2x_g,*I2y_g,*Ixy_g;
	int *rps;
	signed char *Ix;
	signed char *Iy;
	int length = bih.width*bih.height,i,j;
	int handle_w = bih.width;
	int handle_h = bih.height;
	int counts = 0,*result;

	head_cpy(out_gy);										/* copy the bmp header */
	
	if(24!=bih.bitcount)								/* copy the color table */
		memcpy(&out_gy[HEAD_SIZE],&in[HEAD_SIZE],bfh.offBits - HEAD_SIZE);

	Ix = (signed char *)malloc(length*sizeof(Ix[0]));
	Iy = (signed char *)malloc(length*sizeof(Iy[0]));
	I2x = (signed int*)malloc(length*sizeof(I2x[0]));
	I2y = (signed int*)malloc(length*sizeof(I2y[0]));
	Ixy = (signed int*)malloc(length*sizeof(Ixy[0]));
	I2x_g = (signed int*)malloc(length*sizeof(I2x_g[0]));
	I2y_g = (signed int*)malloc(length*sizeof(I2y_g[0]));
	Ixy_g = (signed int*)malloc(length*sizeof(Ixy_g[0]));
	rps = (int*)malloc(length*sizeof(rps[0]));
	result = (int*)malloc(length*sizeof(result[0]));

	memset(Ix,0,sizeof(Ix[0])*length);
	memset(Iy,0,sizeof(Iy[0])*length);
	memset(I2x,0,sizeof(I2x[0])*length);
	memset(I2y,0,sizeof(I2y[0])*length);
	memset(Ixy,0,sizeof(Ixy[0])*length);
	memset(I2x_g,0,sizeof(I2x_g[0])*length);
	memset(I2y_g,0,sizeof(I2y_g[0])*length);
	memset(Ixy_g,0,sizeof(Ixy_g[0])*length);
	memset(rps,0,sizeof(rps[0])*length);
	memset(result,0,sizeof(result[0])*length);

	i = 0;
	j = 0;
	while(i<handle_h)		/* compute Ix,Iy */
	{
		while(j<handle_w)
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
		I2x[i] = Ix[i] * Ix[i];
		I2y[i] = Iy[i] * Iy[i];
		Ixy[i] = Ix[i] * Iy[i];
		
		i++;
	}
	

	gauss_init();
	Gaussian(I2x_g,I2x);			/* Gaussian */
	Gaussian(I2y_g,I2y);
	Gaussian(Ixy_g,Ixy);

	i = 0;
	while(i<length)				/* compute the response function */
	{					/* A = I2x_g, B = I2y_g, C = Ixy_g */
		rps[i] = (int)((I2x_g[i] * I2y_g[i] - Ixy_g[i] * Ixy_g[i])/
			(I2x_g[i] + I2y_g[i]));
		
		i++;				/* M = [A,C,C,B] ,R = AB-C^2-k(A+B)^2 */
	}

	i = 0;
	j = 0;
	while(i<handle_h)
	{
		while(j<handle_w)
		{
			if(rps[ct_index(i,j)]>THRESH && LOCAL_MAX==local_max(rps,i,j))
			{
				result[ct_index(i,j)] = CORN_FLAG;		
				counts++;
				fprintf(stdout,"==total %d==(%d,%d),[%d]\n",counts,i,j,rps[ct_index(i,j)]);
				out_gy[bfh.offBits+ct_index(i,j)] = 0xFF;
			}
			j++;
		}
		j = 0;
		i++;
	}
	
	mark_point(out_result,result);
	
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

static void gauss_init()
{
	int i = 0, j = 0;
	int gauss_w = GAUSS_W>>1;
	while(i<GAUSS_W)  
	{
		while(j<GAUSS_W)
		{
			quot_gau[i][j] = exp(
				-((i-gauss_w)*(i-gauss_w)+(j-gauss_w)*(j-gauss_w))
				/(2*GAUSS_D));
			j++;
		}
		j = 0;
		i++;
	}
	return;
}

static void Gaussian(signed int *out,const signed int *in)
{
	int handle_w = bih.width;	
	int handle_h = bih.height;
	int i = 0,j = 0;

	while(i<handle_h)
	{
		while(j<handle_w)
			gauss_compute(out,in,quot_gau,i,j++);
		j = 0;
		i++;
	}
	return;
}

static void gauss_compute(int *out,const int* in,double (*guass_tp)[GAUSS_W],int m,int n)
{
	int i = 0,j = 0;
	int width = GAUSS_W>>1;

	out[ct_index(m,n)] = 0;
	
	while(i<GAUSS_W)
	{
		while(j<GAUSS_W)
		{
			if(0>m-width+i)
			{
				if(0>m-width+j)
					out[ct_index(m,n)] += 
					(int)((double)in[ct_index(0,0)]*guass_tp[i][j]);
				else
					out[ct_index(m,n)] += 
					(int)((double)in[ct_index(0,n-width+j)]*guass_tp[i][j]);

			}
			else
			{
				if(0>m-width+j)
					out[ct_index(m,n)] += 
					(int)((double)in[ct_index(m-width+i,0)]*guass_tp[i][j]);
				else
					out[ct_index(m,n)] += 
					(int)((double)in[ct_index(m-width+i,n-width+j)]*guass_tp[i][j]);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return;
}

static int local_max(int *rps,int i,int j)
{
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
			if(rps[ct_index(i,j)]<=rps[ct_index(i+n,j+m)])
				return 0;
			m++;
		}
		m = -WINDOW_W;
		n++;
	}
	return LOCAL_MAX;
}

