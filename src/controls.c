#include "shared.h"
#include "controls.h"

#include "gamedefs.h"
#include "camera.h"
#include "input.h"
#include "sound.h"
#include "game.h"

static struct { int x, y; } old_coords;
static struct { float pitch, yaw; } look_angles;

void update_mouse()
{
	int xpos, ypos;

	i_get_mouse_coordinates(&xpos, &ypos);

	// convert to normalized screen coordinates
	// Note: since we warp mouse back to center every frame,
	// these coordinates are actually deltas from one frame
	// to the next.
	float delta_x = (xpos - old_coords.x) / (float)g_window_width;
	float delta_y = (ypos - old_coords.y) / (float)g_window_height;

	old_coords.x = xpos;
	old_coords.y = ypos;

	float mouse_y_dir = +1;
	if (g_mouse_invert_y) {
		mouse_y_dir = -1;
	}

	look_angles.pitch += delta_y * g_mouse_sensitivity * mouse_y_dir;
	look_angles.yaw   += delta_x * g_mouse_sensitivity;

	if(look_angles.pitch > PI/2.f) {
		look_angles.pitch = PI/2.f;
	}

	if(look_angles.pitch < -PI/2.f) {
		look_angles.pitch = -PI/2.f;
	}

	// upate camera look direction
	g_camera->look.x = m_cos(look_angles.yaw) * m_cos(look_angles.pitch);
	g_camera->look.y = m_sin(look_angles.pitch);
	g_camera->look.z = m_sin(look_angles.yaw) * m_cos(look_angles.pitch);

	c_camera_update_referential(g_camera);

	/* TO BE REMOVED... */
	g_camera->rotation.x = look_angles.pitch;
	g_camera->rotation.y = PI/2.f + look_angles.yaw;
}

int G_DEBUG_CURRENT_SOUND_ID = 0;
void update_keys()
{
	if (get_key(GLFW_KEY_F1)) {
		g_state[G_PHY_CLIPPING] = !g_state[G_PHY_CLIPPING];
	}
	
	if (get_key(GLFW_KEY_F2)) {
		MY_SUPER_FLAG = !MY_SUPER_FLAG;
	}

	g_state[G_PLAYER_MOVING] = false;

	if (get_key(GLFW_KEY_W)) {
		g_state[G_PLAYER_MOVING] = true;
		g_state[G_MOVING_FORWARD] = true;
		g_state[G_MOVING_BACKWARD] = false;
	}
	else {
		g_state[G_MOVING_FORWARD] = false;
	}

	if (get_key(GLFW_KEY_S)) {
		g_state[G_PLAYER_MOVING] = true;
		g_state[G_MOVING_BACKWARD] = true;
		g_state[G_MOVING_FORWARD] = false;
	}
	else {
		g_state[G_MOVING_BACKWARD] = false;
	}
	
	if (get_key(GLFW_KEY_A)) {
		g_state[G_PLAYER_MOVING] = true;
		g_state[G_MOVING_LEFT] = true;
		g_state[G_MOVING_RIGHT] = false;
	}
	else {
		g_state[G_MOVING_LEFT] = false;
	}

	if (get_key(GLFW_KEY_D)) {
		g_state[G_PLAYER_MOVING] = true;
		g_state[G_MOVING_RIGHT] = true;
		g_state[G_MOVING_LEFT] = false;
	}
	else {
		g_state[G_MOVING_RIGHT] = false;
	}

	if (get_key(GLFW_KEY_F)) {
		if ( !g_state[G_WITH_CANDLE] || !g_state[G_PLAYER_LIGHT_ON] )
			g_state[G_PLAYER_LIGHT_ON] = !g_state[G_PLAYER_LIGHT_ON];
		g_state[G_WITH_CANDLE] = false;
		g_state[G_WITH_FLASH_LIGHT] = true;
		playSound(G_SOUND_ID_FLASH_LIGHT);
	}

	if (get_key(GLFW_KEY_G)) {
		if ( !g_state[G_WITH_FLASH_LIGHT] || !g_state[G_PLAYER_LIGHT_ON] )
			g_state[G_PLAYER_LIGHT_ON] = !g_state[G_PLAYER_LIGHT_ON];
		else {
			playSound(G_SOUND_ID_FLASH_LIGHT);	// play sound turning off
		}
		g_state[G_WITH_CANDLE] = true;
		g_state[G_WITH_FLASH_LIGHT] = false;
	}

#ifdef DEBUG_GAME
	if (get_key(GLFW_KEY_SPACE)) {
		playSound(G_DEBUG_CURRENT_SOUND_ID);
	}
	if (get_key(GLFW_KEY_P)) {
		g_player_stress_level += 10;
	}
	if (get_key(GLFW_KEY_O)) {
		g_player_stress_level += 0.01;
	}
	if (get_key(GLFW_KEY_L)) {
		g_player_stress_level -= 0.01;
	}
	if (get_key(GLFW_KEY_E)) {
		g_state[G_PLAYER_LOOK_BEHIND] = true;
	}
	if (get_key(GLFW_KEY_M)) {
		g_state[G_SHOW_WIREFRAME] = !g_state[G_SHOW_WIREFRAME];
	}
#endif
}

void c_init_controls()
{
	look_angles.pitch = 0;
	look_angles.yaw = 0;

	old_coords.x = g_window_width/2;
	old_coords.y = g_window_height/2;
}

void c_update_controls()
{
	update_mouse();
	update_keys();
}
