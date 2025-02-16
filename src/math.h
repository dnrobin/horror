#ifndef MAZ_MATH_H
#define MAZ_MATH_H

#define PI 3.14159265f

typedef struct t_vec2 {
	float x;
	float y;
} t_vec2;

typedef struct t_vec3 {
	float x;
	float y;
	float z;
} t_vec3;

/* vector calculus function prototypes */

float deg(const float);		// degree from radian
float rad(const float);		// radian from degree

t_vec3 vec3( const float x, const float y, const float z );	// define a vector on the fly
void vcpy(t_vec3*, const t_vec3*);							// vector copy

float dist( t_vec3 p1, t_vec3 p2 );		// distance between two points
float norm( t_vec3 v );					// norm of a vector

t_vec3 add( t_vec3 v1, t_vec3 v2 );		// vector addition
t_vec3 sub( t_vec3 v1, t_vec3 v2 );		// vector subtraction
float dot( t_vec3 v1, t_vec3 v2 );			// dot product
t_vec3 cross( t_vec3 v1, t_vec3 v2 );		// cross product
t_vec3 scale( t_vec3 v, float k );			// product with scalar
t_vec3 normalize( t_vec3 v );				// return normalized vector

float angle( t_vec3 v1, t_vec3 v2 );		// angle between two vectors

void v_rot(t_vec3* v, const float pitch, const float yaw, const float roll);
void v_rot_about_u(t_vec3* v, const t_vec3 u, const float t);	// ccw rotate a vector on a plane about it's normal by t radians

#endif