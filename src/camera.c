#include <math.h>
#include "math.h"
#include "camera.h"

void c_camera_update_referential(t_camera* camera) {
	float pitch = PI/2 + camera->rotation.x;	// map sperical angles to local camera
	float yaw = PI - camera->rotation.y;
	float roll = camera->rotation.z;
	
	camera->forward = (t_vec3){ sin(pitch)*sin(yaw), cos(pitch), sin(pitch)*cos(yaw) };					// forward direction vector
	camera->up = (t_vec3){ -cos(pitch)*sin(yaw), sin(pitch), -cos(pitch)*cos(yaw) };					// up direction vector
	camera->right = (t_vec3){ -cos(yaw), sin(pitch)*cos(pitch)*cos(yaw)*(sin(yaw)-cos(yaw)), sin(yaw) };	// right direction vector
}

void c_camera_set_pos(t_camera* camera, const float x, const float y, const float z) {
	camera->position = (t_vec3){ x, y, z };
}

void c_camera_set_rot(t_camera* camera, const float x, const float y, const float z) {
	camera->rotation = (t_vec3){ x, y, z };
	c_camera_update_referential(camera);
}

void c_camera_rotate(t_camera* camera, const t_vec3 rotation) {
	camera->rotation = add(camera->rotation, rotation);
	c_camera_update_referential(camera);
}

void c_camera_move(t_camera* camera, const t_vec3 displacement) {
	camera->position = add(camera->position, displacement);
}

void c_camera_move_forward(t_camera* camera, const float distance) {
	c_camera_move(camera, scale(camera->forward, distance));
}

void c_camera_move_right(t_camera* camera, const float distance) {
	c_camera_move(camera, scale(camera->right, distance));
}

void c_camera_move_backward(t_camera* camera, const float distance) {
	c_camera_move(camera, scale(camera->forward, -distance));
}

void c_camera_move_left(t_camera* camera, const float distance) {
	c_camera_move(camera, scale(camera->right, -distance));
}

void c_camera_set_pos_offset(t_camera* camera, const float x, const float y, const float z) {
	camera->position_offset = (t_vec3){ x, y, z };
}
void c_camera_set_rot_offset(t_camera* camera, const float x, const float y, const float z) {
	camera->rotation_offset = (t_vec3){ x, y, z };
	c_camera_update_referential(camera);
}
void c_camera_rotate_offset(t_camera* camera, const t_vec3 rotation) {
	camera->rotation_offset = add(camera->rotation_offset, rotation);
	c_camera_update_referential(camera);
}
void c_camera_move_offset(t_camera* camera, const t_vec3 displacement) {
	camera->position_offset = add(camera->position_offset, displacement);
}