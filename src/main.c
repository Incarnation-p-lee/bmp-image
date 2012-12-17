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
#include "udglobal.h"


int main()
{
	FILE *fpi,*fpo,*fpg,*fpc;
	unsigned int length;
	unsigned char *buf;
	unsigned char *gray_bmp;
	unsigned char *grad_bmp;
	unsigned char *corn_bmp;

	/*fpi = fopen("/home/pli/workspace/c-program/bmp/source/1.bmp","rb");*/
#if 0
	fpi = fopen("./source/1.bmp","rb");
	fpo = fopen("./source/1.gray.bmp","wb");
	fpg = fopen("./source/1.grad.bmp","wb");
#else
	fpi = fopen("./source/2.bmp","rb");
	fpo = fopen("./source/2.gray.bmp","wb");
	fpg = fopen("./source/2.grad.bmp","wb");
	fpc = fopen("./source/2.corn.bmp","wb");
#endif

	fseek(fpi,0,SEEK_END);
	length = ftell(fpi);
	buf = (unsigned char*)malloc(length);
	gray_bmp = (unsigned char*)malloc(length);
	grad_bmp = (unsigned char*)malloc(length);
	corn_bmp = (unsigned char*)malloc(length);
	fseek(fpi,0,SEEK_SET);
	
	fread(buf,length,1,fpi);

	gray(gray_bmp,buf);					/* gray bmp */
	fwrite(gray_bmp,bfh.size,1,fpo);

	gradient(grad_bmp,gray_bmp,0);		/* gradient, edger detector */
	fwrite(grad_bmp,bfh.size,1,fpg);

	memcpy(corn_bmp,gray_bmp,bfh.size);
	memset(&corn_bmp[bfh.offBits],0x0,bih.width*bih.height);
	corner(corn_bmp,gray_bmp);
	fwrite(corn_bmp,bfh.size,1,fpc);


	fclose(fpi);
	fclose(fpo);
	fclose(fpg);
	fclose(fpc);
	free(buf);
	free(gray_bmp);
	free(grad_bmp);
	free(corn_bmp);
	return 0;
}

