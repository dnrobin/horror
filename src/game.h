#ifndef __GAME_H__
#define __GAME_H__

#include "common.h"

#include "math.h"
#include "graphics.h"
#include "sound.h"
#include "collision.h"
#include "physics.h"
#include "camera.h"

void init();
void update();
void shutdown();

/* include debug controls and variables */
#define DEBUG_GAME

bool MY_SUPER_FLAG;

t_physics_particle g_camera_physics_model;
t_bounding_sphere g_camera_collision_model;
t_sound_emitter* g_camera_sound_emitter_model;
h_collision_surface g_collisions;
int g_collisions_count;

float g_player_run_speed;
float g_player_walk_speed;
float g_player_crouch_speed;

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

/* Texture id's shared globally --- CRAP MUST FIX */
#define G_TEX_WALL_DIFFUSE_ID 100
#define G_TEX_WALL_SPECULAR_ID 101
#define G_TEX_WALL_HEIGHT_ID 102
#define G_TEX_WALL_NORMAL_ID 103
#define G_TEX_FLOOR_DIFFUSE_ID 110
#define G_TEX_FLOOR_SPECULAR_ID 111
#define G_TEX_FLOOR_HEIGHT_ID 112
#define G_TEX_FLOOR_NORMAL_ID 113
#define G_TEX_CIEL_DIFFUSE_ID 120
#define G_TEX_CIEL_SPECULAR_ID 121
#define G_TEX_CIEL_HEIGHT_ID 122
#define G_TEX_CIEL_NORMAL_ID 123

#define G_FOG_TEXTURE_ID 500
#define G_FLASHLIGHT_DECAL_ID 501

/* game state flags */
#define G_STATE_ACTIVE		0
#define G_FULLSCREEN		1
#define G_SHOW_WIREFRAME	2

#define G_DEATH_ZONE		5

#define G_PLAYER_PARALIZED		14
#define G_PLAYER_MOVING			15
#define	G_PLAYER_CROUCHING		16
#define	G_PLAYER_CROUCHED		17
#define G_PLAYER_WALKING		18
#define G_PLAYER_RUNNING		19
#define G_PLAYER_JUMPING		20
#define G_PLAYER_FALLING		21

#define	G_MOVING_FORWARD		22
#define	G_MOVING_RIGHT			23
#define	G_MOVING_BACKWARD		24
#define	G_MOVING_LEFT			25

#define G_PLAYER_LOOK_BEHIND	28
#define G_PLAYER_LOOK_FRANTIC	29

#define G_SOUND_ON				30
#define G_SOUND_MUTED			31
#define G_SOUND_PLAYED			32
#define G_SOUND_PAUSED			33
#define G_SOUND_STOPPED			34

#define G_PLAYER_STRESS_LEVEL_1		40
#define G_PLAYER_STRESS_LEVEL_2		41
#define G_PLAYER_STRESS_LEVEL_3		42
#define G_PLAYER_STRESS_LEVEL_4		43
#define G_PLAYER_STRESS_LEVEL_5		44
#define G_PLAYER_STRESS_LEVEL_6		45
#define G_PLAYER_STRESS_LEVEL_7		46
#define G_PLAYER_STRESS_LEVEL_8		47
#define G_PLAYER_STRESS_LEVEL_9		48
#define G_PLAYER_STRESS_LEVEL_10	49

#define G_PHY_CLIPPING		50
#define G_PHY_FREEFALL		51
#define G_PHY_SOLID_GROUND	52
#define G_PHY_FLY			53

#define G_PLAYER_LIGHT_ON       100
#define G_LIGHTS_ON             101
#define G_WITH_CANDLE			102
#define G_WITH_FLASH_LIGHT		103

#define G_PARTY_LIGHT_ON		105

#define G_HAS_CANDLE			150
#define G_HAS_FLASH_LIGHT		151
#define G_HAS_FLARES			152

#define G_DEBUG_ALL				245
#define G_DEBUG_LIGHTS			246
#define G_DEBUG_PHYSICS			247
#define G_DEBUG_ANIMATIONS		248
#define G_DEBUG_CONTROLS		249
#define G_DEBUG_CAMERA			250

/* sound id's */
#define G_SOUND_ID_PLAYER_WALK			3
#define G_SOUND_ID_PLAYER_CROUCH		15
#define G_SOUND_ID_PLAYER_CROUCHED		16
#define G_SOUND_ID_PLAYER_DRAG			16

#define G_SOUND_ID_FLASH_LIGHT			26

#define G_SOUND_ID_SHEMALE				1
#define G_SOUND_ID_DISTURBING_MUSIC		2	// not used anymore?

#define G_SOUND_ID_DARK_SOUND_1			18
#define G_SOUND_ID_DARK_SOUND_2			17

#define G_SOUND_ID_LOW_BREATHING		7
#define G_SOUND_ID_NORMAL_BREATHING		8
#define G_SOUND_ID_SCARED_BREATHING		9
#define G_SOUND_ID_FAST_BREATHING		10
#define G_SOUND_ID_MOANING				11

#define G_SOUND_ID_LOW_HEARTBEAT		4
#define G_SOUND_ID_NORMAL_HEARTBEAT		5
#define G_SOUND_ID_FAST_HEARTBEAT		6

#define G_SOUND_ID_FOOTSTEPS			12
#define G_SOUND_ID_GROANING				13
#define G_SOUND_ID_WHISPER				14

#define G_SOUND_ID_GRUNT_1              21
#define G_SOUND_ID_GRUNT_2              22
#define G_SOUND_ID_GRUNT_3              13

#define G_SOUND_ID_INTRO_NARRATION      19

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

// sepecial globals
int G_WALK_SOUND_ID;

#endif