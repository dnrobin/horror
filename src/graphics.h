#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "common.h"
#include "res.h"

typedef struct texture_resource_descriptor {
	uint id;
	uint gl_id;
	uint width;					// image width in pixels
	uint height;				// image height in pixels
	uint gl_colors;				// number of coulours (1-4)
	uint gl_color_ordering;		// ex. GL_RGBA
	uint gl_color_encoding;		// ex. GL_UNSIGNED_BYTE
	uint gl_filtering;			// ex. GL_LINEAR
} t_texture_resource_descriptor, *h_texture_resource_descriptor;

void checkGLError();
void initGL();
int loadTextures(const int texc, const t_texture_resource_descriptor* texv);

#endif