#include "shared.h"
#include "texture.h"

#include "glad.h"

int r_create_texture_buf(texture_t *texture, int w, int h, int n, const unsigned char *buf)
{
    glGenTextures(1, &texture->gl_handle);

    glBindTexture(GL_TEXTURE_2D, texture->gl_handle);

    glTexImage2D(GL_TEXTURE_2D, 
            0, 		        // lod
            n, 				// number of colors
            w, 		    	// buffer width in pixels
            h, 				// buffer height in pixels
            0, 				// border stuff ignored
            (n > 3 ? GL_RGB : GL_RGBA), // color format
            GL_UNSIGNED_BYTE, 	        // color encoding
            buf);			// pointer to the image buffer

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