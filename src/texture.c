#include "shared.h"
#include "texture.h"

#include "glad.h"

int r_create_texture(texture_t *texture, const bitmap_t *image)
{
    glGenTextures(1, &texture->gl_handle);

    glBindTexture(GL_TEXTURE_2D, texture->gl_handle);

    // glTexImage2D(GL_TEXTURE_2D, 
    //         0, 						    // lod
    //         image->colors, 				// number of colors
    //         image->width, 		    	// buffer width in pixels
    //         image->height, 				// buffer height in pixels
    //         0, 							// 
    //         (image->has_alpha ? GL_RGB : GL_RGBA),  // color format
    //         GL_UNSIGNED_BYTE, 	        // color encoding
    //         image->buffer);			    // pointer to the image buffer

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, 0);

    return STATUS_SUCCESS;
}

void r_delete_texture(texture_t *texture)
{
    glDeleteTextures(1, &texture);
}