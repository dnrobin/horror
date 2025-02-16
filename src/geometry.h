#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "common.h"
#include "math.h"

// REMOVE ASAP
#include "map.h"

typedef struct RGBA {
	float r;
	float g;
	float b;
	float a;
} t_cRGBA, t_RGBA;

typedef struct t_face3 {
	t_vec3 vertices[3];
	t_vec2 texcoords[3];
	t_cRGBA colors[3];
	t_vec3 normal;
	uint texid;
} t_face3;

typedef struct t_face4 {
	t_vec3 vertices[4];
	t_vec2 texcoords[4];
	t_cRGBA colors[4];
	t_vec3 normal;
	uint texid;
} t_face4;


/* structure to hold a single vertex description */
typedef struct vertex {
	t_vec3 v;						// vertex coordinates
	t_RGBA color;					// rgba color values
	t_vec2 tcoord;					// texture coordinates
	struct face* parent;			// pointer to parent face
} t_vertex, *h_vertex;

/* structure to hold a single face description */
typedef struct face {
	unsigned char options;				// face option bits
	unsigned char group;				// group id used for AI and game progress (max 256 values)
	unsigned char texture_id;			// resource id of texture (max 256 values)
	t_vec3 normal;						// normal vector
	t_vertex** vertices;				// contigeous array of pointers to vertices
	unsigned short nb_vertices;			// number of vertices in array
} t_face, *h_face;

/* FACE OPTIONS BITS DESCRIPTIONS: */
#define SURFACE_IS_COLLISION		0x01	// bit 1
#define SURFACE_IS_FLOOR			0x02	// bit 2
//#define SURFACE_			0x04	// bit 3
//#define SURFACE_			0x08	// bit 4
//#define SURFACE_			0x10	// bit 5
//#define SURFACE_			0x20	// bit 6
//#define SURFACE_			0x40	// bit 7
//#define SURFACE_			0x80	// bit 8

/* structure to hold references to faces and vertices in a model */
typedef struct geometry {
	struct face_list* faces;
	unsigned int nb_faces;
	struct vertex_list* vertices;
	unsigned int nb_vertices;
} t_geometry, *h_geometry;

#endif