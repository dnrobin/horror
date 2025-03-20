#include "shared.h"
#include "camera.h"


void c_camera_update_referential(camera_t* cam) {
	
	// float pitch = PI/2 + cam->rotation.x;	// map sperical vec3_angles to local cam
	// float yaw = PI - cam->rotation.y;
	// float roll = cam->rotation.z;

	cam->look = vec3_normalize(cam->look);
	cam->up = vec3(0, 1, 0);
	cam->right = vec3_normalize(vec3_cross(cam->look, cam->up));
	cam->up = vec3_normalize(vec3_cross(cam->right, cam->look));
	
	// cam->look = (vec3_t){ sin(pitch)*sin(yaw), cos(pitch), sin(pitch)*cos(yaw) };					// look direction vector
	// cam->up = (vec3_t){ -cos(pitch)*sin(yaw), sin(pitch), -cos(pitch)*cos(yaw) };					// up direction vector
	// cam->right = (vec3_t){ -cos(yaw), sin(pitch)*cos(pitch)*cos(yaw)*(sin(yaw)-cos(yaw)), sin(yaw) };	// right direction vector
}

void c_camera_set_pos(camera_t* cam, const float x, const float y, const float z) {
	cam->position = (vec3_t){ x, y, z };
}

void c_camera_set_rot(camera_t* cam, const float x, const float y, const float z) {
	cam->rotation = (vec3_t){ x, y, z };
	c_camera_update_referential(cam);
}

void c_camera_rotate(camera_t* cam, const vec3_t rotation) {
	cam->rotation = vec3_add(cam->rotation, rotation);
	c_camera_update_referential(cam);
}

void c_camera_move(camera_t* cam, const vec3_t displacement) {
	cam->position = vec3_add(cam->position, displacement);
}

void c_camera_move_forward(camera_t* cam, const float distance) {
	c_camera_move(cam, vec3_scale(cam->look, distance));
}

void c_camera_move_right(camera_t* cam, const float distance) {
	c_camera_move(cam, vec3_scale(cam->right, distance));
}

void c_camera_move_backward(camera_t* cam, const float distance) {
	c_camera_move(cam, vec3_scale(cam->look, -distance));
}

void c_camera_move_left(camera_t* cam, const float distance) {
	c_camera_move(cam, vec3_scale(cam->right, -distance));
}

void c_camera_set_pos_offset(camera_t* cam, const float x, const float y, const float z) {
	cam->position_offset = (vec3_t){ x, y, z };
}
void c_camera_set_rot_offset(camera_t* cam, const float x, const float y, const float z) {
	cam->rotation_offset = (vec3_t){ x, y, z };
	c_camera_update_referential(cam);
}
void c_camera_rotate_offset(camera_t* cam, const vec3_t rotation) {
	cam->rotation_offset = vec3_add(cam->rotation_offset, rotation);
	c_camera_update_referential(cam);
}
void c_camera_move_offset(camera_t* cam, const vec3_t displacement) {
	cam->position_offset = vec3_add(cam->position_offset, displacement);
}