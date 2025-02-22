#ifndef __CAMERA_H__
#define __CAMERA_H__

/**
 * Camera holds everything to generate the view transform:
 * - position, orientation and field of view.
 * Some functions are provided to alter the state of the camera
 * through local transformations. These functions are mainly used
 * by the animation subsystem to create the illusion of head movement.
 */

typedef struct {

	vec3_t position;
	vec3_t rotation;

	vec3_t right;
	vec3_t up;

	vec3_t position_offset;
	vec3_t rotation_offset;

	float fov_angle;
	vec3_t look;
} camera_t;

void c_camera_update_referential(camera_t* camera);
void c_camera_set_pos(camera_t* camera, const float x, const float y, const float z);
void c_camera_set_rot(camera_t* camera, const float x, const float y, const float z);

// for animation purposes:

void c_camera_rotate(camera_t* camera, const vec3_t rotation);
void c_camera_move(camera_t* camera, const vec3_t displacement);
void c_camera_move_forward(camera_t* camera, const float distance);
void c_camera_move_right(camera_t* camera, const float distance);
void c_camera_move_backward(camera_t* camera, const float distance);
void c_camera_move_left(camera_t* camera, const float distance);

void c_camera_set_pos_offset(camera_t* camera, const float x, const float y, const float z);
void c_camera_set_rot_offset(camera_t* camera, const float x, const float y, const float z);
void c_camera_rotate_offset(camera_t* camera, const vec3_t rotation);
void c_camera_move_offset(camera_t* camera, const vec3_t displacement);

#endif