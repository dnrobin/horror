#include "shared.h"

#include "camera.h"
#include "controls.h"
#include "sound.h"
#include "game.h"

#include "input.h"

#include "math.h"

#include <math.h>

#include <stdlib.h>
#include <GLUT/glut.h>


static struct { int x, y; } old_coords;
static struct { float pitch, yaw; } look_angles;

void c_init_controls()
{
	look_angles.pitch = 0;
	look_angles.yaw = 0;

	old_coords.x = g_window_width/2;
	old_coords.y = g_window_height/2;
}

void c_update_controls(double dt)
{
	int xpos, ypos;

	i_get_mouse_coordinates(&xpos, &ypos);

	printf("xpos: %i, ypos: %i\n", xpos, ypos);

	// convert to normalized screen coordinates
	// Note: since we warp mouse back to center every frame,
	// these coordinates are actually deltas from one frame
	// to the next.
	float delta_x = (xpos - old_coords.x) / (float)g_window_width;
	float delta_y = (ypos - old_coords.y) / (float)g_window_height;

	old_coords.x = xpos;
	old_coords.y = ypos;

	printf("delta_x: %f, delta_y: %f\n", delta_x, delta_y);

	float mouse_y_dir = +1;
	if (g_mouse_invert_y) {
		mouse_y_dir = -1;
	}

	look_angles.pitch += delta_y * g_mouse_sensitivity * mouse_y_dir;
	look_angles.yaw   += delta_x * g_mouse_sensitivity;

	printf("pitch: %f, yaw: %f\n", look_angles.pitch, look_angles.yaw);

	printf("\n");

	if(look_angles.pitch > M_PI_2) {
		look_angles.pitch = M_PI_2;
	}

	if(look_angles.pitch < -M_PI_2) {
		look_angles.pitch = -M_PI_2;
	}

	// upate camera look direction
	g_camera->look.x = cosf(look_angles.yaw) * cosf(look_angles.pitch);
	g_camera->look.y = sinf(look_angles.pitch);
	g_camera->look.z = sinf(look_angles.yaw) * cosf(look_angles.pitch);

	c_camera_update_referential(g_camera);

	/* TO BE REMOVED... */
	g_camera->rotation.x = look_angles.pitch;
	g_camera->rotation.y = M_PI_2 + look_angles.yaw;
}

void handleSpecialKeyDown(int key, int x, int y)
{
	if ( key == GLFW_KEY_F1 ) {
		g_state[G_PHY_CLIPPING] = !g_state[G_PHY_CLIPPING];
	}
	else if ( key == GLFW_KEY_F2 ) {
		MY_SUPER_FLAG = !MY_SUPER_FLAG;
	}
}

int G_DEBUG_CURRENT_SOUND_ID = 0;
void handleKeyDown(unsigned char key, int x, int y) {

	static unsigned int q = 0;

	// ESC key exits program
	if ( key == GLFW_KEY_ESCAPE ) {
		exit(0);
	}
	
	switch( key ) {
		case GLFW_KEY_W:
			g_state[G_PLAYER_MOVING] = true;
			g_state[G_MOVING_FORWARD] = true;
			g_state[G_MOVING_BACKWARD] = false;
			break;
		case GLFW_KEY_S:
			g_state[G_PLAYER_MOVING] = true;
			g_state[G_MOVING_BACKWARD] = true;
			g_state[G_MOVING_FORWARD] = false;
			break;
		case GLFW_KEY_A:
			g_state[G_PLAYER_MOVING] = true;
			g_state[G_MOVING_LEFT] = true;
			g_state[G_MOVING_RIGHT] = false;
			break;
		case GLFW_KEY_D:
			g_state[G_PLAYER_MOVING] = true;
			g_state[G_MOVING_RIGHT] = true;
			g_state[G_MOVING_LEFT] = false;
			break;
		case GLFW_KEY_F:
			if ( !g_state[G_WITH_CANDLE] || !g_state[G_PLAYER_LIGHT_ON] )
	            g_state[G_PLAYER_LIGHT_ON] = !g_state[G_PLAYER_LIGHT_ON];
            g_state[G_WITH_CANDLE] = false;
            g_state[G_WITH_FLASH_LIGHT] = true;
            playSound(G_SOUND_ID_FLASH_LIGHT);
			break;
		case GLFW_KEY_G:
			if ( !g_state[G_WITH_FLASH_LIGHT] || !g_state[G_PLAYER_LIGHT_ON] )
	            g_state[G_PLAYER_LIGHT_ON] = !g_state[G_PLAYER_LIGHT_ON];
	        else {
	        	playSound(G_SOUND_ID_FLASH_LIGHT);	// play sound turning off
	        }
	        g_state[G_WITH_CANDLE] = true;
	        g_state[G_WITH_FLASH_LIGHT] = false;
			break;

#ifdef DEBUG_GAME

		case GLFW_KEY_SPACE:
            playSound(G_DEBUG_CURRENT_SOUND_ID);
			break;
        case GLFW_KEY_P:
            g_player_stress_level += 0.5;
            break;
        case GLFW_KEY_O:
            g_player_stress_level += 5.1;
            break;
        case GLFW_KEY_L:
            g_player_stress_level -= 0.5;
            break;
        case GLFW_KEY_E:
        	g_state[G_PLAYER_LOOK_BEHIND] = true;
        	break;
        case GLFW_KEY_M:
        	g_state[G_SHOW_WIREFRAME] = !g_state[G_SHOW_WIREFRAME];
        	break;

#endif
	}
	
	g_keys[ key ] = true;
}

void handleKeyUp(unsigned char key, int x, int y) {
	switch( key ) {
		case GLFW_KEY_W:
			g_state[G_MOVING_FORWARD] = false;
			break;
		case GLFW_KEY_S:
			g_state[G_MOVING_BACKWARD] = false;
			break;
		case GLFW_KEY_A:
			g_state[G_MOVING_LEFT] = false;
			break;
		case GLFW_KEY_D:
			g_state[G_MOVING_RIGHT] = false;
			break;
	}
	
	g_keys[ key ] = false;
	
	if ( !(g_keys[GLFW_KEY_W] || g_keys[GLFW_KEY_A] || g_keys[GLFW_KEY_S] || g_keys[GLFW_KEY_D]))
		g_state[G_PLAYER_MOVING] = false;
}

void handleMouseDown(int button, int state, int x, int y) {
	
}

void handleMouseMove(const int x, const int y) {
	
	/* weird hack to set cursor to middle on first call */
	static bool first_call = true;
	static bool f_just_warped = false;
    
    static int old_x = 0;
    
    if ( first_call ) {
        first_call = false;
        old_x = (int)g_window_width/2;
        f_just_warped = true;
        // glutWarpPointer((int)g_window_width/2, (int)g_window_height/2);
		// glfwSetCursorPos(g_win, (int)g_window_width/2, (int)g_window_height/2);
        return;
    }
	
	if ( f_just_warped ) {
		f_just_warped = false;
		return;
	}
	
	// calculate mouse speed
	float speed_x = (float)( x - old_x ) / g_window_width;
	
    g_camera->rotation.y += g_mouse_sensitivity * 2 * PI * speed_x;
    g_camera->rotation.x = ( g_mouse_invert_y ? -1.0 : 1.0 ) * PI * ( (float)y / g_window_height - 0.5 );
    c_camera_update_referential(&g_camera);
	
	old_x = x;
	
	if ( x <= 0 || x >= g_window_width ) {
		// put back the mouse cursor to the center of the screen
		f_just_warped = true;
		// glutWarpPointer((int)g_window_width/2, y);
		
		old_x = g_window_width/2;
	}
}