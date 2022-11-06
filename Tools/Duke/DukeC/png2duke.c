// PNG to DUKE converter by NDRAEY (c) 2022

#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "duke.h"

int main(int argc, char** argv) {
	printf("png2duke by NDRAEY (c) 2022\n\n");
	if(argc<=1) {
		printf("Not enough arguments!\n");
		exit(1);
	}

	char* file = argv[argc-1];

	FILE* fp = fopen(file, "rb");
	if(!fp) {
		printf("Error opening file %s: errno=%d\n", file, errno);
		exit(1);
	}

	char header[8];

	fread(header, 1, 8, fp);
	if(png_sig_cmp((png_const_bytep)header, 0, 8)) {
		printf("Not a PNG file!\n");
		fclose(fp);
		exit(1);
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop info_ptr = png_create_info_struct(png_ptr);

	if(setjmp(png_jmpbuf(png_ptr))) {
		printf("setjmp() failed!\n");
		fclose(fp);
		exit(1);
	}

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    int width = png_get_image_width(png_ptr, info_ptr);
    int height = png_get_image_height(png_ptr, info_ptr);
    char color_type = png_get_color_type(png_ptr, info_ptr);
    char bit_depth = png_get_bit_depth(png_ptr, info_ptr);

	png_read_update_info(png_ptr, info_ptr);

	if (setjmp(png_jmpbuf(png_ptr))) {

	}
	
	png_bytep* row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
	for(int y=0; y<height; y++) {
		row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
	}

	png_read_image(png_ptr, row_pointers);

	// START HERE!
	int modifer = 3;

	char* nyfile = malloc(strlen(file)+6);
	strcpy(nyfile, file);
	strcat(nyfile, ".duke");

	FILE* dukefile = fopen(nyfile, "wb");

	/*
	fwrite((unsigned short[]){
		width, height
	}, 2, 2, dukefile);

	fwrite((unsigned int[]){width*height*modifer}, 4, 1, dukefile);
	fwrite((unsigned char[]){0}, 1, 1, dukefile);
	*/

	fwrite((&(DukeHeader_t){
		{'D', 'U', 'K', 'E'},
		width, height, width*height*modifer, 0
	}), sizeof(DukeHeader_t), 1, dukefile);

	for(int y=0; y<height; y++) {
		png_bytep row = row_pointers[y];

		for(int x=0; x<(width*modifer); x+=modifer) {
			fwrite((unsigned char[]){row[x], row[x+1], row[x+2]}, 1, 3, dukefile);
		}
	}

	fflush(dukefile);

	// END HERE!

	for(int y=0; y<height; y++) {
		free(row_pointers[y]);
	}
	free(row_pointers);
	
	fclose(fp);
	fclose(dukefile);

	free(nyfile);

	printf("All OKAY! The file is ready!\n");
	
	return 0;
}
