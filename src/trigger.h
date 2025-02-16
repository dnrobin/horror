#ifndef __TRIGGER_H__
#define __TRIGGER_H__

#include "math.h"
#include "mem.h"

typedef struct trigger {
	void (*action)();
	t_vec3 position;
	char retrigger;
	float retrigger_interval;
	float retrigger_start_time;
	float retrigger_ellapsed;
	char triggered;
} t_trigger, *h_trigger;

h_array g_triggers;

void addTrigger(const t_vec3 position, const void(*action)(), const char retrigger, const float retrigger_interval);
void fireTrigger(h_trigger trig);

#endif