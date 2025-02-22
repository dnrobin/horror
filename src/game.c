#include "shared.h"
#include "game.h"

#include "trigger.h"
#include "timing.h"
#include "camera.h"
#include "collision.h"
#include "controls.h"
#include "shaders.h"
#include "render.h"
#include "map.h"

#include "glad.h"

#include <math.h>
#include <stdlib.h>

// private game state
static camera_t game_camera;

// set global pointers
camera_t *g_camera = &game_camera;



/* TO BE MOVED */

// ********************************************************************
// BEGIN MAP RESOURCE DEFINITIONS
// ********************************************************************
int resources_count = 32;
t_resource_descriptor resources[] = {
	{ 987, RESOURCE_TYPE_IMAGE, "res/textures/walltex_06_diffuse.bmp" },
	{ 989, RESOURCE_TYPE_IMAGE, "res/textures/walltex_06_diffuse2.bmp" },
	{ 988, RESOURCE_TYPE_IMAGE, "res/textures/floortex_5.bmp" },
	{ 990, RESOURCE_TYPE_SOUND, "res/sounds/background_6.wav"},
	{ 991, RESOURCE_TYPE_SOUND, "res/sounds/background_3.wav"},
	{ 992, RESOURCE_TYPE_SOUND, "res/sounds/music_1.wav"},
	{ 993, RESOURCE_TYPE_SOUND, "res/sounds/walk_4.wav"},
	{ 994, RESOURCE_TYPE_SOUND, "res/sounds/heart_1.wav"},
	{ 995, RESOURCE_TYPE_SOUND, "res/sounds/heart_2.wav"},
	{ 996, RESOURCE_TYPE_SOUND, "res/sounds/heart_3.wav"},
	{ 997, RESOURCE_TYPE_SOUND, "res/sounds/breathe_1.wav"},
	{ 998, RESOURCE_TYPE_SOUND, "res/sounds/breathe_2.wav"},
	{ 999, RESOURCE_TYPE_SOUND, "res/sounds/breathe_3.wav"},
	{ 1000, RESOURCE_TYPE_SOUND, "res/sounds/breathe_4.wav"},
	{ 1001, RESOURCE_TYPE_SOUND, "res/sounds/moan_1.wav"},
	{ 1002, RESOURCE_TYPE_SOUND, "res/sounds/footsteps_1.wav"},
	{ 1003, RESOURCE_TYPE_SOUND, "res/sounds/grunt_behind_1.wav"},
	{ 1004, RESOURCE_TYPE_SOUND, "res/sounds/whisper_1.wav"},
	{ 1005, RESOURCE_TYPE_SOUND, "res/sounds/fx_7.wav"},
	{ 1006, RESOURCE_TYPE_SOUND, "res/sounds/fx_8.wav"},
	{ 1007, RESOURCE_TYPE_SOUND, "res/sounds/dark_sound_1.wav"},
	{ 1008, RESOURCE_TYPE_SOUND, "res/sounds/fx_beat_1.wav"},
	{ 1009, RESOURCE_TYPE_SOUND, "res/sounds/intro_naration.wav"},
	{ 1010, RESOURCE_TYPE_SOUND, "res/sounds/background_2.wav"},
	{ 1011, RESOURCE_TYPE_IMAGE, "res/textures/vision_1.bmp"},
    { 1012, RESOURCE_TYPE_SOUND, "res/sounds/grunt_far_1.wav"},
    { 1013, RESOURCE_TYPE_SOUND, "res/sounds/grunt_close_1.wav"},
    { 1014, RESOURCE_TYPE_IMAGE, "res/textures/mask2.bmp"},
    { 1015, RESOURCE_TYPE_IMAGE, "res/textures/noise_1.bmp"},
    { 1016, RESOURCE_TYPE_SOUND, "res/sounds/flash_light_1.wav"},
    { 1017, RESOURCE_TYPE_SOUND, "res/sounds/background_7.wav"},
    { 1018, RESOURCE_TYPE_IMAGE, "res/textures/fog.bmp"}
};

int textures_count = 7;
t_texture_resource_descriptor textures[] = {
	{ 987, 	0, 803, 786, 4, GL_BGRA, GL_UNSIGNED_BYTE, GL_LINEAR },
	{ 989, 	0, 800, 600, 4, GL_BGRA, GL_UNSIGNED_BYTE, GL_LINEAR },
	{ 988, 	0, 720, 464, 4, GL_BGRA, GL_UNSIGNED_BYTE, GL_LINEAR },
	{ 1011, 0, 867, 650, 4, GL_BGRA, GL_UNSIGNED_BYTE, GL_LINEAR },
    { 1014, 0, 867, 650, 4, GL_BGRA, GL_UNSIGNED_BYTE, GL_LINEAR },
    { 1015, 0, 867, 650, 3, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR },
    { 1018, 0, 800, 600, 4, GL_BGRA, GL_UNSIGNED_BYTE, GL_LINEAR }
};

int sounds_count = 25;
t_sound_resource_descriptor sounds[] = {
	{ 990, SOUND_EMIT_GLOBAL | SOUND_EMIT_LOOPED | SOUND_EMIT_AUTOPLAY, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.12, 1.0, 1.0, 0, 0, 1.0, 1.0, 0, 0, 0, 0, 0 },
	{ 991, SOUND_EMIT_LOOPED, {1.0, 2.0, -14.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.35, 1.0, 56.0, 5.0, 7.0, 0.0, 1.0, 0, 0, 0, 0, 0 },
	{ 992, SOUND_EMIT_GLOBAL | SOUND_EMIT_LOOPED, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.4, 1.0, 30.0, 0.1, 2.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0, 0 },
	{ 993, 0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 0.15, 1.0, 1.0, 0, 0, 1, 1, 0, 0, 1, 0, 0 },
	{ 994, SOUND_EMIT_GLOBAL | SOUND_EMIT_LOOPED, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.10, 1.0, 1.0, 0, 0, 1.0, 1.0, 0, 0, 0, 0, 0 },
	{ 995, SOUND_EMIT_GLOBAL | SOUND_EMIT_LOOPED, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.18, 1.0, 1.0, 0, 0, 1.0, 1.0, 0, 0, 0, 0, 0 },
	{ 996, SOUND_EMIT_GLOBAL | SOUND_EMIT_LOOPED, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.28, 1.0, 1.0, 0, 0, 1.0, 1.0, 0, 0, 0, 0, 0 },
	{ 997, SOUND_EMIT_GLOBAL | SOUND_EMIT_LOOPED, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.05, 1.0, 1.0, 0, 0, 1.0, 1.0, 0, 0, 0, 0, 0 },
	{ 998, SOUND_EMIT_GLOBAL | SOUND_EMIT_LOOPED, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.15, 1.0, 1.0, 0, 0, 1.0, 1.0, 0, 0, 0, 0, 0 },
	{ 999, SOUND_EMIT_GLOBAL | SOUND_EMIT_LOOPED, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.10, 1.0, 1.0, 0, 0, 1.0, 1.0, 0, 0, 0, 0, 0 },
	{ 1000, SOUND_EMIT_GLOBAL | SOUND_EMIT_LOOPED, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.05, 1.0, 1.0, 0, 0, 1.0, 1.0, 0, 0, 0, 0, 0 },
	{ 1001, SOUND_EMIT_GLOBAL | SOUND_EMIT_LOOPED, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.13, 1.0, 1.0, 0, 0, 1.0, 1.0, 0, 0, 0, 0, 0 },
	{ 1002, SOUND_EMIT_GLOBAL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.3, 1.0, 1.0, 0, 0, 1.0, 1.0, 0, 0, 0, 0, 0 },
	{ 1003, SOUND_EMIT_GLOBAL, {-9.0, 0.0, -11.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.94, 1.0, 4.0, 0.5, 5.0, 0.0, 1.0, 0, 0, 0, 0, 0 },
	{ 1004, SOUND_EMIT_GLOBAL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.3, 1.0, 10.0, 0.1, 3.0, 0.0, 1.0, 0, 0, 0, 0, 0 },
	{ 1005, 0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 0.05, 1.0, 1.0, 0, 0, 1, 1, 0, 0, 1, 0, 0 },
	{ 1006, 0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 0.3, 1.0, 1.0, 0, 0, 1, 1, 0, 0, 1, 0, 0 },
	{ 1007, SOUND_EMIT_GLOBAL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1.0, 1.0, 10.0, 0.1, 3.0, 0.0, 1.0, 0, 0, 0, 0, 0 },
	{ 1008, SOUND_EMIT_GLOBAL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1.0, 1.0, 10.0, 0.1, 3.0, 0.0, 1.0, 0, 0, 0, 0, 0 },
	{ 1009, SOUND_EMIT_GLOBAL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.2, 1.0, 1.0, 0, 0, 1.0, 1.0, 0, 0, 0, 0, 0 },
	{ 1010, SOUND_EMIT_GLOBAL | SOUND_EMIT_LOOPED | SOUND_EMIT_AUTOPLAY, {-4.0, -1.0, -14.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.01, 1.0, 56.0, 0.25, 3.0, 0.0, 1.0, 0, 0, 0, 0, 0 },
    { 1012, SOUND_EMIT_GLOBAL, {-9.0, 0.0, -11.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.24, 1.0, 4.0, 0.06, 5.0, 0.0, 1.0, 0, 0, 0, 0, 0 },
    { 1013, SOUND_EMIT_GLOBAL, {-9.0, 0.0, -11.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.62, 1.0, 4.0, 0.08, 5.0, 0.0, 1.0, 0, 0, 0, 0, 0 },
    { 1016, 0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 0.05, 1.0, 1.0, 0, 0, 1, 1, 0, 0, 1, 0, 0 },
    { 1017, SOUND_EMIT_GLOBAL | SOUND_EMIT_LOOPED | SOUND_EMIT_AUTOPLAY, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.1, 1.0, 1.0, 0, 0, 1.0, 1.0, 0, 0, 0, 0, 0 },
};

// typedef struct t_light {
// 	vec3_t position;
// 	vec3_t direction;
// 	float color_ambient[3];
// 	float color_diffuse[3];
// 	float color_specular[3];
// 	int type;	// ambient, directional, point, spot
// 	float atten_factor_const;
// 	float atten_factor_lin;
// 	float atten_factor_quad;
// 	float atten_factor_exp;
// 	float vec3_angle;
// } t_light;

// int lights_count = 7;
// t_lights lights[] = {
// 	{}
// };

// ********************************************************************
// END MAP RESOURCE DEFINITIONS
// ********************************************************************


// walking animation
float g_player_walk_anim_frames_count = 100;
float g_player_walk_anim_frames[100] = {0, 0, 0, 0, 0, 0, -0.28661436, -0.903256429, -1.476376847, -2.000888557, -2.472135955, -2.885936216, -3.23861642, -3.527046152, -3.748665289, -3.901506725, -3.984213827, -3.996052483, -3.936917611, -3.807334096, -3.60845213, -3.342037005, -3.01045344, -2.616644594, -2.164105942, -1.656854249, -1.099391918, -0.496667023, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.496667023, -1.099391918, -1.656854249, -2.164105942, -2.616644594, -3.01045344, -3.342037005, -3.60845213, -3.807334096, -3.936917611, -3.996052483, -3.984213827, -3.901506725, -3.748665289, -3.527046152, -3.23861642, -2.885936216, -2.472135955, -2.000888557, -1.476376847, -0.903256429, -0.28661436, 0, 0, 0, 0, 0};

/* trigger callbacks */

void setStressLevel(const float level) {
	// impact on anxiety
	g_player_anxiety_level += (level - g_player_stress_level)/5.0;
	
	// set the new minimum
	g_player_stress_level_min += g_player_anxiety_level*g_player_stress_level/120.0;
	
	// update stress level
	g_player_stress_level = level > 10.0 ? 10.0 : ( level < 0 ? 0 : level);
	
	printf("player stress:%0.1f, axiety:%0.1f and lower bound at %0.1f\n",g_player_stress_level,g_player_anxiety_level,g_player_stress_level_min);
}

void trigger_player_scared_level10() {
	setStressLevel(10.0);
}

void trigger_player_scared_level9() {
	setStressLevel(9.0);
}

void trigger_player_scared_level8() {
	setStressLevel(8.0);
}

void trigger_player_scared_level7() {
	setStressLevel(7.0);
}

void trigger_player_scared_level6() {
	setStressLevel(6.0);
}

void trigger_player_scared_level5() {
	setStressLevel(5.0);
}

void trigger_player_scared_level4() {
	setStressLevel(4.0);
}

void trigger_player_scared_level3() {
	setStressLevel(3.0);
}

void trigger_player_look_behind() {
	g_state[G_PLAYER_LOOK_BEHIND] = true;
}

void trigger_player_frantic() {
	g_state[G_PLAYER_LOOK_FRANTIC] = true;
}

void trigger_whisper() {
	playSound(G_SOUND_ID_WHISPER);
	addTimer(850, &trigger_player_look_behind);
	addTimer(g_player_reaction_time, &trigger_player_scared_level6);
}

void trigger_footsteps() {
	playSound(G_SOUND_ID_FOOTSTEPS);
	addTimer(850, &trigger_player_frantic);
	addTimer(g_player_reaction_time, &trigger_player_scared_level8);
}

void trigger_grunt() {
	playSound(G_SOUND_ID_GROANING);
	addTimer(850, &trigger_player_frantic);
	addTimer(g_player_reaction_time, &trigger_player_scared_level7);
}

void trigger_music() {
	playSound(G_SOUND_ID_DISTURBING_MUSIC);
	addTimer(1200, &trigger_player_scared_level7);
}

void trigger_near_deathzone() {
	playSound(G_SOUND_ID_SHEMALE);
	addTimer(5400, &trigger_player_scared_level6);
}

void trigger_enter_deathzone() {
	g_state[G_DEATH_ZONE] = true;
	addTimer(2500, &trigger_player_scared_level10);
}

void trigger_flashlight() {
	g_state[G_HAS_FLASH_LIGHT] = true;
	g_state[G_WITH_FLASH_LIGHT] = true;
	g_state[G_PLAYER_LIGHT_ON] = true;
	playSound(G_SOUND_ID_PLAYER_CROUCH);		// I know.. not the appropriate sound
}

void trigger_party_light() {
	g_state[G_PARTY_LIGHT_ON] = true;
	addTimer(g_player_reaction_time, &trigger_player_scared_level10);
}

void trigger_player_start_event_1() {
	g_state[G_PLAYER_PARALIZED] = false;
	g_state[G_PLAYER_LIGHT_ON] = true;
}

void trigger_player_start_event_2() {
	playSound(G_SOUND_ID_INTRO_NARRATION);
}

void trigger_player_start_event() {
	g_state[G_PLAYER_PARALIZED] = true;
	g_state[G_PLAYER_LIGHT_ON] = false;
	g_state[G_PLAYER_CROUCHING] = true;
	trigger_player_scared_level6();
	addTimer(3600, &trigger_player_start_event_2);
	addTimer(16000, &trigger_player_start_event_1);
}

void trigger_step_1a0() {
	playSound(G_SOUND_ID_FOOTSTEPS);
	addTimer(650, &trigger_player_look_behind);
	addTimer(300, &trigger_player_scared_level5);
}

void trigger_step_1a() {
    playSound(G_SOUND_ID_GRUNT_1);
    g_state[G_PLAYER_LIGHT_ON] = true;
    addTimer(450, &trigger_player_look_behind);
}

void trigger_step_1b() {
	playSound(G_SOUND_ID_DARK_SOUND_1);
	addTimer(300, &trigger_player_scared_level4);
}

void trigger_step_2() {
	playSound(G_SOUND_ID_DARK_SOUND_2);
	addTimer(1000, &trigger_player_scared_level5);
}

void trigger_step_3a() {
    playSound(G_SOUND_ID_GRUNT_1);
    addTimer(300, &trigger_player_scared_level5);
}

void trigger_step_3b_1() {
	addTimer(300, &trigger_player_scared_level6);
	g_state[G_PLAYER_PARALIZED] = false;
}

void trigger_step_3b() {
    playSound(G_SOUND_ID_GRUNT_2);
    //g_state[G_PLAYER_PARALIZED] = true;
    //addTimer(300, &trigger_player_look_behind);
    addTimer(650, &trigger_step_3b_1);
}

void trigger_step_3c_2() {
	g_state[G_PLAYER_PARALIZED] = false;
}

void trigger_step_3c_1() {
	g_state[G_PLAYER_PARALIZED] = true;
	addTimer(650, &trigger_player_look_behind);
	addTimer(800, &trigger_player_scared_level8);
	addTimer(3000, &trigger_step_3c_2);
}

void trigger_step_3c() {
    playSound(G_SOUND_ID_GRUNT_3);
    g_state[G_PLAYER_LIGHT_ON] = true;
    addTimer(650, &trigger_step_3c_1);
}

t_trigger triggers[] = {
	// { &trigger_player_start_event, {0.0, 0.0, 0.0}, 0, 0, 0, 0, 0 },
	{ &trigger_step_1a0, {4.0, 0.0, -2.25}, 0, 0, 0, 0, 0 },
    { &trigger_step_1a, {-2.0, 0.0, -1.0}, 0, 0, 0, 0, 0 },
	{ &trigger_step_1b, {-7.0, 0.0, -5.0}, 0, 0, 0, 0, 0 },
	{ &trigger_step_2, {-10.0, 0.0, -6.0}, 0, 0, 0, 0, 0 },
    { &trigger_step_3a, {-10.0, 0.0, -9.0}, 0, 0, 0, 0, 0 },
    { &trigger_player_look_behind, {12.75, 0.0, 13.75}, 0, 0, 0, 0, 0 },
    { &trigger_step_3b, {15.25, 0.0, 15.5}, 0, 0, 0, 0, 0 },
	{ &trigger_step_3c, {16.25, 0.0, 16.25}, 0, 0, 0, 0, 0 },
};
int triggers_count = sizeof(triggers) / sizeof(t_trigger);

/* -------------------------------------------- INIT -------------------------------------------- */

void shutdown() {
	unloadShaderProgram();
}

void init() {

	c_init_controls();

	/*********************************************
	// YARKE YARKE YARKE!!!
	/*******************************************/
	g_timers = array();
	g_triggers = array();
	/*********************************************
	// YARKE YARKE YARKE!!!
	/*******************************************/

	#ifdef __DEBUG
		printf(KMAG "\n== Loading resources ==\n" KNRM);
	#endif
	
	/* load main resources */
	loadResourcesFromFile(resources_count, resources);
	
	#ifdef __DEBUG
		printf("\n-- Attempting to upload texture memory...\n");
	#endif

	// upload textures to GL -- should not be called here...
	loadTextures(textures_count, textures);
	
	#ifdef __DEBUG
		printf("\n-- Attempting to load shaders...\n");
	#endif

	char *vertShader;
	char *fragShader;
	GLint vlen, flen;
	
	loadShaderSource("res/shaders/default.vert", &vertShader, &vlen);
	loadShaderSource("res/shaders/default.frag", &fragShader, &flen);

	setVertexShaderSource(&vertShader, &vlen);
	setFragmentShaderSource(&fragShader, &flen);

	initShaderProgram();

	#ifdef __DEBUG
		printf("\n-- Attempting to create sound emitters...\n");
	#endif
	
	// creating sound emitters..
	load_sound_emitters(sounds_count, sounds);
	
	#ifdef __DEBUG
		printf("\n-- Attempting to load map...\n");
	#endif
	
	// Load the map from file
	loadMap("res/maps/map1.map");
	
	#ifdef __DEBUG
		printf(KMAG "\n== Initializing game ==\n" KNRM);
	#endif
	
	// load triggers
	int n;
	t_trigger trig;
	for ( n = 0; n < triggers_count; n ++ ) {
		trig = (t_trigger)triggers[n];
		addTrigger(trig.position, trig.action, trig.retrigger, trig.retrigger_interval);
	}
	
	float start_x = 0;
	float start_z = 0;
	
	/* camera physics */
	g_camera_collision_model.radius = 0.39;
	g_camera_physics_model.mass = 1.0;
	g_camera_physics_model.cur_pos = vec3(start_x, -0.3, start_z);
	g_camera_physics_model.vel = vec3(0, 0, 0);
	g_camera_physics_model.accel = vec3(0.0, -10.0, 0.0);
	
	c_camera_set_pos( g_camera, start_x, -0.2, start_z );
	c_camera_set_rot( g_camera, 0.0, 0.0, 0.0 );
	
	/* moving speeds */
	g_player_crouch_speed = 0.56;	 // units/sec
	g_player_walk_speed = 0.7;	 	// units/sec
	g_player_run_speed = 1.3;	 	// units/sec
	
	// init everything to false
	for(int i = 0; i < 256; i++) g_state[i] = false;
	
	/* controls init */
	g_mouse_sensitivity = 0.9;
	g_mouse_invert_y = false;
	
	/* stress level */
	g_player_anxiety_level = 1.0;	// always start at 1
	g_player_stress_level = 2.0;
	g_player_stress_level_min = 0.0;
	g_player_stress_level_decrease_rate = 0.1667;
	g_player_stress_level_increase_rate = 0.0;
	g_player_reaction_time = 800;	// milliseconds
	
	// init game states
	g_state[G_HAS_FLASH_LIGHT] = true;
	g_state[G_HAS_CANDLE] = true;

	g_state[G_WITH_CANDLE] = true;

    g_state[G_PLAYER_LIGHT_ON] = true;
	
	g_state[G_PHY_CLIPPING] = true;
	
	g_state[G_STATE_ACTIVE] = true;

	// REMOVE ME!!!!! ////////
	MY_SUPER_FLAG = false;
	//////////////////////////
}

/* -------------------------------------------- UPDATE -------------------------------------------- */

void updateStressResponse() {
	
	float dt = getEllapsedSeconds(TIMER4);

	static lights_were_off = false;

	if ( !g_state[G_PLAYER_LIGHT_ON] ) {
		if ( !lights_were_off ) {
			lights_were_off = true;
			g_player_stress_level += g_player_stress_level_decrease_rate;
		} else {
			// increase stress level
			g_player_stress_level += g_player_stress_level_decrease_rate*0.79*dt;
		}
	} else {
		if ( lights_were_off ) {
			lights_were_off = false;
			g_player_stress_level -= g_player_stress_level_decrease_rate;
		} else {
			// decrease stress level
			g_player_stress_level -= g_player_stress_level_decrease_rate*(1.0 - (g_player_anxiety_level/20.0))*dt;
		}
	}
	
	//printf("t:%f\te:%f\n",g_player_stress_t, exp(-g_player_stress_t));
	
	// clamp to min value
	if ( g_player_stress_level < g_player_stress_level_min )
		g_player_stress_level = g_player_stress_level_min;
		
	// clamp max value
	if ( g_player_stress_level > 10.0 )
		g_player_stress_level = 10.0;
	
	// set sounds to reflect player stress
	if ( g_player_stress_level >= 9.0 ) {	g_state[G_PLAYER_STRESS_LEVEL_10];
		
		g_walking_animation_rate = 0.0;
		
		//printf("Player stress level is at 10\n");
		
		//g_player_walk_speed = 0.0;
		soundSetState(G_SOUND_ID_MOANING, 			G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_FAST_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_SCARED_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_HEARTBEAT, 	G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_NORMAL_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_HEARTBEAT, 	G_SOUND_STOPPED);

	} else if ( g_player_stress_level >= 8.0 ) {	g_state[G_PLAYER_STRESS_LEVEL_9];

			g_walking_animation_rate = 0.08*g_player_walk_speed;
		
		//printf("Player stress level is at 9\n");
		
		//g_player_walk_speed = 0.1;
		soundSetState(G_SOUND_ID_MOANING, 			G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_BREATHING,	G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_SCARED_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_HEARTBEAT, 	G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_NORMAL_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_HEARTBEAT, 	G_SOUND_STOPPED);
		
	} else if ( g_player_stress_level >= 7.0 ) {	g_state[G_PLAYER_STRESS_LEVEL_8];

			g_walking_animation_rate = 0.17*g_player_walk_speed;
		
		//printf("Player stress level is at 8\n");
		
		//g_player_walk_speed = 0.2;
		soundSetState(G_SOUND_ID_MOANING, 			G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_SCARED_BREATHING, 	G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_NORMAL_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_HEARTBEAT, 	G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_NORMAL_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_HEARTBEAT, 	G_SOUND_STOPPED);
		
	} else if ( g_player_stress_level >= 6.0 ) {	g_state[G_PLAYER_STRESS_LEVEL_7];

			g_walking_animation_rate = 0.35*g_player_walk_speed;
		
		//printf("Player stress level is at 7\n");
		
		//g_player_walk_speed = 0.5;
		soundSetState(G_SOUND_ID_MOANING, 			G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_SCARED_BREATHING, 	G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_NORMAL_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_HEARTBEAT,	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_HEARTBEAT, 	G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_LOW_HEARTBEAT, 	G_SOUND_STOPPED);
		
	} else if ( g_player_stress_level >= 5.0 ) {	g_state[G_PLAYER_STRESS_LEVEL_6];

			g_walking_animation_rate = 0.48*g_player_walk_speed;
		
		//printf("Player stress level is at 6\n");
		
		//g_player_walk_speed = 0.6;
		soundSetState(G_SOUND_ID_MOANING, 			G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_SCARED_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_BREATHING, 	G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_LOW_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_HEARTBEAT, 	G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_LOW_HEARTBEAT, 	G_SOUND_STOPPED);
		
	} else if ( g_player_stress_level >= 4.0 ) {	g_state[G_PLAYER_STRESS_LEVEL_5];

			g_walking_animation_rate = 0.56*g_player_walk_speed;
		
		//printf("Player stress level is at 5\n");
		
		//g_player_walk_speed = 0.7;
		soundSetState(G_SOUND_ID_MOANING, 			G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_SCARED_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_BREATHING, 	G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_LOW_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_HEARTBEAT, 	G_SOUND_PLAYED);
		
	} else if ( g_player_stress_level >= 3.0 ) {	g_state[G_PLAYER_STRESS_LEVEL_4];

			g_walking_animation_rate = 0.67*g_player_walk_speed;
		
		//printf("Player stress level is at 4\n");
		
		//g_player_walk_speed = 0.8;
		soundSetState(G_SOUND_ID_MOANING, 			G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_SCARED_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_BREATHING, 	G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_LOW_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_HEARTBEAT, 	G_SOUND_STOPPED);
		
	} else if ( g_player_stress_level >= 2.0 ) {	g_state[G_PLAYER_STRESS_LEVEL_3];

			g_walking_animation_rate = 0.8*g_player_walk_speed;
		
		//printf("Player stress level is at 3\n");
		
		//g_player_walk_speed = 0.9;
		soundSetState(G_SOUND_ID_MOANING, 			G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_SCARED_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_BREATHING, 	G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_FAST_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_HEARTBEAT, 	G_SOUND_STOPPED);
		
	} else if ( g_player_stress_level >= 1.0 ) {	g_state[G_PLAYER_STRESS_LEVEL_2];

			g_walking_animation_rate = 0.9*g_player_walk_speed;
		
		//printf("Player stress level is at 2\n");
		
		//g_player_walk_speed = 1.0;
		soundSetState(G_SOUND_ID_MOANING, 			G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_SCARED_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_BREATHING, 	G_SOUND_PLAYED);
		soundSetState(G_SOUND_ID_FAST_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_HEARTBEAT, 	G_SOUND_STOPPED);
		
	} else {										g_state[G_PLAYER_STRESS_LEVEL_1];

			g_walking_animation_rate = 1.0*g_player_walk_speed;
		
		//printf("Player stress level is at 1\n");
		
		//g_player_walk_speed = 1.1;
		soundSetState(G_SOUND_ID_MOANING, 			G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_SCARED_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_BREATHING, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_FAST_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_NORMAL_HEARTBEAT, 	G_SOUND_STOPPED);
		soundSetState(G_SOUND_ID_LOW_HEARTBEAT, 	G_SOUND_STOPPED);
	}
}

void update(double dt) {

	static last_stress_level = 0.0, stress_increase = 0.0;		// for animation speeds
	
	// some animation flags
    static bool walked_step = false, waiting_to_move = true, just_got_frantic = false, just_began_croutching = false, just_began_rising = false, look_behind_ready = true, just_began_looking_behind = false;

	float player_speed = g_player_walk_speed*(1.0 - g_player_stress_level/10.0);

	/* move player with controls */
	float distance = getEllapsedSeconds(TIMER_PLAYER_MOVEMENT) * (g_state[G_PHY_CLIPPING]?player_speed:2.0);

	// c_update_controls(dt);
	if ( g_state[G_PLAYER_MOVING] && !g_state[G_PLAYER_PARALIZED] ) {

		if ( g_state[G_MOVING_FORWARD] ) {
			if ( !g_state[G_PHY_CLIPPING] ) {
				c_camera_move_forward(g_camera, distance);
			} else {
				c_camera_move(g_camera, vec3_scale(vec3_normalize(vec3(g_camera->look.x, 0, g_camera->look.z)), distance));
			}
		}
		if ( g_state[G_MOVING_BACKWARD] ) {
			if ( !g_state[G_PHY_CLIPPING] ) {
				c_camera_move_backward(g_camera, distance);
			} else {
				c_camera_move(g_camera, vec3_scale(vec3_normalize(vec3(g_camera->look.x, 0, g_camera->look.z)), -distance));
			}
		}
		if ( g_state[G_MOVING_LEFT] ) {
			c_camera_move(g_camera, vec3_scale(vec3_normalize(vec3(g_camera->right.x, 0, g_camera->right.z)), -distance));
		}
		if ( g_state[G_MOVING_RIGHT] ) {
			c_camera_move(g_camera, vec3_scale(vec3_normalize(vec3(g_camera->right.x, 0, g_camera->right.z)), distance));
		}
	}

	c_update_controls(dt);

	if ( GL_DEBUG_GEOMETRY_MODE ) return;
	
	/* update timers */
	updateTimers();
	
	/* update stress response of player */
	updateStressResponse();

	/* update player sound perception */
	sound_update_listener(&g_camera->position, &g_camera->look, &g_camera->up);
	
	if ( g_state[G_PHY_CLIPPING] ) {
		
		/* animate player movement */
		static float t = 0.0, a = 0.0, b = 0.0, c = 0.0;
		float dt = getEllapsedSeconds(TIMER_PLAYER_ANIMATION); t += dt;

		float looking_h, looking_v, s;
		
        float looking_influence = 0.5*(g_player_stress_level*g_player_stress_level/100.0)*(2.0 * sin(t) - 0.5*cos(3*t));
        float vertical_stress_influence;
        float horizontal_stress_influence;
		
        if ( g_player_stress_level > 7 ) {
            vertical_stress_influence = 0.1*(g_player_stress_level*g_player_stress_level/100.0)*sin(sin(3.4*t)-0.2*sin(7*t));
            horizontal_stress_influence = 0.4*(g_player_stress_level*g_player_stress_level/100.0)*(0.5*sin(3*t) + sin(1.5*sin(2.4*t) - 0.2*sin(18*t) + 0.1*sin(38*t)));
        }
        
		static float player_croutch_y = 0.0;
		static float player_croutch_z = 0.0;
        
        float player_croutch_y_max = -0.28; // max negative distance
        
        if ( g_player_stress_level - last_stress_level > 5 || g_player_stress_level >= 7 ) {
            g_state[G_PLAYER_CROUCHING] = true;
        } else if ( last_stress_level - g_player_stress_level > 0 && g_player_stress_level < 9 ) {
            g_state[G_PLAYER_CROUCHING] = false;
            g_state[G_PLAYER_CROUCHED] = true;
        }
		
		if ( g_state[G_PLAYER_CROUCHING] ) {
			
			/* croutching animation */
			if ( !just_began_croutching ) { 
				just_began_croutching = true;
				playSound(G_SOUND_ID_PLAYER_CROUCH);
                b = 0.0;
			}
            b += dt;
			player_croutch_y += player_croutch_y_max * (1.0 - exp(-0.0006*b*b));  // decline
            
			if ( player_croutch_y <= player_croutch_y_max + 0.001 ) {
				just_began_croutching = false;
				g_state[G_PLAYER_CROUCHING] = false;
				g_state[G_PLAYER_CROUCHED] = true;
				if ( player_croutch_y < 0.16 ) playSound(G_SOUND_ID_PLAYER_CROUCHED);
			}
			
		} else {
			
			/* getting back up animation */
			if ( g_state[G_PLAYER_CROUCHED] ) {
				if ( !just_began_rising ) {
					just_began_rising = true;
					b = 0.0;
					playSound(G_SOUND_ID_PLAYER_CROUCH);
				}
				
                b += dt;
				player_croutch_y += -player_croutch_y_max * (1.0 - exp(-0.00006*b*b));
                
				if ( player_croutch_y > -0.001 ) {
					just_began_rising = false;
					g_state[G_PLAYER_CROUCHED] = false;
				}
			}
			
		}
	
		// player look frantic animation

		if ( g_state[G_PLAYER_LOOK_FRANTIC] ) {
			if ( !just_got_frantic ) {
				just_got_frantic = true;
				a = 0.0;
			}
			s = 2.4*t; a += dt;
			looking_h = 0.7*(1.0 - a*a/36.0)*(2.0 * sin(2*t) - 0.4*sin(6*t));
			looking_v = 0.35*(1.0 - a*a/25.0)*(sin(s) - 0.5*sin(3*s));
			if ( a > 6.0 ) {
				g_state[G_PLAYER_LOOK_FRANTIC] = false;
				just_got_frantic = false;
			}
			c_camera_set_pos_offset(g_camera, 0.0, player_croutch_y, 0.0);
			c_camera_set_rot_offset(g_camera, looking_v, looking_h, 0.0);
			g_state[G_PLAYER_MOVING] = false;
		}
		
		// player look behind animation

		else if ( g_state[G_PLAYER_LOOK_BEHIND] ) {
            if ( !just_began_looking_behind ) {
                just_began_looking_behind = true;
                a = 0.0; c = rand()%10 > 5 ? -1 : 1;
            }
            a += dt; s = 1.8*(0.1 + g_player_stress_level/20.0); s = s < 0.3 ? 0.3 : s;
            looking_h = 3.5*sin(2.0 * sin(s*a) - 0.2*sin(s*3.4*a) - 0.1*sin(s*10*a));
			looking_v = 0.6*sin(0.2*sin(s*3.4*a) - 0.1*sin(s*10*a));
			if ( a*s > 2.0 ) {
				g_state[G_PLAYER_LOOK_BEHIND] = false;
                look_behind_ready = true;
                just_began_looking_behind = false;
                c_camera_set_rot(g_camera, looking_v, c*looking_h, 0.0);
                c_camera_set_rot_offset(g_camera, 0.0, 0.0, 0.0);
			}
			else {
				c_camera_set_pos_offset(g_camera, 0.0, player_croutch_y, 0.0);
				c_camera_set_rot_offset(g_camera, looking_v, c*looking_h, 0.0);
				g_state[G_PLAYER_MOVING] = false;
			}
		}
		
		else {
			// player idle animation
			c_camera_set_pos_offset(g_camera, 0.0, player_croutch_y, 0.0);
			c_camera_set_rot_offset(g_camera, vertical_stress_influence + 0.01 * (1.0 - sin(PI*t)), looking_influence + horizontal_stress_influence, 0);
		}
        
        // FIX ME: WHENEVER IDLE FOR A SEC HE SETS UP A TIMER!
        if ( false && !g_state[G_PLAYER_MOVING] ) {
            // randomly make player look behind
            if ( look_behind_ready ) {
                addTimer(1000*(30.0+rand()%70),&trigger_player_look_behind);
                look_behind_ready = false;
            }
        }
	
		if ( g_state[G_PLAYER_MOVING] && !g_state[G_PLAYER_PARALIZED] ) {
			/* walking animation */
			
			float o = 6.0 * (0.5 - cos(4*PI*t*g_walking_animation_rate)); o = o < 0 ? o : 0;
			
			c_camera_set_pos_offset(g_camera, 0.0, player_croutch_y + 0.008 * o + 0.01 * (1.0 - sin(3*PI*g_walking_animation_rate*t)), -0.003*o);
			c_camera_set_rot_offset(g_camera,
					vertical_stress_influence + 0.005 * o - 0.02 * sin(2*PI*g_walking_animation_rate*t),
					looking_influence + horizontal_stress_influence - 0.03 * sin(2*PI*g_walking_animation_rate*t) + 0.005 * (1.0 - sin(3*PI*g_walking_animation_rate*t)),
					0);
					
			if ( waiting_to_move ) {
				waiting_to_move = false;
				if ( g_state[G_PLAYER_CROUCHED] ) {
					playSound(G_SOUND_ID_PLAYER_DRAG);
				} else {
					playSound(G_SOUND_ID_PLAYER_WALK);
				}
			}
		
            if ( g_state[G_PLAYER_CROUCHED] ) {
                if ( o < -0.25 && !walked_step )
                    playSound(G_SOUND_ID_PLAYER_DRAG);
            } else if ( o < -0.45 && !walked_step ) {
				walked_step = true;
                playSound(G_SOUND_ID_PLAYER_WALK);
				if ( g_state[G_MOVING_LEFT] || g_state[G_MOVING_RIGHT] )
					playSound(G_SOUND_ID_PLAYER_CROUCH);
			}
            
            if ( o > -0.095 ) {
				walked_step = false;
			}
		
		} else {
			walked_step = false;
			waiting_to_move = true;
		}
		
		last_stress_level = g_player_stress_level;
	}
	
	if ( g_state[G_PHY_CLIPPING] ) {
		/* do some basic physics */
		if ( !g_state[G_DEBUG_PHYSICS] ) {
			vcpy(&g_camera_physics_model.cur_pos,&g_camera->position);
		
			/* NO PHYSICS YET, CHECK BACK SOON! */
		
			/* check collisions */
			vcpy(&g_camera_collision_model.center,&g_camera_physics_model.cur_pos);
			bool collided = detectCollision(&g_camera_collision_model, g_collisions_count, g_collisions );
			vcpy(&g_camera_physics_model.cur_pos,&g_camera_collision_model.center);
		
			// update camera position
			vcpy(&g_camera->position,&g_camera_physics_model.cur_pos);
		}

		/* check "collision" with triggers */
		int i;
		h_trigger trigger;
		if ( g_triggers->count > 0 ) {
			array_set_internal_position(g_triggers, 0);
			for ( i = 0; i < g_triggers->count; i ++ ) {
				trigger = array_next(g_triggers);
				if ( norm(vec3_sub(g_camera->position, trigger->position)) < 0.7 ) {
					fireTrigger(trigger);
				}
			}
		}
	}

	display();
}