#include <math.h>
#include "math.h"
#include "camera.h"

void c_camera_update_referential(t_camera* camera) {
	float pitch = PI/2 + camera->rotation.x;	// map sperical vec3_angles to local camera
	float yaw = PI - camera->rotation.y;
	float roll = camera->rotation.z;
	
	camera->forward = (vec3_t){ sin(pitch)*sin(yaw), cos(pitch), sin(pitch)*cos(yaw) };					// forward direction vector
	camera->up = (vec3_t){ -cos(pitch)*sin(yaw), sin(pitch), -cos(pitch)*cos(yaw) };					// up direction vector
	camera->right = (vec3_t){ -cos(yaw), sin(pitch)*cos(pitch)*cos(yaw)*(sin(yaw)-cos(yaw)), sin(yaw) };	// right direction vector
}

void c_camera_set_pos(t_camera* camera, const float x, const float y, const float z) {
	camera->position = (vec3_t){ x, y, z };
}

void c_camera_set_rot(t_camera* camera, const float x, const float y, const float z) {
	camera->rotation = (vec3_t){ x, y, z };
	c_camera_update_referential(camera);
}

void c_camera_rotate(t_camera* camera, const vec3_t rotation) {
	camera->rotation = vec3_add(camera->rotation, rotation);
	c_camera_update_referential(camera);
}

void c_camera_move(t_camera* camera, const vec3_t displacement) {
	camera->position = vec3_add(camera->position, displacement);
}

void c_camera_move_forward(t_camera* camera, const float distance) {
	c_camera_move(camera, vec3_scale(camera->forward, distance));
}

void c_camera_move_right(t_camera* camera, const float distance) {
	c_camera_move(camera, vec3_scale(camera->right, distance));
}

void c_camera_move_backward(t_camera* camera, const float distance) {
	c_camera_move(camera, vec3_scale(camera->forward, -distance));
}

void c_camera_move_left(t_camera* camera, const float distance) {
	c_camera_move(camera, vec3_scale(camera->right, -distance));
}

void c_camera_set_pos_offset(t_camera* camera, const float x, const float y, const float z) {
	camera->position_offset = (vec3_t){ x, y, z };
}
void c_camera_set_rot_offset(t_camera* camera, const float x, const float y, const float z) {
	camera->rotation_offset = (vec3_t){ x, y, z };
	c_camera_update_referential(camera);
}
void c_camera_rotate_offset(t_camera* camera, const vec3_t rotation) {
	camera->rotation_offset = vec3_add(camera->rotation_offset, rotation);
	c_camera_update_referential(camera);
}
void c_camera_move_offset(t_camera* camera, const vec3_t displacement) {
	camera->position_offset = vec3_add(camera->position_offset, displacement);
}