#ifndef __MAZE_GAME_H__
#define __MAZE_GAME_H__

#include "sound.h"
#include "physics.h"
#include "collision.h"
#include "camera.h"

void init();
void update();
void shutdown();

t_physics_particle g_camera_physics_model;
t_bounding_sphere g_camera_collision_model;
t_sound_emitter* g_camera_sound_emitter_model;
h_collision_surface g_collisions;
int g_collisions_count;

float g_player_run_speed;
float g_player_walk_speed;
float g_player_crouch_speed;
float g_player_fov;

/* global object variables */
extern camera_t *g_camera;

/* window state variables */
uint g_window_width;
uint g_window_height;
uint g_window_x;
uint g_window_y;
uint g_frame_millisec;

/* game user settings */
float g_mouse_sensitivity;		// values range 0.0 - 1.0
bool g_mouse_invert_y;

/* graphics shader control variables */
float g_parallax_depth;
float g_parallax_quality;
unsigned int g_shader_settings0[4];
unsigned int g_shader_settings1[4];
unsigned int g_shader_settings2[4];
unsigned int g_shader_settings3[4];
float g_vision_adapt_factor;

// stress level of player
float g_player_stress_level;
float g_player_stress_level_min;
float g_player_stress_level_increase_rate;
float g_player_stress_level_decrease_rate;
float g_player_reaction_time;
float g_player_anxiety_level;

// CHEAP WAY OUT OF THE PROBLEM...
float g_walking_animation_rate;

// array to hold game state flags
bool g_state[256];

// array to hold active keys
bool g_keys[256];

// special globals
int G_WALK_SOUND_ID;

#endif