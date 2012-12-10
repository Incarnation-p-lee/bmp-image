/*
* Author:	incarnation.p.lee
* Date:		12/2/12
* Description:	main function
* Change Log:
*/

  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "externs.h"


int main()
{
	FILE *fpi,*fpo,*fpg;
	unsigned int length;
	unsigned char *buf;
	unsigned char *out;
	unsigned char *grad;

	/*fpi = fopen("/home/pli/workspace/c-program/bmp/source/1.bmp","rb");*/
#if 1
	fpi = fopen("./source/4.bmp","rb");
	fpo = fopen("./source/4.gray.bmp","wb");
	fpg = fopen("./source/4.grad.bmp","wb");
#else
	fpi = fopen("./source/2.bmp","rb");
	fpo = fopen("./source/2.gray.bmp","wb");
	fpg = fopen("./source/2.grad.bmp","wb");
#endif

	fseek(fpi,0,SEEK_END);
	length = ftell(fpi);
	buf = (unsigned char*)malloc(length);
	out = (unsigned char*)malloc(length);
	grad = (unsigned char*)malloc(length);
	fseek(fpi,0,SEEK_SET);
	
	fread(buf,length,1,fpi);

	gray(buf,out);
	fwrite(out,length,1,fpo);

	
	memcpy(grad,out,54);	
	gradient(out,grad);
#if 0
	memset(&grad[54],0,1977-54);
#endif 
	fwrite(grad,length,1,fpg);

	fclose(fpi);
	fclose(fpo);
	fclose(fpg);
	free(buf);
	free(out);
	free(grad);
	return 0;
}

