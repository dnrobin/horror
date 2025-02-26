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
} t_trigger, *h_trigger;

h_array g_triggers;

void addTrigger(const vec3_t position, const void(*action)(), const char retrigger, const float retrigger_interval);
void fireTrigger(h_trigger trig);

#endif