#include "shared.h"
#include "bitmap.h"

#include <stdlib.h>

int f_load_bitmap_file(const char* filename, bitmap_t *image)
{
	FILE* fp;

	unsigned size, i;				// size of image in bytes
	unsigned short int planes;		// number of planes in image (must be 1)
	unsigned short int bpp;			// number of bits per pixel (must be 24 or 32)
	unsigned int cmp;				// compression (must be 0)
	char temp;						// used to convert bgr to rgb color

	if( (fp = fopen(filename, "rb")) == NULL ) {
		ERROR_RET("File not found '%s'.", filename);
		return 0;
	}

	if( (image = (bitmap_t*)malloc(sizeof(bitmap_t))) == NULL ) {
		ERROR_RET("Error allocating memory for texture file '%s'.", filename);
	}

	// move to the width/height values
	fseek(fp, 18, SEEK_CUR);

	if( (i = fread(&image->width, 4, 1, fp)) != 1 ) {
		ERROR_RET("Error reading texture file '%s'.", filename);
	}

	if( (i = fread(&image->height, 4, 1, fp)) != 1 ) {
		ERROR_RET("Error reading texture file '%s'.", filename);
	}

	// calculate size (assuming 24bit)
	size = image->width * image->height * 3;

	// read the planes
	if( (fread(&planes, 2, 1, fp)) != 1 ) {
		return 0;
	}

	if( planes != 1 ) {
		ERROR_RET("Wrong image file format: not right amount of planes in '%s'.", filename);
	}

	// read bpp
	if( (i = fread(&bpp, 2, 1, fp)) != 1 ) {
		return 0;
	}

	if( bpp != 8 && bpp != 24 && bpp != 32 ) {
		ERROR_RET("Wrong image file format: wrong bits per pixel in '%s'.", filename);
	}

	// read compression (should be 0)
	if( (i = fread(&cmp, 4, 1, fp)) != 1 ) {
		return 0;
	}

	if( cmp != 0 ) {
		ERROR_RET("Wrong image file format: wrong compression mode in '%s'.", filename);
	}

	// read size
	if( (i = fread(&size, 4, 1, fp)) != 1 ) {
		return 0;
	}

	fseek(fp, 12, SEEK_CUR);

	// read data
	image->buffer = (unsigned char *)malloc(sizeof(unsigned char)*size);
	if( image->buffer == NULL ) {
		printf("Error allocation memory for texture images\n");
		return 0;
	}
	if( (i = fread(image->buffer, size, 1, fp)) != 1 ) {
		printf("Error reading image buffer from file\n");
		return 0;
	}
	
	if ( bpp == 24 ) {
		// swap bgr to rgb
		for ( i = 0; i < size; i += 3 ) {
			temp = image->buffer[i + 2];
			image->buffer[i + 2] = image->buffer[i + 1];
			image->buffer[i + 1] = temp;
		}
		image->has_alpha = false;
	}
	else {
		image->has_alpha = true;
	}

	image->bitdepth = bpp;
	image->colors = bpp/8;

	fclose(fp);

	return STATUS_SUCCESS;
}