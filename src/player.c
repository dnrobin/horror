#include "shared.h"
#include "player.h"

#include "gamedefs.h"
#include "timing.h"
#include "game.h"


void update_stress_response() {
	
	float dt = getEllapsedSeconds(TIMER4);

	static bool lights_were_off = false;

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
	
	// clamp to min value
	if ( g_player_stress_level < g_player_stress_level_min ) {
		g_player_stress_level = g_player_stress_level_min;
	}
		
	// clamp max value
	if ( g_player_stress_level > 10.0 ) {
		g_player_stress_level = 10.0;
	}

	// adjust player fov based on stress
	g_player_fov = 70.0 * m_exp(-(g_player_stress_level/16.0)*(g_player_stress_level/16.0));
	
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
