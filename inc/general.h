/*
* Author:	incarnation.p.lee
* Date:		12/11/12
* Description:	general function
* Change Log:
*/

#ifndef GENERAL_H
#define GENERAL_H


#include "udglobal.h"

void head_cpy(unsigned char*);
void head_read(const unsigned char*);
void mark_point(unsigned char*,int*);
static void mark_paint(unsigned char *,int,int);
unsigned int ct_index(int,int);
unsigned int point_to_bytes(int,int);

#endif
  
