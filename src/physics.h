#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "math.h"

typedef struct t_physics_particle {
	t_vec3 cur_pos;
	t_vec3 last_pos;
	t_vec3 force;
	t_vec3 vel;
	t_vec3 accel;
	float mass;
} t_physics_particle, *h_physics_particle;



#endif