/*
* Author:	incarnation.p.lee
* Date:		12/13/12
* Description:	
* Change Log:
*/

#ifndef CORNER_H
#define CORNER_H

#define NORMAL 		0.0625
#define WINDOW_W	7
#define GAUSS_W		5
#define GAUSS_D		0.8
#define THRESH		7000
#define WEIGHT_MAX	0.01
#define LOCAL_MAX 	0xA5
#define CORN_FLAG	0xFF

void corner(unsigned char*,const unsigned char*);
static int ct_index(int,int);
static int local_max(int*,int,int);
/*static void index_ct(int*,int*,int);*/
static void gauss_compute(int*,const int*,double (*)[GAUSS_W],int,int);
static void Gaussian(signed int*,const signed int*);

static int gauss_m[3][3] = {
		{1,2,1},
		{2,4,2},
		{1,2,1},};

#endif
  
