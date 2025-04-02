#ifndef __R_TEXTURE_H__
#define __R_TEXTURE_H__

#include "glad.h"
#include "stb/stb_image.h"

typedef struct {

} texture_t;

int r_load_texture(const char *filename)
{
    int width, height, nchan;
    unsigned char *data = stbi_load(filename, &width, &height, &nchan, 0);

    if (!data) {
         return 0;
    }

    GLuint texture;
    GLenum target = GL_TEXTURE_2D;
    GLenum colors, format;

    if (height == 1) {
        target = GL_TEXTURE_1D;
    }

    if (nchan == 1) {
        format = GL_RED;
    }
    else if (nchan == 3) {
        format = GL_RGB;
    }
    else if (nchan == 4) {
        format = GL_RGBA;
    }

    glGenTextures(1, &texture);
    glBindTexture(target, texture);
    glTexImage2D(target
        , 0
        , GL_RGB
        , width
        , height
        , 0
        , format
        , GL_UNSIGNED_BYTE
        , data);

    if (height > 1) {

        glGenerateMipmap(target);

        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    stbi_image_free(data);

    return texture;
}

#endif