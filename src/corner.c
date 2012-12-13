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
  

void corner(const unsigned char *in)
{
	float *I2x,*I2y,*Ixy,*I2x_g,*I2y_g,*Ixy_g;
	unsigned char *Ix;
	unsigned char *Iy;
	int length = bih.width*bih.height,i = 0,j = 0;
	int handle_w = bih.width;
	int handle_h = bih.height;

	Ix = (unsigned char *)malloc(length*sizeof(unsigned char));
	Iy = (unsigned char *)malloc(length*sizeof(unsigned char));
	I2x = (float*)malloc(length*sizeof(float));
	I2y = (float*)malloc(length*sizeof(float));
	Ixy = (float*)malloc(length*sizeof(float));
	I2x_g = (float*)malloc(length*sizeof(float));
	I2y_g = (float*)malloc(length*sizeof(float));
	Ixy_g = (float*)malloc(length*sizeof(float));

	memcpy(Ix,&in[bfh.offBits],length);
	memcpy(Iy,&in[bfh.offBits],length);
	memset(I2x,0,sizeof(float)*length);
	memset(I2y,0,sizeof(float)*length);
	memset(Ixy,0,sizeof(float)*length);
	memset(I2x_g,0,sizeof(float)*length);
	memset(I2y_g,0,sizeof(float)*length);
	memset(Ixy_g,0,sizeof(float)*length);

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
		I2x[i] = (float)Ix[i] * (float)Ix[i];
		I2y[i] = (float)Iy[i] * (float)Iy[i];
		Ixy[i] = (float)Ix[i] * (float)Iy[i];
		i++;
	}

	Gaussian(I2x_g,I2x);			/* Gaussian */
	Gaussian(I2y_g,I2y);
	Gaussian(Ixy_g,Ixy);

	i = 0;
	while(i<length)				/* compute the response function */
	{					/* A = I2x_g, B = I2y_g, C = Ixy_g */
						/* M = [A,C,C,B] ,R = AB-C^2-k(A+B)^2 */
	}
	
	free(Ix);
	free(Iy);
	free(I2x);
	free(I2y);
	free(Ixy);
	free(I2x_g);
	free(I2y_g);
	free(Ixy_g);

	return;
}

static void Gaussian(float *out,const float *in)
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

static int ct_index(int i,int j)
{
	return (int)((i+1)*bih.width + j + 1);
}
