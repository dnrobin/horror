#ifndef __PHYSICS_H__
#define __PHYSICS_H__

typedef struct t_physics_particle {
	vec3_t cur_pos;
	vec3_t last_pos;
	vec3_t force;
	vec3_t vel;
	vec3_t accel;
	float mass;
} t_physics_particle, *h_physics_particle;

#endif