#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "math.h"

typedef struct t_camera {
	vec3_t position;
	vec3_t position_offset;
	vec3_t rotation;
	vec3_t rotation_offset;
	vec3_t forward;		// -z in local coordinate system
	vec3_t right;		// x in local coordinate system
	vec3_t up;			// y in local coordinate system
} t_camera;

void c_camera_update_referential(t_camera* camera);
void c_camera_set_pos(t_camera* camera, const float x, const float y, const float z);
void c_camera_set_rot(t_camera* camera, const float x, const float y, const float z);
void c_camera_rotate(t_camera* camera, const vec3_t rotation);
void c_camera_move(t_camera* camera, const vec3_t displacement);
void c_camera_move_forward(t_camera* camera, const float distance);
void c_camera_move_right(t_camera* camera, const float distance);
void c_camera_move_backward(t_camera* camera, const float distance);
void c_camera_move_left(t_camera* camera, const float distance);

void c_camera_set_pos_offset(t_camera* camera, const float x, const float y, const float z);
void c_camera_set_rot_offset(t_camera* camera, const float x, const float y, const float z);
void c_camera_rotate_offset(t_camera* camera, const vec3_t rotation);
void c_camera_move_offset(t_camera* camera, const vec3_t displacement);

#endif