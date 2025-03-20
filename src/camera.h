#ifndef __MAZE_GAME_CAM_H__
#define __MAZE_GAME_CAM_H__

typedef struct {

	vec3_t				eye;		// world-space eye position
	
	vec3_t				right;
	vec3_t				look;		// look direction (rh z)
	vec3_t				up;			// up vector
	
	vec3_t 				angles;		// [pitch, yaw, roll]
	
	float 				yfov;
	float				znear;
	float				zfar;
} camera_t;

/*
 Animating the camera should actually be a point
 on a sphere surrounding the camera which the cam
 can track using lookat.
*/

void cam_get_transform(camera_t *c, mat4_t out);
void cam_get_inv_transform(camera_t *c, mat4_t out);

void cam_reset_orientation(camera_t *c);
void cam_move_to(camera_t *c, const vec3_t p);
void cam_move_by(camera_t *c, const vec3_t v);
void cam_move_forward(camera_t *c, float d);
void cam_move_backward(camera_t *c, float d);
void cam_move_left(camera_t *c, float d);
void cam_move_right(camera_t *c, float d);
void cam_move_up(camera_t *c, float d);
void cam_move_down(camera_t *c, float d);
void cam_set_angles(camera_t *c, m_float pitch, m_float yaw, m_float roll);
void cam_lookat(camera_t *c, const m_float *p);
void cam_pitch(camera_t *c, m_float angle);
void cam_tilt(camera_t *c, m_float angle);
void cam_pan(camera_t *c, m_float angle);

#endif