#include "shared.h"
#include "camera.h"

/**
 * The camera can be used as a fly cam or an FPS cam. This
 * means that in fly cam mode, movement and rotations are 
 * in full 3-space. In FPS mode, movement is limited to the
 * plane in which the camera is travelling.
 **/


static void recalculate_basis_fps(camera_t *c)
{
	if (c->angles[0] > +M_PI_2) c->angles[0] = +M_PI_2;
	if (c->angles[0] < -M_PI_2) c->angles[0] = -M_PI_2;

	c->angles[2] = M_CLAMP(c->angles[2], -M_PI_4, M_PI_4);

	printf("TROUBLESHOOT CAMERA\n");
	printf("pitch:\t%f\n", c->angles[0]);
	printf("yaw:\t%f\n", c->angles[1]);
	printf("roll:\t%f\n", c->angles[2]);

	// TODO: Update this code to work with new mat4_transform_**
	
	vec3(c->right
		, m_cos(c->angles[1])
		, 0	// always confined to the plane for FPS
		,-m_sin(c->angles[1])
	);

	vec3(c->up
		, m_sin(c->angles[0])*m_sin(c->angles[1])
		, m_cos(c->angles[0])
		, m_sin(c->angles[0])*m_cos(c->angles[1])
	);

	// oriented along true r/h +z direction
	vec3(c->look
		, m_cos(c->angles[0])*m_sin(c->angles[1])
		,-m_sin(c->angles[0])
		, m_cos(c->angles[0])*m_cos(c->angles[1])
	);

	// printf("%f\n",vec3_dot(c->right, c->up));
	// printf("%f\n",vec3_dot(c->up, c->look));
	// printf("%f\n\n",vec3_dot(c->look, c->right));

	printf("right:\t"); vec3_print(c->right);
	printf("up:\t"); vec3_print(c->up);
	printf("look:\t"); vec3_print(c->look);
	printf("======================\n");
}
void cam_reset_orientation(camera_t *c)
{
	vec3(c->angles, 0, 0, 0);
	recalculate_basis_fps(c);
}
void cam_move_to(camera_t *c, const vec3_t p)
{
	vec3_copy(c->eye, p);
}
void cam_move_by(camera_t *c, const vec3_t v)
{
	vec3_add(c->eye, c->eye, v);
}
void cam_move_forward(camera_t *c, float d)
{
	vec3_t v;
	vec3_scale(v, c->look, -d);
	cam_move_by(c, v);
}
void cam_move_backward(camera_t *c, float d)
{
	vec3_t v;
	vec3_scale(v, c->look, +d);
	cam_move_by(c, v);
}
void cam_move_left(camera_t *c, float d)
{
	vec3_t v;
	vec3_scale(v, c->right, -d);
	cam_move_by(c, v);
}
void cam_move_right(camera_t *c, float d)
{
	vec3_t v;
	vec3_scale(v, c->right, +d);
	cam_move_by(c, v);
}
void cam_move_up(camera_t *c, float d)
{
	vec3_t v;
	vec3_scale(v, c->up, +d);
	cam_move_by(c, v);
}
void cam_move_down(camera_t *c, float d)
{
	vec3_t v;
	vec3_scale(v, c->up, -d);
	cam_move_by(c, v);
}
void cam_set_angles(camera_t *c, m_float pitch, m_float yaw, m_float roll)
{
	vec3(c->angles, pitch, yaw, roll);
	recalculate_basis_fps(c);
}
void cam_lookat(camera_t *c, const m_float *point)
{
	vec3_t d;
	vec3_sub(d, point, c->eye);
	vec3_normalize(d, d);

	// TODO: validate this
	c->angles[0] = m_asin(d[1]);
	m_float h = m_max(M_FLOAT_EPSILON, m_acos(d[1]));
	c->angles[1] = m_acos(-d[2]/h);

	recalculate_basis_fps(c);
}
void cam_pitch(camera_t *c, m_float angle)
{
	c->angles[0] += angle;
	recalculate_basis_fps(c);
}
void cam_pan(camera_t *c, m_float angle)
{
	c->angles[1] += angle;
	recalculate_basis_fps(c);
}
void cam_tilt(camera_t *c, m_float angle)
{
	c->angles[2] += angle;
	recalculate_basis_fps(c);
}