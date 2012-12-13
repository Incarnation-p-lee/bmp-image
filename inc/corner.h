/*
* Author:	incarnation.p.lee
* Date:		12/13/12
* Description:	
* Change Log:
*/

#ifndef CORNER_H
#define CORNER_H

#define NORMAL 0.0625

void corner(const unsigned char*);
static int ct_index(int,int);
static void Gaussian(float*,const float*);

static int gauss_m[3][3] = {
		{1,2,1},
		{2,4,2},
		{1,2,1},};

#endif
  
