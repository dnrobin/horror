#ifndef __MAZE_GAME_TEXTURE_H__
#define __MAZE_GAME_TEXTURE_H__

#include "bitmap.h"

typedef struct {
    // TODO: decouple this. Asset should contain reference to this object.
    int                 asset_id;

    uint                gl_handle;      // OpenGL handle to object
    uint                gl_type;        // OpenGL texture type to bind to

    int                 width, height;
    int                 bitsperpixel;   // 16, 24 or 32
    int                 channels;       // 1, 2, 3 or 4
    int                 hasalpha;
} texture_t;

int r_create_texture(texture_t *texture, const bitmap_t *image);
void r_delete_texture(texture_t *texture);

#endif