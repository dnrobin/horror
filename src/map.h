#ifndef __MAP_H__
#define __MAP_H__

#include "common.h"
#include "geometry.h"

#define GL_LIST_ID_MAP 				1
#define GL_LIST_ID_WIREFRAME 		2

typedef struct t_map_descriptor {
	uint nb_faces;
	//unsigned int ofs_to_faces;
} t_map_descriptor, *h_map_descriptor;

typedef struct t__face {
	uint type;				// real face type (3 or 4)
	t_vec3 verts[4];		// extra vector if type 3
	t_vec2 tcoords[4];		// same
	t_cRGBA colors[4];
	t_vec3 normal;
	uint texid;
} t__face;

typedef struct t__face2 {
	uint type;				// real face type (3 or 4)
	t_vec3 verts[4];		// extra vector if type 3
	t_vec2 tcoords[4];		// same
	t_cRGBA colors[4];
	t_vec3 normal;
	uint tex_diffuse_id;	// RGB color (3D)
	uint tex_specular_id;	// Specular map (1D)
	uint tex_height_id;		// Height value (1D)
	uint tex_normal_id;		// Normal map (3D)
} t__face2;

#define FACE_TYPE_3 3
#define FACE_TYPE_4 4

/* prototypes */
int saveMap(const int mapc, const float* mapv, const char* filename );
int saveMap2(const int mapc, const float* mapv, const char* filename );
int loadMap(const char* filename);
int loadMap2(const char* filename);
void subdivision4(const t_face4* face, const int u, const int v, const int ndivs, int rec);

t_face4* convertFace4( const t__face* );
//t_face3 convertFace3( const t__face* );
//t__face convertFace( const t_face3* );
//t__face convertFace( const t_face4* );

#define NSUBDIVS 3

#endif