#ifndef __MAZE_GAME_TEXTURE_H__
#define __MAZE_GAME_TEXTURE_H__

typedef struct {

    uint                gl_handle;      // OpenGL handle to object
    uint                gl_type;        // OpenGL texture type to bind to

    int                 width, height;
    int                 bitsperpixel;   // 16, 24 or 32
    int                 channels;       // 1, 2, 3 or 4
    int                 hasalpha;
} texture_t;

int r_create_texture_buf(texture_t *texture, int w, int h, int n, const unsigned char *buf);
void r_delete_texture(texture_t *texture);

#endif