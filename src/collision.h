#ifndef __H_COLLISION__
#define __H_COLLISION__

#include "common.h"
#include "math.h"

/* useful collision structure objects */
typedef struct t_bounding_sphere {
	t_vec3 center;
	float radius;
} t_bounding_sphere, *h_bounding_sphere;

typedef struct t_collision_box {
	t_vec3 center;
	t_vec3 dimensions;
	t_vec3 front;
	t_vec3 top;
	t_vec3 right;
} t_collision_box, *h_collision_box;

typedef struct t_collision_surface {
	t_vec3 v1, v2, v3, v4;	// always define in ccw direction w/r to normal
	t_vec3 normal;
} t_collision_surface, *h_collision_surface;

/* collision function prototypes */
bool detectCollision( t_bounding_sphere* p, const int surfc, const h_collision_surface surfv );

#endif