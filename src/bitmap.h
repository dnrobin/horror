#ifndef MAZ_BITMAP_H
#define MAZ_BITMAP_H

typedef struct t_bitmap {
	int size_x, size_y;
	unsigned char* data;
} t_bitmap, *h_bitmap;

h_bitmap loadBitmapImageFromFile(const char* filename);

#endif