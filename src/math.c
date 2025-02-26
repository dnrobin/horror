#include "math.h"

#include <math.h>
#include <stdlib.h>	// for rand()

int m_rand()
{
	return rand();
}

float m_randomf()
{
	return (float)(2*rand() - 1);
}

float m_randbtwn(float a, float b)
{
	return a + (b - a)*fabsf(m_randomf());
}

float m_deg(const float rad) {
	return 180.0 * rad / PI;
}

float m_rad(const float deg) {
	return PI * deg / 180.0;
}

float m_acos(float x)
{
	return acosf(x);
}

float m_asin(float x)
{
	return asinf(x);
}

float m_atan(float x)
{
	return atanf(x);
}

float m_atan2(float y, float x)
{
	return atan2f(y, x);
}

float m_cos(float x)
{
	return cosf(x);
}

float m_sin(float x)
{
	return sinf(x);
}

float m_tan(float x)
{
	return tanf(x);
}

float m_acosh(float x)
{
	return acoshf(x);
}

float m_asinh(float x)
{
	return asinhf(x);
}

float m_atanh(float x)
{
	return atanhf(x);
}

float m_cosh(float x)
{
	return coshf(x);
}

float m_sinh(float x)
{
	return sinhf(x);
}

float m_tanh(float x)
{
	return tanhf(x);
}

float m_exp(float x)
{
	return expf(x);
}

float m_exp2(float x)
{
	return exp2f(x);
}

float m_expm1(float x)
{
	return expm1f(x);
}

float m_log(float x)
{
	return logf(x);
}

float m_log10(float x)
{
	return log10f(x);
}

float m_log2(float x)
{
	return log2f(x);
}

float m_log1p(float x)
{
	return log1pf(x);
}

float m_logb(float x)
{
	return logbf(x);
}

float m_modf(float x, float * iptr)
{
	return modff(x, iptr);
}

float m_ldexp(float x, int d)
{
	return ldexpf(x, d);
}

float m_frexp(float x, int * nptr)
{
	return frexpf(x, nptr);
}

float m_fabs(float x)
{
	return fabsf(x);
}

float m_cbrt(float x)
{
	return cbrtf(x);
}

float m_hypot(float x, float y)
{
	return hypotf(x, y);
}

float m_pow(float x, float n)
{
	return powf(x, n);
}

float m_sqrt(float x)
{
	return sqrtf(x);
}

float m_erf(float x)
{
	return erff(x);
}

float m_erfc(float x)
{
	return erfcf(x);
}

float m_lgamma(float x)
{
	return lgammaf(x);
}

float m_tgamma(float x)
{
	return tgammaf(x);
}

float m_ceil(float x)
{
	return ceilf(x);
}

float m_floor(float x)
{
	return floorf(x);
}

float m_nearbyint(float x)
{
	return nearbyintf(x);
}

float m_rint(float x)
{
	return rintf(x);
}

float m_round(float x)
{
	return roundf(x);
}

float m_trunc(float x)
{
	return truncf(x);
}

float m_fmod(float x, float y)
{
	return fmodf(x, y);
}

float m_remainder(float x, float y)
{
	return remainderf(x, y);
}
float m_remquo(float x, float y, int *quo)
{
	return remquof(x, y, quo);
}

float m_copysign(float x, float y)
{
	return copysignf(x, y);
}

float m_fmax(float a, float b)
{
	return fmaxf(a, b);
}

float m_fmin(float a, float b)
{
	return fminf(a, b);
}

//===============================================================================

vec3_t vec3_sub(const vec3_t v1, const vec3_t v2) {
	vec3_t r;
	
	r.x = v1.x - v2.x;
	r.y = v1.y - v2.y;
	r.z = v1.z - v2.z;
	
	return r;
}

vec3_t vec3_add(const vec3_t v1, const vec3_t v2) {
	vec3_t r;
	
	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;
	r.z = v1.z + v2.z;
	
	return r;
}

float vec3_dot(const vec3_t v1, const vec3_t v2) {
	float r;
	
	r = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	
	return r;
}

vec3_t vec3_scale(const vec3_t v, float k) {
	vec3_t r;
	
	r.x = v.x * k;
	r.y = v.y * k;
	r.z = v.z * k;
	
	return r;
}

vec3_t vec3_cross(const vec3_t v1, const vec3_t v2) {
	vec3_t r;
	
	r.x = v1.y * v2.z - v1.z * v2.y;
	r.y = v1.z * v2.x - v1.x * v2.z;
	r.z = v1.x * v2.y - v1.y * v2.x;
	
	return r;
}

vec3_t vec3_normalize(const vec3_t v) {
	float l;
	vec3_t r;
	
	l = vec3_norm(v);
	
	r.x = v.x / (float)l;
	r.y = v.y / (float)l;
	r.z = v.z / (float)l;
	
	return r;
}

float vec3_dist(const vec3_t p1, const vec3_t p2) {
	float d;
	
	d = vec3_norm( vec3_sub( p1, p2 ) );
	
	return d;
}

float vec3_norm(const vec3_t v) {
	float l;
	
	l = (float)sqrt( v.x*v.x + v.y*v.y + v.z*v.z );
	
	return l;
}

float vec3_angle(const vec3_t v1, const vec3_t v2) {
	float vec3_angle;
	
	vec3_angle = acos( vec3_dot(v1, v2) / ( vec3_norm(v1) * vec3_norm(v2) ) );
	
	return vec3_angle;
}

void vec3_rotate(vec3_t* v, const float x, const float y, const float z) {
	float cx = cos(x), sx = sin(x);
	float cy = cos(y), sy = sin(y);
	float cz = cos(z), sz = sin(z);

	float RzRyRx[3][3] = {
		{ cz*cy, 	-sz*cx + cz*sy*sx,	sz*sx + cz*sy*cx },
		{ sz*cy,	cz*cx + sz*sy*sx,	-cz*sx + sz*sy*cx },
		{ -sy,		cy*sx,				cy*cx }
	};
	
	float vx = v->x * RzRyRx[0][0] + v->y * RzRyRx[0][1] + v->z * RzRyRx[0][2];
	float vy = v->x * RzRyRx[1][0] + v->y * RzRyRx[1][1] + v->z * RzRyRx[1][2];
	float vz = v->x * RzRyRx[2][0] + v->y * RzRyRx[2][1] + v->z * RzRyRx[2][2];

	v->x = vx;
	v->y = vy;
	v->z = vz;
}

void vec3_rotate_about(vec3_t* v, const vec3_t u, const float t) {	// t in radians

	float u_x = u.x, u_xx = u.x*u.x;
	float u_y = u.y, u_yy = u.y*u.y;
	float u_z = u.z, u_zz = u.z*u.z;
	float c = cos(t), cc = 1 - c;
	float s = sin(t);

	/* the rotation matrix about u
	float R[3][3] = {
		{ u_x*u_x+(1-u_x*u_x)*c, u_x*u_y*(1-c)-u_z*s, u_x*u_z*(1-c)+u_y*s },
		{ u_x*u_y*(1-c)+u_z*s, u_y*u_y+(1-u_y*u_y)*c, u_y*u_z*(1-c)-u_x*s },
		{ u_x*u_z*(1-c)-u_y*s, u_y*u_z*(1-c)+u_x*s, u_z*u_z+(1-u_z*u_z)*c }
	};*/
	
	// aply transformation to v
	v->x *= u_xx+(1-u_xx)*c + u_x*u_y*cc+u_z*s + u_x*u_z*cc-u_y*s;
	v->y *= u_x*u_y*cc-u_z*s + u_yy+(1-u_yy)*c + u_y*u_z*cc+u_x*s;
	v->z *= u_x*u_z*cc+u_y*s + u_y*u_z*cc-u_x*s + u_zz+(1-u_zz)*c;
}

void vec3_cpy(vec3_t* destination, const vec3_t* origin) {
	destination->x = origin->x;
	destination->y = origin->y;
	destination->z = origin->z;
}

int vec3_cmp(const vec3_t* v1, const vec3_t* v2) {
	if (v1->x == v2->x &&
		v1->y == v2->y &&
		v1->z == v2->z ) return 1;
	return 0;
}

vec3_t vec3(const float x, const float y, const float z) {
	vec3_t v = (vec3_t){ x, y, z };
	return v;
}