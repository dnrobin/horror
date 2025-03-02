#ifndef __MAZE_GAME_BITMAP_H__
#define __MAZE_GAME_BITMAP_H__

typedef struct t_bitmap {
	int 				width;
	int 				height;
	int 				colors;
	int 				bitdepth;
	bool 				has_alpha;
	unsigned char* 		buffer;
} bitmap_t;

int f_load_bitmap_file(const char* filename, bitmap_t *image);
void f_free_bitmap(bitmap_t *image);

#endif