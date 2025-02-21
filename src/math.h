#ifndef MAZ_MATH_H
#define MAZ_MATH_H

#define PI 3.14159265f

typedef struct vec2_t {
	float x;
	float y;
} vec2_t;

typedef struct vec3_t {
	float x;
	float y;
	float z;
} vec3_t;

/* vector calculus function prototypes */

float deg(const float);		// degree from radian
float rad(const float);		// radian from degree

vec3_t vec3( const float x, const float y, const float z );	// define a vector on the fly
void vcpy(vec3_t*, const vec3_t*);							// vector copy

float dist( vec3_t p1, vec3_t p2 );		// distance between two points
float norm( vec3_t v );					// norm of a vector

vec3_t vec3_add( vec3_t v1, vec3_t v2 );		// vector addition
vec3_t vec3_sub( vec3_t v1, vec3_t v2 );		// vector vec3_sub(traction
float vec3_dot( vec3_t v1, vec3_t v2 );			// vec3_dot( product
vec3_t vec3_cross( vec3_t v1, vec3_t v2 );		// vec3_cross product
vec3_t vec3_scale( vec3_t v, float k );			// product with scalar
vec3_t vec3_normalize( vec3_t v );				// return vec3_normalized vector

float vec3_angle( vec3_t v1, vec3_t v2 );		// vec3_angle between two vectors

void v_rot(vec3_t* v, const float pitch, const float yaw, const float roll);
void v_rot_about_u(vec3_t* v, const vec3_t u, const float t);	// ccw rotate a vector on a plane about it's normal by t radians

#endif