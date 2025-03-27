#ifndef __MAZE_GAME_TRIGGER_H__
#define __MAZE_GAME_TRIGGER_H__

#include "mem.h"

typedef struct trigger {
	void (*action)();
	vec3_t position;
	char retrigger;
	float retrigger_interval;
	float retrigger_start_time;
	float retrigger_ellapsed;
	char triggered;
} t_trigger;

h_array g_triggers;

void addTrigger(const vec3_t position, void(*action)(), const char retrigger, const float retrigger_interval);
void fireTrigger(t_trigger *trig);

#endif