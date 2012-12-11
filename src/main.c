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
	unsigned char *gray_bmp;
	unsigned char *grad_bmp;

	/*fpi = fopen("/home/pli/workspace/c-program/bmp/source/1.bmp","rb");*/
#if 1
	fpi = fopen("./source/3.bmp","rb");
	fpo = fopen("./source/3.gray.bmp","wb");
	fpg = fopen("./source/3.grad.bmp","wb");
#else
	fpi = fopen("./source/2.bmp","rb");
	fpo = fopen("./source/2.gray.bmp","wb");
	fpg = fopen("./source/2.grad.bmp","wb");
#endif

	fseek(fpi,0,SEEK_END);
	length = ftell(fpi);
	buf = (unsigned char*)malloc(length);
	gray_bmp = (unsigned char*)malloc(length);
	grad_bmp = (unsigned char*)malloc(length);
	fseek(fpi,0,SEEK_SET);
	
	fread(buf,length,1,fpi);

	gray(gray_bmp,buf);					/* gray bmp */
	fwrite(gray_bmp,length,1,fpo);

	gradient(grad_bmp,gray_bmp,0);		/* gradient, edger detector */
	fwrite(grad_bmp,length,1,fpg);


	fclose(fpi);
	fclose(fpo);
	fclose(fpg);
	free(buf);
	free(gray_bmp);
	free(grad_bmp);
	return 0;
}

