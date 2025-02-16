#include <math.h>
#include <stdlib.h>

#include "collision.h"
#include "common.h"
/*
bool _detectCollision( t_collision_box * b, const int colsc, const h_collision colsv ) {
	
	int i;
	h_collision c;
	
	for ( i = 0; i < colsc; i ++ ) {
		
		c = &colsv[i];
		
		d = sub( b->center, c->center );
		
	}
	
}
*/

bool detectCollision( t_bounding_sphere* p, const int surfc, const h_collision_surface surfv ) {
	
	bool f_collision = false;
	
	int i;
	t_vec3 d, ps, v, u, r;
	float xx, yy, zz;
	h_collision_surface s;
	
	for ( i = 0; i < surfc; i ++ ) {
		
		s = &surfv[i];
		
		// calculate the vector from p to v1
		d = sub( p->center, s->v1 );
		
		// find the perpendicular distance from p to the plane surface
		zz = dot( d, s->normal );
		zz = zz >= 0.0 ? zz : -zz; // abs() doesn't work...
		
		// ignore collision if distance is greater than bounding sphere radius
		if ( zz >= p->radius ) continue;

		// project p onto s
		ps = add( p->center, scale( s->normal, -zz ) );

		// calculate the edge going vector
		u = sub(s->v2, s->v1);

		// calculate the exterior pointing normal
		r = cross( u, s->normal );

		// calculate coplanar vector from v1 to ps
		v = sub( ps, s->v1 );

		// reject this surface if ps is "outside" the edge
		if ( dot( r, v ) > 0 ) continue;

		// -----

		// calculate the edge going vector
		u = sub(s->v3, s->v2);

		// calculate the exterior pointing normal
		r = cross( u, s->normal );

		// calculate coplanar vector from v1 to ps
		v = sub( ps, s->v2 );

		// reject this surface if ps is "outside" the edge
		if ( dot( r, v ) > 0 ) continue;

		// -----

		// calculate the edge going vector
		u = sub(s->v4, s->v3);

		// calculate the exterior pointing normal
		r = cross( u, s->normal );

		// calculate coplanar vector from v1 to ps
		v = sub( ps, s->v3 );

		// reject this surface if ps is "outside" the edge
		if ( dot( r, v ) > 0 ) continue;

		// -----

		// calculate the edge going vector
		u = sub(s->v1, s->v4);

		// calculate the exterior pointing normal
		r = cross( u, s->normal );

		// calculate coplanar vector from v1 to ps
		v = sub( ps, s->v4 );

		// reject this surface if ps is "outside" the edge
		if ( dot( r, v ) > 0 ) continue;

		//printf("\nCollision with surface %d, zz:%1.3f xx:%1.3f yy:%1.3f", i, zz, xx, yy);
		//exit(1);
		
		// there is collision with the current surface, move back point
		p->center = add( p->center, scale( s->normal, p->radius - zz ) );
		
		// flag collision state
		f_collision = true;
		
	}
	
	return f_collision;
}