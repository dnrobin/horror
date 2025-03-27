#include "shared.h"
#include "game.h"

#include "gamedefs.h"
#include "timing.h"
#include "trigger.h"
#include "controls.h"
#include "player.h"
#include "graphics.h"
#include "sound.h"
#include "render.h"
#include "shader.h"
#include "map.h"

// private game state
static camera_t game_camera;

// set global pointers
camera_t *g_camera = &game_camera;

#include "map_definitions.inc"

typedef enum {
	PLAYER_JUST_SCARED,
	PLAYER_REACTING_TO_SCARE,
	PLAYER_
} player_state_t;

/* -------------------------------------------- INIT -------------------------------------------- */

static void unload_map()
{
	for (int i = 0; i < map_shaders_count; ++i) {
		// r_delete_shader(&map_shaders[i]);
	}
}

static void load_map()
{
	g_timers = array();
	g_triggers = array();

	#ifdef __DEBUG
		printf(KMAG "\n== Loading assets ==\n" KNRM);
	#endif
	
	for (int i = 0; i < map_assets_count; ++i) {
		f_load_map_asset_file(&map_assets[i]);
	}

	#ifdef __DEBUG
		printf("\n-- Creating shaders...\n");
	#endif

	for (int i = 0; i < map_shaders_count; ++i) {
		f_load_map_shader_file(&map_shaders[i]);
	}

	// TEMP!!!!!!!!!!!!!!!!!!!!!!
	g_main_shader_program = ((shader_t*)get_asset(map_shaders[0].asset_id)->obj)->gl_handle;
	// TEMP!!!!!!!!!!!!!!!!!!!!!!
	
	#ifdef __DEBUG
		printf("\n-- Creating sound emitters...\n");
	#endif
	
	// create sound emitters from loaded audio buffers
	for (int i = 0; i < map_sound_emitters_count; ++i) {
		s_create_sound_emitter(&map_sound_emitters[i]);
	}

	#ifdef __DEBUG
		printf("\n-- Creating triggers...\n");
	#endif

	for (int n = 0; n < triggers_count; n ++ ) {
		t_trigger *trig = &triggers[n];
		addTrigger(trig->position, trig->action, trig->retrigger, trig->retrigger_interval);
	}
	
	#ifdef __DEBUG
		printf("\n-- Creating geometry...\n");
	#endif
	
	// Load the map from file
	#ifdef USE_MODERN_PIPELINE
		f_load_map_json("maps/map0.json");
	#else
		map_load("maps/map1.map");
	#endif	
}

void game_code_init()
{
	g_state[G_DEBUG_CAMERA] = true;

	load_map();

	// _debug_print_asset_list();
	
	#ifdef __DEBUG
		printf(KMAG "\n== Initializing game ==\n" KNRM);
	#endif

	c_init_controls();
	
	float start_x = 0;
	float start_z = 0;
	
	/* camera physics */
	g_camera->yfov = 70;
	g_camera->znear = 0.1;
	g_camera->zfar = 100;
	// g_camera->yfov	// set at update to match player model
	cam_reset_orientation(g_camera);
	g_camera_collision_model.radius = 0.39;
	g_camera_physics_model.mass = 1.0;
	vec3(g_camera_physics_model.cur_pos, start_x, -0.3, start_z);
	vec3(g_camera_physics_model.vel, 0, 0, 0);
	vec3(g_camera_physics_model.accel, 0.0, -10.0, 0.0);
	
	// g_camera->rotation_offset = (vec3_t){ 1.3, -.1, 0 };
	cam_move_to(g_camera, (vec3_t){start_x, -0.2, start_z});
	
	/* moving speeds */
	g_player_crouch_speed = 0.56;	 // units/sec
	g_player_walk_speed = 0.7;	 	// units/sec
	g_player_run_speed = 1.3;	 	// units/sec
	g_player_fov = 70.0;
	
	// init everything to false
	for(int i = 0; i < 256; i++) g_state[i] = false;
	
	/* controls init */
	g_mouse_sensitivity = 1.5;
	g_mouse_invert_y = true;
	
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
}

void game_code_shutdown()
{
	#ifdef __DEBUG
		printf(KMAG "\n== Shutting down ==\n" KNRM);
	#endif

	unload_map();
}

/* -------------------------------------------- UPDATE -------------------------------------------- */

static void move_player()
{
	float player_speed = g_player_walk_speed*(1.0 - g_player_stress_level/10.0);
	float distance = getEllapsedSeconds(TIMER_PLAYER_MOVEMENT) * (g_state[G_PHY_CLIPPING]?player_speed:2.0);

	if ( g_state[G_PLAYER_MOVING] && !g_state[G_PLAYER_PARALIZED] ) {

		vec2_t d = {0, 0};

		if (g_state[G_MOVING_FORWARD]) {
			d[1] += +1;
		}
		if (g_state[G_MOVING_LEFT]) {
			d[0] += -1;
		}
		if (g_state[G_MOVING_BACKWARD]) {
			d[1] += -1;
		}
		if (g_state[G_MOVING_RIGHT]) {
			d[0] += +1;
		}

		vec2_trim(d, d, distance);

		cam_move_right(g_camera,   d[0]);
		cam_move_forward(g_camera, d[1]);

		// if ( g_state[G_MOVING_FORWARD] ) {
		// 	cam_move_forward(g_camera, distance);
		// 	// if ( !g_state[G_PHY_CLIPPING] ) {
		// 	// 	cam_move_forward(g_camera, distance);
		// 	// } else {
		// 	// 	vec3_t v = { g_camera->look[0], 0, g_camera->look[2] };
		// 	// 	vec3_normalize(v, v);
		// 	// 	vec3_scale(v, v, distance);
		// 	// 	cam_move_by(g_camera, v);
		// 	// }
		// }
		// if ( g_state[G_MOVING_BACKWARD] ) {
		// 	cam_move_backward(g_camera, distance);
		// 	// if ( !g_state[G_PHY_CLIPPING] ) {
		// 	// 	cam_move_backward(g_camera, distance);
		// 	// } else {
		// 	// 	vec3_t v = { g_camera->look[0], 0, g_camera->look[2] };
		// 	// 	vec3_normalize(v, v);
		// 	// 	vec3_scale(v, v, -distance);
		// 	// 	cam_move_by(g_camera, v);
		// 	// }
		// }
		// if ( g_state[G_MOVING_LEFT] ) {
		// 	cam_move_left(g_camera, distance);
		// }
		// if ( g_state[G_MOVING_RIGHT] ) {
		// 	cam_move_right(g_camera, distance);
		// }
	}
}

/**
 * Player animation state machine:
 * - idle is default, but stress-level dependent
 * - 
 */

void animate_player()
{
	if (GAME_SKIP_ANIMATIONS) {
		return;
	}

	static float last_stress_level = 0.0, stress_increase = 0.0;		// for animation speeds

    static bool walked_step = false;
	static bool waiting_to_move = true;
	static bool just_got_frantic = false;
	static bool just_began_croutching = false;
	static bool just_began_rising = false;
	static bool look_behind_ready = true;
	static bool just_began_looking_behind = false;

	static float t = 0.0, a = 0.0, b = 0.0, c = 0.0;
	float dt = getEllapsedSeconds(TIMER_PLAYER_ANIMATION); t += dt;

	float looking_h, looking_v, s;

	float looking_influence = 0.5*(g_player_stress_level*g_player_stress_level/100.0)*(2.0 * m_sin(t) - 0.5*m_cos(3*t));
	float vertical_stress_influence;
	float horizontal_stress_influence;

	if ( g_player_stress_level > 7 ) {
		vertical_stress_influence = 0.1*(g_player_stress_level*g_player_stress_level/100.0)*m_sin(m_sin(3.4*t)-0.2*m_sin(7*t));
		horizontal_stress_influence = 0.4*(g_player_stress_level*g_player_stress_level/100.0)*(0.5*m_sin(3*t) + m_sin(1.5*m_sin(2.4*t) - 0.2*m_sin(18*t) + 0.1*m_sin(38*t)));
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
		player_croutch_y += player_croutch_y_max * (1.0 - m_exp(-0.0006*b*b));  // decline
		
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
			player_croutch_y += -player_croutch_y_max * (1.0 - m_exp(-0.00006*b*b));
			
			if ( player_croutch_y > -0.001 ) {
				just_began_rising = false;
				g_state[G_PLAYER_CROUCHED] = false;
			}
		}
	}

	/* player look frantic animation */
	if ( g_state[G_PLAYER_LOOK_FRANTIC] ) {
		if ( !just_got_frantic ) {
			just_got_frantic = true;
			a = 0.0;
		}
		s = 2.4*t; a += dt;
		looking_h = 0.7*(1.0 - a*a/36.0)*(2.0 * m_sin(2*t) - 0.4*m_sin(6*t));
		looking_v = 0.35*(1.0 - a*a/25.0)*(m_sin(s) - 0.5*m_sin(3*s));
		if ( a > 6.0 ) {
			g_state[G_PLAYER_LOOK_FRANTIC] = false;
			just_got_frantic = false;
		}
		// c_camera_set_pos_offset(g_camera, 0.0, player_croutch_y, 0.0);
		// c_camera_set_rot_offset(g_camera, looking_v, looking_h, 0.0);
		g_state[G_PLAYER_MOVING] = false;
	}

	/* player look behind animation */
	else if ( g_state[G_PLAYER_LOOK_BEHIND] ) {
		if ( !just_began_looking_behind ) {
			just_began_looking_behind = true;
			a = 0.0; c = m_rand()*10 > 5 ? -1 : 1;
		}
		a += dt; s = 1.8*(0.1 + g_player_stress_level/20.0); s = s < 0.3 ? 0.3 : s;
		looking_h = 3.5*m_sin(2.0 * m_sin(s*a) - 0.2*m_sin(s*3.4*a) - 0.1*m_sin(s*10*a));
		looking_v = 0.6*m_sin(0.2*m_sin(s*3.4*a) - 0.1*m_sin(s*10*a));
		if ( a*s > 2.0 ) {
			g_state[G_PLAYER_LOOK_BEHIND] = false;
			look_behind_ready = true;
			just_began_looking_behind = false;
			cam_set_angles(g_camera, looking_v, c*looking_h, 0.0);
			// c_camera_set_rot_offset(g_camera, 0.0, 0.0, 0.0);
		}
		else {
			// c_camera_set_pos_offset(g_camera, 0.0, player_croutch_y, 0.0);
			// c_camera_set_rot_offset(g_camera, looking_v, c*looking_h, 0.0);
			g_state[G_PLAYER_MOVING] = false;
		}
	}

	else {
		
		/* player idle animation */
		// c_camera_set_pos_offset(g_camera, 0.0, player_croutch_y, 0.0);
		// c_camera_set_rot_offset(g_camera, vertical_stress_influence + 0.01 * (1.0 - m_sin(M_PI*t)), looking_influence + horizontal_stress_influence, 0);
	}

	// FIX ME: WHENEVER IDLE FOR A SEC HE SETS UP A TIMER!
	if ( false && !g_state[G_PLAYER_MOVING] ) {
		
		/* andomly make player look behind */
		if ( look_behind_ready ) {
			add_timer(1000*(30.0+m_rand()*70),&trigger_player_look_behind);
			look_behind_ready = false;
		}
	}

	if ( g_state[G_PLAYER_MOVING] && !g_state[G_PLAYER_PARALIZED] ) {
		
		/* walking animation */
		float o = 6.0 * (0.5 - m_cos(4*M_PI*t*g_walking_animation_rate)); o = o < 0 ? o : 0;
		
		// c_camera_set_pos_offset(g_camera, 0.0, player_croutch_y + 0.008 * o + 0.01 * (1.0 - m_sin(3*M_PI*g_walking_animation_rate*t)), -0.003*o);
		// c_camera_set_rot_offset(g_camera,
		// 		vertical_stress_influence + 0.005 * o - 0.02 * m_sin(2*M_PI*g_walking_animation_rate*t),
		// 		looking_influence + horizontal_stress_influence - 0.03 * m_sin(2*M_PI*g_walking_animation_rate*t) + 0.005 * (1.0 - m_sin(3*M_PI*g_walking_animation_rate*t)),
		// 		0);
				
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
	}
	
	else {
		walked_step = false;
		waiting_to_move = true;
	}

	last_stress_level = g_player_stress_level;
}

void game_code_update()
{
	c_update_controls();

	move_player();

	// stop here if debugging
	if (!GL_DEBUG_GEOMETRY_MODE && !GAME_SKIP_COLLISIONS) {
		
		update_timers();
		
		update_stress_response();

		// TODO: move to more appropriate place
		g_camera->yfov = g_player_fov;

		s_sound_update_listener(&g_camera->eye, &g_camera->look, &g_camera->up);

		if ( g_state[G_PHY_CLIPPING] )
		{
			// only animate if in player state
			animate_player();

			/* do some basic physics */
			if ( !g_state[G_DEBUG_PHYSICS] )
			{
				vec3_copy(g_camera_physics_model.cur_pos, g_camera->eye);
			
				/* NO PHYSICS YET, CHECK BACK SOON! */
			
				/* check collisions */
				vec3_copy(g_camera_collision_model.center, g_camera_physics_model.cur_pos);
				bool collided = check_collisions(&g_camera_collision_model, g_collisions_count, g_collisions );
				vec3_copy(g_camera_physics_model.cur_pos, g_camera_collision_model.center);
			
				// update camera position
				vec3_copy(g_camera->eye, g_camera_physics_model.cur_pos);
			}

			/* check "collision" with triggers */
			if (!GAME_SKIP_TRIGGERS) {
				t_trigger* trigger;
				if ( g_triggers->count > 0 )
				{
					array_set_internal_position(g_triggers, 0);
					for (int i = 0; i < g_triggers->count; i ++ ) {
						trigger = array_next(g_triggers);
						vec3_t v;
						vec3_sub(v, g_camera->eye, trigger->position);
						if ( vec3_length(v) < 0.7 ) {
							fireTrigger(trigger);
						}
					}
				}
			}
		}
	}

	display();
}