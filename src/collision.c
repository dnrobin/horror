#include "shared.h"
#include "collision.h"



/*
bool _detectCollision( t_collision_box * b, const int colsc, const h_collision colsv ) {
	
	int i;
	h_collision c;
	
	for ( i = 0; i < colsc; i ++ ) {
		
		c = &colsv[i];
		
		vec3_sub(d,  b->center, c->center );
		
	}
	
}
*/

bool check_collisions( t_bounding_sphere* p, const int surfc, const h_collision_surface surfv ) {
	
	bool f_collision = false;
	
	int i;
	vec3_t d, ps, v, u, r;
	float xx, yy, zz;
	h_collision_surface s;
	
	for ( i = 0; i < surfc; i ++ ) {
		
		s = &surfv[i];
		
		// calculate the vector from p to v1
		vec3_sub(d,  p->center, s->v1 );
		
		// find the perpendicular distance from p to the plane surface
		zz = vec3_dot( d, s->normal );
		zz = zz >= 0.0 ? zz : -zz; // abs() doesn't work...
		
		// ignore collision if distance is greater than bounding sphere radius
		if ( zz >= p->radius ) continue;

		// project p onto s
		vec3_t n;
		vec3_scale(n, s->normal, -zz );
		vec3_add(ps, p->center,  n);

		// calculate the edge going vector
		vec3_sub(u, s->v2, s->v1);

		// calculate the exterior pointing normal
		vec3_cross(r, u, s->normal );

		// calculate coplanar vector from v1 to ps
		vec3_sub(v,  ps, s->v1 );

		// reject this surface if ps is "outside" the edge
		if ( vec3_dot( r, v ) > 0 ) continue;

		// -----

		// calculate the edge going vector
		vec3_sub(u, s->v3, s->v2);

		// calculate the exterior pointing normal
		vec3_cross(r, u, s->normal );

		// calculate coplanar vector from v1 to ps
		vec3_sub(v,  ps, s->v2 );

		// reject this surface if ps is "outside" the edge
		if ( vec3_dot( r, v ) > 0 ) continue;

		// -----

		// calculate the edge going vector
		vec3_sub(u, s->v4, s->v3);

		// calculate the exterior pointing normal
		vec3_cross(r, u, s->normal );

		// calculate coplanar vector from v1 to ps
		vec3_sub(v,  ps, s->v3 );

		// reject this surface if ps is "outside" the edge
		if ( vec3_dot( r, v ) > 0 ) continue;

		// -----

		// calculate the edge going vector
		vec3_sub(u, s->v1, s->v4);

		// calculate the exterior pointing normal
		vec3_cross(r, u, s->normal );

		// calculate coplanar vector from v1 to ps
		vec3_sub(v,  ps, s->v4 );

		// reject this surface if ps is "outside" the edge
		if ( vec3_dot( r, v ) > 0 ) continue;

		//printf("\nCollision with surface %d, zz:%1.3f xx:%1.3f yy:%1.3f", i, zz, xx, yy);
		//exit(1);
		
		// there is collision with the current surface, move back point
		vec3_scale(n, s->normal, p->radius - zz );
		vec3_add(p->center, p->center, n );
		
		// flag collision state
		f_collision = true;
		
	}
	
	return f_collision;
}