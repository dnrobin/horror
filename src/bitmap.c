#include "shared.h"
#include "bitmap.h"

#include <stdlib.h>

h_bitmap loadBitmapImageFromFile(const char* filename) {
    
	FILE* fp;
	h_bitmap image;
	unsigned size, i;				// size of image in bytes
	unsigned short int planes;		// number of planes in image (must be 1)
	unsigned short int bpp;			// number of bits per pixel (must be 24 or 32)
	unsigned int cmp;				// compression (must be 0)
	char temp;						// used to convert bgr to rgb color

	// register new bitmap to memory
	if( (image = (h_bitmap)malloc(sizeof(t_bitmap))) == NULL ) {
		printf("Error loading textures files.");
		return 0;
	}

	// try opening the file
	if( (fp = fopen(filename, "rb")) == NULL ) {
		printf("File not found: \"%s\"\n",filename);
		return 0;
	}

	// move to the width/height values
	fseek(fp, 18, SEEK_CUR);

	// read width
	if( (i = fread(&image->size_x, 4, 1, fp)) != 1 ) {
		return 0;
	}
	//printf("Image width %d\n",image->size_x);

	// read height
	if( (i = fread(&image->size_y, 4, 1, fp)) != 1 ) {
		return 0;
	}
	//printf("Image height %d\n",image->size_y);

	// calculate size (assuming 24bit)
	size = image->size_x * image->size_y * 3;

	// read the planes
	if( (fread(&planes, 2, 1, fp)) != 1 ) {
		return 0;
	}

	if( planes != 1 ) {
		printf("Wrong image file format: not right amount of planes\n");
		return 0;
	}

	// read bpp
	if( (i = fread(&bpp, 2, 1, fp)) != 1 ) {
		return 0;
	}

	if( bpp != 8 && bpp != 24 && bpp != 32 ) {
		printf("Wrong image file format: wrong bits per pixel\n");
		return 0;
	}
	//printf("bpp %d\n",bpp);

	// read compression (should be 0)
	if( (i = fread(&cmp, 4, 1, fp)) != 1 ) {
		return 0;
	}

	if( cmp != 0 ) {
		printf("Wrong image file format: wrong compression mode.\n");
		//return 0;
	}
	//printf("compression %d\n",cmp);

	// read size
	if( (i = fread(&size, 4, 1, fp)) != 1 ) {
		return 0;
	}
	//printf("Image size (bytes) %d\n",size);

	// move ahead 
	fseek(fp, 12, SEEK_CUR);

	// read data
	image->data = (unsigned char *)malloc(sizeof(unsigned char)*size);
	if( image->data == NULL ) {
		printf("Error allocation memory for texture images\n");
		return 0;
	}
	if( (i = fread(image->data, size, 1, fp)) != 1 ) {
		printf("Error reading image data from file\n");
		return 0;
	}
	
	if ( bpp == 24 ) {
		for ( i = 0; i < size; i += 3 ) {
			temp = image->data[i + 2];
			image->data[i + 2] = image->data[i + 1];
			image->data[i + 1] = temp;
		}
	}
	
	fclose(fp);

	return image;
}