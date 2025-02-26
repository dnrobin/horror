#ifndef __MAZE_GAME_COLLISION_H__
#define __MAZE_GAME_COLLISION_H__

/* useful collision structure objects */
typedef struct t_bounding_sphere {
	vec3_t center;
	float radius;
} t_bounding_sphere, *h_bounding_sphere;

typedef struct t_collision_box {
	vec3_t center;
	vec3_t dimensions;
	vec3_t front;
	vec3_t top;
	vec3_t right;
} t_collision_box, *h_collision_box;

typedef struct t_collision_surface {
	vec3_t v1, v2, v3, v4;	// always define in ccw direction w/r to normal
	vec3_t normal;
} t_collision_surface, *h_collision_surface;

/* collision function prototypes */
bool check_collisions( t_bounding_sphere* p, const int surfc, const h_collision_surface surfv );

#endif