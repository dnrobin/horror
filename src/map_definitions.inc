#include "shared.h"

#include "res.h"
#include "game.h"
#include "gamedefs.h"
#include "trigger.h"
#include "timing.h"
#include "graphics.h"

#include "glad.h"

resource_descriptor_t resource_descriptors[] = {
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
const int resource_descriptors_count = sizeof(resource_descriptors) / sizeof(resource_descriptor_t);

texture_resource_descriptor_t texture_resource_descriptors[] = {
	{ 987,  0, 803, 786, 4, GL_BGRA, GL_UNSIGNED_BYTE, GL_LINEAR },
	{ 988,  0, 720, 464, 4, GL_BGRA, GL_UNSIGNED_BYTE, GL_LINEAR },
	{ 989,  0, 803, 786, 4, GL_BGRA, GL_UNSIGNED_BYTE, GL_LINEAR },
	{ 1011, 0, 867, 650, 4, GL_BGRA, GL_UNSIGNED_BYTE, GL_LINEAR },
    { 1014, 0, 867, 650, 4, GL_BGRA, GL_UNSIGNED_BYTE, GL_LINEAR },
    { 1015, 0, 867, 650, 3, GL_RGB,  GL_UNSIGNED_BYTE, GL_LINEAR },
    { 1018, 0, 0, 0, 4, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR },
};
const int texture_resource_descriptors_count = sizeof(texture_resource_descriptors) / sizeof(texture_resource_descriptor_t);

shader_descriptor_t shader_descriptors[] = {
	{ 100, 0, "res/shaders/default.vert", "res/shaders/default.frag"}
};
const int shader_descriptors_count = sizeof(shader_descriptors) / sizeof(shader_descriptor_t);

t_sound_resource_descriptor sound_descriptors[] = {
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
const int sound_descriptors_count = sizeof(sound_descriptors) / sizeof(t_sound_resource_descriptor);

// ********************************************************************
// END MAP RESOURCE DEFINITIONS
// ********************************************************************

// walking animation
float g_player_walk_anim_frames_count = 100;
float g_player_walk_anim_frames[100] = {0, 0, 0, 0, 0, 0, -0.28661436, -0.903256429, -1.476376847, -2.000888557, -2.472135955, -2.885936216, -3.23861642, -3.527046152, -3.748665289, -3.901506725, -3.984213827, -3.996052483, -3.936917611, -3.807334096, -3.60845213, -3.342037005, -3.01045344, -2.616644594, -2.164105942, -1.656854249, -1.099391918, -0.496667023, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.496667023, -1.099391918, -1.656854249, -2.164105942, -2.616644594, -3.01045344, -3.342037005, -3.60845213, -3.807334096, -3.936917611, -3.996052483, -3.984213827, -3.901506725, -3.748665289, -3.527046152, -3.23861642, -2.885936216, -2.472135955, -2.000888557, -1.476376847, -0.903256429, -0.28661436, 0, 0, 0, 0, 0};

/* trigger callbacks */

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

const int triggers_count = sizeof(triggers) / sizeof(t_trigger);