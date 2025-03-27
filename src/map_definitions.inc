#include "shared.h"
#include "res.h"

#include "timing.h"
#include "trigger.h"
#include "texture.h"
#include "sound.h"
#include "game.h"
#include "gamedefs.h"

#include "glad.h"

#define MAP_ASSET_DEFAULT_SHADER 100

static map_asset_descriptor_t map_assets[] = {

	// { 50, 	ASSET_IMAGE, "textures/dusty-cobble/dusty-cobble_albedo.png" },
	// { 51, 	ASSET_IMAGE, "textures/dusty-cobble/dusty-cobble_ao.png" },
	// { 52, 	ASSET_IMAGE, "textures/dusty-cobble/dusty-cobble_roughness.png" },
	// { 53, 	ASSET_IMAGE, "textures/dusty-cobble/dusty-cobble_normal-ogl.png" },

	// { 60, 	ASSET_IMAGE, "textures/dutch_brickwall/dutch_brickwall_albedo.jpg" },
	// { 61, 	ASSET_IMAGE, "textures/dutch_brickwall/dutch_brickwall_normal.png" },
	// { 62, 	ASSET_IMAGE, "textures/dutch_brickwall/dutch_brickwall_roughness.jpg" },
	// { 63, 	ASSET_IMAGE, "textures/dutch_brickwall/dutch_brickwall_metallic.jpg" },

	// { 70, 	ASSET_IMAGE, "textures/sloppy-mortar-stone-wall/sloppy-mortar-stone-wall_albedo.png" },
	// { 71, 	ASSET_IMAGE, "textures/sloppy-mortar-stone-wall/sloppy-mortar-stone-wall_normal-ogl.png" },
	// { 72, 	ASSET_IMAGE, "textures/sloppy-mortar-stone-wall/sloppy-mortar-stone-wall_roughness.png" },
	// { 73, 	ASSET_IMAGE, "textures/sloppy-mortar-stone-wall/sloppy-mortar-stone-wall_metallic.png" },
	// { 74, 	ASSET_IMAGE, "textures/sloppy-mortar-stone-wall/sloppy-mortar-stone-wall_height.png" },
	// { 75, 	ASSET_IMAGE, "textures/sloppy-mortar-stone-wall/sloppy-mortar-stone-wall_ao.png" },

	{ 987, 	ASSET_IMAGE, "textures/walltex_06_diffuse.bmp" },
	{ 989, 	ASSET_IMAGE, "textures/walltex_06_diffuse2.bmp" },
	{ 988, 	ASSET_IMAGE, "textures/floortex_5.bmp" },
	{ 990, 	ASSET_SOUND, "sounds/background_6.wav" },
	{ 991, 	ASSET_SOUND, "sounds/background_3.wav" },
	{ 992, 	ASSET_SOUND, "sounds/music_1.wav" },
	{ 993, 	ASSET_SOUND, "sounds/walk_4.wav" },
	{ 994, 	ASSET_SOUND, "sounds/heart_1.wav" },
	{ 995, 	ASSET_SOUND, "sounds/heart_2.wav" },
	{ 996, 	ASSET_SOUND, "sounds/heart_3.wav" },
	{ 997, 	ASSET_SOUND, "sounds/breathe_1.wav" },
	{ 998, 	ASSET_SOUND, "sounds/breathe_2.wav" },
	{ 999, 	ASSET_SOUND, "sounds/breathe_3.wav" },
	{ 1000, ASSET_SOUND, "sounds/breathe_4.wav" },
	{ 1001, ASSET_SOUND, "sounds/moan_1.wav" },
	{ 1002, ASSET_SOUND, "sounds/footsteps_1.wav" },
	{ 1003, ASSET_SOUND, "sounds/grunt_behind_1.wav" },
	{ 1004, ASSET_SOUND, "sounds/whisper_1.wav" },
	{ 1005, ASSET_SOUND, "sounds/fx_7.wav" },
	{ 1006, ASSET_SOUND, "sounds/fx_8.wav" },
	{ 1007, ASSET_SOUND, "sounds/dark_sound_1.wav" },
	{ 1008, ASSET_SOUND, "sounds/fx_beat_1.wav" },
	{ 1009, ASSET_SOUND, "sounds/intro_naration.wav" },
	{ 1010, ASSET_SOUND, "sounds/background_2.wav" },
	{ 1011, ASSET_IMAGE, "textures/vision_1.bmp" },
    { 1012, ASSET_SOUND, "sounds/grunt_far_1.wav" },
    { 1013, ASSET_SOUND, "sounds/grunt_close_1.wav" },
    { 1014, ASSET_IMAGE, "textures/mask2.bmp" },
    { 1015, ASSET_IMAGE, "textures/noise_1.bmp" },
    { 1016, ASSET_SOUND, "sounds/flash_light_1.wav" },
    { 1017, ASSET_SOUND, "sounds/background_7.wav" },
    { 1018, ASSET_IMAGE, "textures/fog.bmp" }
};
static const int map_assets_count = sizeof(map_assets) / sizeof(map_asset_descriptor_t);

static map_shader_descriptor_t map_shaders[] = {
	{ MAP_ASSET_DEFAULT_SHADER, "shaders/default.vert", "shaders/default.frag" }
};
static const int map_shaders_count = sizeof(map_shaders) / sizeof(map_shader_descriptor_t);

// ********************************************************************
// END MAP RESOURCE DEFINITIONS
// ********************************************************************



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// World/scene defs
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static sound_emitter_descriptor_t map_sound_emitters[] = {
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
    { 1016, 0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 0.15, 1.0, 1.0, 0, 0, 1, 1, 0, 0, 1, 0, 0 },
    { 1017, SOUND_EMIT_GLOBAL | SOUND_EMIT_LOOPED | SOUND_EMIT_AUTOPLAY, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.1, 1.0, 1.0, 0, 0, 1.0, 1.0, 0, 0, 0, 0, 0 },
};
static const int map_sound_emitters_count = sizeof(map_sound_emitters) / sizeof(sound_emitter_descriptor_t);

static void setStressLevel(const float level) {
	// impact on anxiety
	g_player_anxiety_level += (level - g_player_stress_level)/5.0;
	
	// set the new minimum
	g_player_stress_level_min += g_player_anxiety_level*g_player_stress_level/120.0;
	
	// update stress level
	g_player_stress_level = level > 10.0 ? 10.0 : ( level < 0 ? 0 : level);
	
	printf("player stress:%0.1f, axiety:%0.1f and lower bound at %0.1f\n",g_player_stress_level,g_player_anxiety_level,g_player_stress_level_min);
}

static void trigger_player_scared_level10() {
	setStressLevel(10.0);
}

static void trigger_player_scared_level9() {
	setStressLevel(9.0);
}

static void trigger_player_scared_level8() {
	setStressLevel(8.0);
}

static void trigger_player_scared_level7() {
	setStressLevel(7.0);
}

static void trigger_player_scared_level6() {
	setStressLevel(6.0);
}

static void trigger_player_scared_level5() {
	setStressLevel(5.0);
}

static void trigger_player_scared_level4() {
	setStressLevel(4.0);
}

static void trigger_player_scared_level3() {
	setStressLevel(3.0);
}

static void trigger_player_look_behind() {
	g_state[G_PLAYER_LOOK_BEHIND] = true;
}

static void trigger_player_frantic() {
	g_state[G_PLAYER_LOOK_FRANTIC] = true;
}

static void trigger_whisper() {
	playSound(G_SOUND_ID_WHISPER);
	add_timer(850, &trigger_player_look_behind);
	add_timer(g_player_reaction_time, &trigger_player_scared_level6);
}

static void trigger_footsteps() {
	playSound(G_SOUND_ID_FOOTSTEPS);
	add_timer(850, &trigger_player_frantic);
	add_timer(g_player_reaction_time, &trigger_player_scared_level8);
}

static void trigger_grunt() {
	playSound(G_SOUND_ID_GROANING);
	add_timer(850, &trigger_player_frantic);
	add_timer(g_player_reaction_time, &trigger_player_scared_level7);
}

static void trigger_music() {
	playSound(G_SOUND_ID_DISTURBING_MUSIC);
	add_timer(1200, &trigger_player_scared_level7);
}

static void trigger_near_deathzone() {
	playSound(G_SOUND_ID_SHEMALE);
	add_timer(5400, &trigger_player_scared_level6);
}

static void trigger_enter_deathzone() {
	g_state[G_DEATH_ZONE] = true;
	add_timer(2500, &trigger_player_scared_level10);
}

static void trigger_flashlight() {
	g_state[G_HAS_FLASH_LIGHT] = true;
	g_state[G_WITH_FLASH_LIGHT] = true;
	g_state[G_PLAYER_LIGHT_ON] = true;
	playSound(G_SOUND_ID_PLAYER_CROUCH);		// I know.. not the appropriate sound
}

static void trigger_party_light() {
	g_state[G_PARTY_LIGHT_ON] = true;
	add_timer(g_player_reaction_time, &trigger_player_scared_level10);
}

static void trigger_player_start_event_1() {
	g_state[G_PLAYER_PARALIZED] = false;
	g_state[G_PLAYER_LIGHT_ON] = true;
}

static void trigger_player_start_event_2() {
	playSound(G_SOUND_ID_INTRO_NARRATION);
}

static void trigger_player_start_event() {
	g_state[G_PLAYER_PARALIZED] = true;
	g_state[G_PLAYER_LIGHT_ON] = false;
	g_state[G_PLAYER_CROUCHING] = true;
	trigger_player_scared_level6();
	add_timer(3600, &trigger_player_start_event_2);
	add_timer(16000, &trigger_player_start_event_1);
}

static void trigger_step_1a0() {
	playSound(G_SOUND_ID_FOOTSTEPS);
	add_timer(650, &trigger_player_look_behind);
	add_timer(300, &trigger_player_scared_level5);
}

static void trigger_step_1a() {
    playSound(G_SOUND_ID_GRUNT_1);
    g_state[G_PLAYER_LIGHT_ON] = true;
    add_timer(450, &trigger_player_look_behind);
}

static void trigger_step_1b() {
	playSound(G_SOUND_ID_DARK_SOUND_1);
	add_timer(300, &trigger_player_scared_level4);
}

static void trigger_step_2() {
	playSound(G_SOUND_ID_DARK_SOUND_2);
	add_timer(1000, &trigger_player_scared_level5);
}

static void trigger_step_3a() {
    playSound(G_SOUND_ID_GRUNT_1);
    add_timer(300, &trigger_player_scared_level5);
}

static void trigger_step_3b_1() {
	add_timer(300, &trigger_player_scared_level6);
	g_state[G_PLAYER_PARALIZED] = false;
}

static void trigger_step_3b() {
    playSound(G_SOUND_ID_GRUNT_2);
    //g_state[G_PLAYER_PARALIZED] = true;
    //add_timer(300, &trigger_player_look_behind);
    add_timer(650, &trigger_step_3b_1);
}

static void trigger_step_3c_2() {
	g_state[G_PLAYER_PARALIZED] = false;
}

static void trigger_step_3c_1() {
	g_state[G_PLAYER_PARALIZED] = true;
	add_timer(650, &trigger_player_look_behind);
	add_timer(800, &trigger_player_scared_level8);
	add_timer(3000, &trigger_step_3c_2);
}

static void trigger_step_3c() {
    playSound(G_SOUND_ID_GRUNT_3);
    g_state[G_PLAYER_LIGHT_ON] = true;
    add_timer(650, &trigger_step_3c_1);
}

static t_trigger triggers[] = {
	{ &trigger_player_start_event, {0.0, 0.0, 0.0}, 0, 0, 0, 0, 0 },
	{ &trigger_step_1a0, {4.0, 0.0, -2.25}, 0, 0, 0, 0, 0 },
    { &trigger_step_1a, {-2.0, 0.0, -1.0}, 0, 0, 0, 0, 0 },
	{ &trigger_step_1b, {-7.0, 0.0, -5.0}, 0, 0, 0, 0, 0 },
	{ &trigger_step_2, {-10.0, 0.0, -6.0}, 0, 0, 0, 0, 0 },
    { &trigger_step_3a, {-10.0, 0.0, -9.0}, 0, 0, 0, 0, 0 },
    { &trigger_player_look_behind, {12.75, 0.0, 13.75}, 0, 0, 0, 0, 0 },
    { &trigger_step_3b, {15.25, 0.0, 15.5}, 0, 0, 0, 0, 0 },
	{ &trigger_step_3c, {16.25, 0.0, 16.25}, 0, 0, 0, 0, 0 },
};
static const int triggers_count = sizeof(triggers) / sizeof(t_trigger);