/*
* Author:	incarnation.p.lee
* Date:		12/2/12
* Description:	BMP format
* Change Log:
*/

#ifndef EXTERNS_H
#define EXTERNS_H

extern signed int gray(unsigned char *,const unsigned char *);
extern signed int gradient(unsigned char *,const unsigned char *,unsigned char);
extern void head_cpy(unsigned char*);
extern void head_read(const unsigned char*);
extern signed int matrix(const unsigned char *,unsigned int,unsigned int,unsigned char);
extern void corner(unsigned char*,const unsigned char*);
extern unsigned int point_to_bytes(int,int);

#endif

