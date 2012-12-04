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
	FILE *fpi,*fpo;
	unsigned int length;
	unsigned char *buf;
	unsigned char *out;

	/*fpi = fopen("/home/pli/workspace/c-program/bmp/source/1.bmp","rb");*/
#if 0
	fpi = fopen("./source/1.bmp","rb");
	fpo = fopen("./source/1.gray.bmp","wb");
#else
	fpi = fopen("./source/2.bmp","rb");
	fpo = fopen("./source/2.gray.bmp","wb");
#endif

	fseek(fpi,0,SEEK_END);
	length = ftell(fpi);
	buf = (unsigned char*)malloc(length);
	out = (unsigned char*)malloc(length);
	fseek(fpi,0,SEEK_SET);
	
	fread(buf,length,1,fpi);
	gray(buf,out);
	fwrite(out,length,1,fpo);

	fclose(fpi);
	fclose(fpo);
	free(buf);
	free(out);
	return 0;
}

