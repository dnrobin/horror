#include <math.h>
#include "math.h"

float deg(const float rad) {
	return 180.0 * rad / PI;
}

float rad(const float deg) {
	return PI * deg / 180.0;
}

float dist(const t_vec3 p1, const t_vec3 p2) {
	float d;
	
	d = norm( sub( p1, p2 ) );
	
	return d;
}

t_vec3 sub(const t_vec3 v1, const t_vec3 v2) {
	t_vec3 r;
	
	r.x = v1.x - v2.x;
	r.y = v1.y - v2.y;
	r.z = v1.z - v2.z;
	
	return r;
}

t_vec3 add(const t_vec3 v1, const t_vec3 v2) {
	t_vec3 r;
	
	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;
	r.z = v1.z + v2.z;
	
	return r;
}

float dot(const t_vec3 v1, const t_vec3 v2) {
	float r;
	
	r = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	
	return r;
}

t_vec3 scale(const t_vec3 v, float k) {
	t_vec3 r;
	
	r.x = v.x * k;
	r.y = v.y * k;
	r.z = v.z * k;
	
	return r;
}

t_vec3 cross(const t_vec3 v1, const t_vec3 v2) {
	t_vec3 r;
	
	r.x = v1.y * v2.z - v1.z * v2.y;
	r.y = v1.z * v2.x - v1.x * v2.z;
	r.z = v1.x * v2.y - v1.y * v2.x;
	
	return r;
}

t_vec3 normalize(const t_vec3 v) {
	float l;
	t_vec3 r;
	
	l = norm(v);
	
	r.x = v.x / (float)l;
	r.y = v.y / (float)l;
	r.z = v.z / (float)l;
	
	return r;
}

float norm(const t_vec3 v) {
	float l;
	
	l = (float)sqrt( v.x*v.x + v.y*v.y + v.z*v.z );
	
	return l;
}

float angle(const t_vec3 v1, const t_vec3 v2) {
	float angle;
	
	angle = acos( dot(v1, v2) / ( norm(v1) * norm(v2) ) );
	
	return angle;
}

void v_rot(t_vec3* v, const float x, const float y, const float z) {
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

void v_rot_about_u(t_vec3* v, const t_vec3 u, const float t) {	// t in radians

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

void vcpy(t_vec3* destination, const t_vec3* origin) {
	destination->x = origin->x;
	destination->y = origin->y;
	destination->z = origin->z;
}

int vcmpr(t_vec3* v1, t_vec3* v2) {
	if (v1->x == v2->x &&
		v1->y == v2->y &&
		v1->z == v2->z ) return 1;
	return 0;
}

t_vec3 vec3(const float x, const float y, const float z) {
	t_vec3 v = (t_vec3){ x, y, z };
	return v;
}