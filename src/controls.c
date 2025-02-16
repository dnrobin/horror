#include "shared.h"
#include "controls.h"

#include "input.h"
#include "sound.h"
#include "game.h"
#include "timing.h"

#include "math.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

static int G_DEBUG_CURRENT_SOUND_ID = 0;

void set_flash_light(bool state)
{
	if (!g_state[G_WITH_FLASH_LIGHT]) {
		playSound(G_SOUND_ID_FLASH_LIGHT);
	}
	g_state[G_WITH_CANDLE] = false;
	g_state[G_WITH_FLASH_LIGHT] = true;
	g_state[G_PLAYER_LIGHT_ON] = state;
}

void toggle_flash_light()
{
	set_flash_light(true);
	g_state[G_PLAYER_LIGHT_ON] = !g_state[G_PLAYER_LIGHT_ON];
	playSound(G_SOUND_ID_FLASH_LIGHT);
}

void set_candle_light(bool state)
{
	if (g_state[G_WITH_FLASH_LIGHT]) {
		playSound(G_SOUND_ID_FLASH_LIGHT);
	}
	g_state[G_WITH_CANDLE] = true;
	g_state[G_WITH_FLASH_LIGHT] = false;
	g_state[G_PLAYER_LIGHT_ON] = state;
}

void toggle_candle_light()
{
	set_candle_light(true);
	g_state[G_PLAYER_LIGHT_ON] = !g_state[G_PLAYER_LIGHT_ON];
}

void c_update_controls()
{
	if (get_key(KEY_F1)) {
		g_state[G_PHY_CLIPPING] = !g_state[G_PHY_CLIPPING];
	}
	
	if (get_key(KEY_F2)) {
		MY_SUPER_FLAG = !MY_SUPER_FLAG;
	}
	
	t_vec2 d = {0, 0};

	if (get_key(KEY_UP) || get_key(KEY_W)) {
		d.y = +1;
		g_state[G_MOVING_FORWARD] = true;
	}

	if (get_key(KEY_LEFT) || get_key(KEY_A)) {
		d.x = -1;
		g_state[G_MOVING_LEFT] = true;
	}

	if (get_key(KEY_DOWN) || get_key(KEY_S)) {
		d.y = -1;
		g_state[G_MOVING_BACKWARD] = true;
	}

	if (get_key(KEY_RIGHT) || get_key(KEY_D)) {
		d.x = +1;
		g_state[G_MOVING_RIGHT] = true;
	}

	// vec2_normalize(d);
	// move_player_in_direction(d);

	if (get_key(KEY_F)) {
		set_candle_light(0);
		toggle_flash_light();
	}

	if (get_key(KEY_G)) {
		set_flash_light(0);
		toggle_candle_light();
	}

#ifdef DEBUG_GAME
	if (get_key(KEY_SPACE)) {
		playSound(G_DEBUG_CURRENT_SOUND_ID);
	}

	if (get_key(KEY_P)) {
		g_player_stress_level += 0.5;
	}

	if (get_key(KEY_O)) {
		g_player_stress_level += 5.1;
	}

	if (get_key(KEY_L)) {
		g_player_stress_level -= 0.5;
	}

	if (get_key(KEY_E)) {
		// THIS SHOULD BE AN EVENT TRIGGER!
		g_state[G_PLAYER_LOOK_BEHIND] = true;
	}

	if (get_key(KEY_M)) {
		g_state[G_SHOW_WIREFRAME] = !g_state[G_SHOW_WIREFRAME];
	}
#endif

	double xpos, ypos;
	get_mouse_pos(&xpos, &ypos);
}

// int G_DEBUG_CURRENT_SOUND_ID = 0;
// void handleKeyDown(unsigned char key, int x, int y)
// {
// 	static unsigned int q = 0;

// 	switch (key) {
		
// 		case GLFW_KEY_W:
// 			g_state[G_PLAYER_MOVING] = true;
// 			g_state[G_MOVING_FORWARD] = true;
// 			g_state[G_MOVING_BACKWARD] = false;
// 			break;

// 		case GLFW_KEY_S:
// 			g_state[G_PLAYER_MOVING] = true;
// 			g_state[G_MOVING_BACKWARD] = true;
// 			g_state[G_MOVING_FORWARD] = false;
// 			break;

// 		case GLFW_KEY_A:
// 			g_state[G_PLAYER_MOVING] = true;
// 			g_state[G_MOVING_LEFT] = true;
// 			g_state[G_MOVING_RIGHT] = false;
// 			break;

// 		case GLFW_KEY_D:
// 			g_state[G_PLAYER_MOVING] = true;
// 			g_state[G_MOVING_RIGHT] = true;
// 			g_state[G_MOVING_LEFT] = false;
// 			break;

// 		case GLFW_KEY_F:
// 			if ( !g_state[G_WITH_CANDLE] || !g_state[G_PLAYER_LIGHT_ON] )
// 	            g_state[G_PLAYER_LIGHT_ON] = !g_state[G_PLAYER_LIGHT_ON];
//             g_state[G_WITH_CANDLE] = false;
//             g_state[G_WITH_FLASH_LIGHT] = true;
//             playSound(G_SOUND_ID_FLASH_LIGHT);
// 			break;

// 		case GLFW_KEY_G:
// 			if ( !g_state[G_WITH_FLASH_LIGHT] || !g_state[G_PLAYER_LIGHT_ON] )
// 	            g_state[G_PLAYER_LIGHT_ON] = !g_state[G_PLAYER_LIGHT_ON];
// 	        else {
// 	        	playSound(G_SOUND_ID_FLASH_LIGHT);	// play sound turning off
// 	        }
// 	        g_state[G_WITH_CANDLE] = true;
// 	        g_state[G_WITH_FLASH_LIGHT] = false;
// 			break;

// #ifdef DEBUG_GAME

// 		case GLFW_KEY_SPACE:
//             playSound(G_DEBUG_CURRENT_SOUND_ID);
// 			break;
// 		case GLFW_KEY_P:
//             g_player_stress_level += 0.5;
//             break;
// 		case GLFW_KEY_O:
//             g_player_stress_level += 5.1;
//             break;
// 		case GLFW_KEY_L:
//             g_player_stress_level -= 0.5;
//             break;
// 		case GLFW_KEY_E:
//         	g_state[G_PLAYER_LOOK_BEHIND] = true;
//         	break;
// 		case GLFW_KEY_M:
//         	g_state[G_SHOW_WIREFRAME] = !g_state[G_SHOW_WIREFRAME];
//         	break;
// #endif
// 	}
	
// 	g_keys[key] = true;
// }

// void handleKeyUp(unsigned char key, int x, int y)
// {
// 	switch( key ) {
// 		case GLFW_KEY_W:
// 			g_state[G_MOVING_FORWARD] = false;
// 			break;
// 		case GLFW_KEY_S:
// 			g_state[G_MOVING_BACKWARD] = false;
// 			break;
// 		case GLFW_KEY_A:
// 			g_state[G_MOVING_LEFT] = false;
// 			break;
// 		case GLFW_KEY_D:
// 			g_state[G_MOVING_RIGHT] = false;
// 			break;
// 	}
	
// 	g_keys[key] = false;
	
// 	if ( !(g_keys[GLFW_KEY_W] || g_keys[GLFW_KEY_S] || g_keys[GLFW_KEY_A] || g_keys[GLFW_KEY_D]) )
// 		g_state[G_PLAYER_MOVING] = false;
// }

// void handleMouseDown(int button, int state, int x, int y)
// {
	
// }

void handleMouseMove(const int x, const int y)
{	
	/* weird hack to set cursor to middle on first call */
	static bool first_call = true;
	static bool f_just_warped = false;
    
    static int old_x = 0;
    
    if ( first_call ) {
        first_call = false;
        old_x = (int)g_window_width/2;
        f_just_warped = true;
        // glutWarpPointer((int)g_window_width/2, (int)g_window_height/2);
        return;
    }
	
	if ( f_just_warped ) {
		f_just_warped = false;
		return;
	}
	
	// calculate mouse speed
	float speed_x = (float)( x - old_x ) / g_window_width;
	
    g_game_camera.rotation.y += g_mouse_sensitivity * 2 * PI * speed_x;
    g_game_camera.rotation.x = ( g_mouse_invert_y ? -1.0 : 1.0 ) * PI * ( (float)y / g_window_height - 0.5 );
    c_camera_update_referential(&g_game_camera);
	
	old_x = x;
	
	if ( x <= 0 || x >= g_window_width ) {
		// put back the mouse cursor to the center of the screen
		f_just_warped = true;
		// glutWarpPointer((int)g_window_width/2, y);
		
		old_x = g_window_width/2;
	}
}