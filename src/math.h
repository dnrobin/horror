#ifndef __MAZE_GAME_MATH_H__
#define __MAZE_GAME_MATH_H__

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

float m_deg(const float);		// degree from radian
float m_rad(const float);		// radian from degree

vec3_t vec3( const float x, const float y, const float z );	// define a vector on the fly
void vec3_cpy(vec3_t*, const vec3_t*);							// vector copy
int vec3_cmp(const vec3_t* v1, const vec3_t* v2);

float vec3_dist( vec3_t p1, vec3_t p2 );		// distance between two points
float vec3_norm( vec3_t v );					// norm of a vector

vec3_t vec3_add( vec3_t v1, vec3_t v2 );		// vector addition
vec3_t vec3_sub( vec3_t v1, vec3_t v2 );		// vector vec3_sub(traction
float vec3_dot( vec3_t v1, vec3_t v2 );			// vec3_dot( product
vec3_t vec3_cross( vec3_t v1, vec3_t v2 );		// vec3_cross product
vec3_t vec3_scale( vec3_t v, float k );			// product with scalar
vec3_t vec3_normalize( vec3_t v );				// return vec3_normalized vector

float vec3_angle( vec3_t v1, vec3_t v2 );		// vec3_angle between two vectors

void vec3_rotate(vec3_t* v, const float pitch, const float yaw, const float roll);
void vec3_rotate_about(vec3_t* v, const vec3_t u, const float t);	// ccw rotate a vector on a plane about it's normal by t radians

int m_rand();
float m_randomf();
float m_randbtwn(float a, float b);
float m_acos(float);
float m_asin(float);
float m_atan(float);
float m_atan2(float, float);
float m_cos(float);
float m_sin(float);
float m_tan(float);
float m_acosh(float);
float m_asinh(float);
float m_atanh(float);
float m_cosh(float);
float m_sinh(float);
float m_tanh(float);
float m_exp(float);
float m_exp2(float);
float m_expm1(float);
float m_log(float);
float m_log10(float);
float m_log2(float);
float m_log1p(float);
float m_logb(float);
float m_modf(float, float *);
float m_ldexp(float, int);
float m_frexp(float, int *);
float m_fabs(float);
float m_cbrt(float);
float m_hypot(float, float);
float m_pow(float, float);
float m_sqrt(float);
float m_erf(float);
float m_erfc(float);
float m_lgamma(float);
float m_tgamma(float);
float m_ceil(float);
float m_floor(float);
float m_nearbyint(float);
float m_rint(float);
float m_round(float);
float m_trunc(float);
float m_fmod(float, float);
float m_remainder(float, float);
float m_remquo(float, float, int *);
float m_copysign(float, float);
float m_fmax(float, float);
float m_fmin(float, float);


#endif