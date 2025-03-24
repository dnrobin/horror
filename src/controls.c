#include "shared.h"
#include "controls.h"

#include "gamedefs.h"
#include "camera.h"
#include "input.h"
#include "sound.h"
#include "game.h"

// track mouse movement
static float last_x;
static float last_y;

const vec2_t mouse_speed = { 0.002, 0.001 };

void update_mouse()
{
	// TODO: track mouse with the callback function instead!!
	int xpos, ypos;
	i_get_mouse_coordinates(&xpos, &ypos);

	static bool first_event = true;

    if (first_event) {
        last_x = xpos;
        last_y = ypos;
        first_event = false;
    }

    float dx = xpos - last_x;
    float dy = ypos - last_y;

	last_x = xpos;
    last_y = ypos;

	float mouse_y_dir = +1;
	if (g_mouse_invert_y) {
		mouse_y_dir = -1;
	}

    float angle_y = -dx * mouse_speed[0];
    float angle_x = dy * mouse_speed[1];

	cam_pan(g_camera, 	angle_y * g_mouse_sensitivity);
	cam_pitch(g_camera, angle_x * g_mouse_sensitivity * mouse_y_dir);
}

int G_DEBUG_CURRENT_SOUND_ID = 0;
void update_keys()
{
	if (get_key(GLFW_KEY_F1)) {
		g_state[G_PHY_CLIPPING] = !g_state[G_PHY_CLIPPING];
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
	
}

void c_update_controls()
{
	update_mouse();
	update_keys();
}
