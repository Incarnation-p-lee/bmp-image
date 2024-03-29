/*
* Author:	incarnation.p.lee
* Date:		12/2/12
* Description:	BMP format
* Change Log:
*/

#ifndef BMP_FORMAT_H
#define BMP_FORMAT_H
#define BITS_1	1
#define BITS_4	4
#define BITS_8	8
#define HEAD_SIZE 54
#define CCOUNT8 256

typedef struct BMP_file_head{
	unsigned short type;
	unsigned int size;
	unsigned short resd1;
	unsigned short resd2;
	unsigned int offBits;
}Bf_head;
	
typedef struct BMP_info_head{
	unsigned int size;
	unsigned int width;
	unsigned int height;
	unsigned short planes;
	unsigned short bitcount;
	unsigned int compression;
	unsigned int imagesize;
	unsigned int xples;
	unsigned int yples;
	unsigned int cused;
	unsigned int cimportant;
}Bi_head;
		
typedef struct BMP_colors{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char reserved;
}b_color;


#endif
