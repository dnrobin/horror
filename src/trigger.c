#include "shared.h"
#include "trigger.h"
#include "timing.h"

#include <stdlib.h>

void addTrigger(const vec3_t position, void(*action)(), const char retrigger, const float retrigger_interval)
{
	t_trigger* trig;
	
	if( (trig = (t_trigger*)malloc(sizeof(t_trigger))) == NULL ) {
		printf("Error while trying to create new trigger\n");
		return;
	}

	trig->retrigger = retrigger;
	trig->retrigger_interval = retrigger_interval;
	trig->retrigger_start_time = getSeconds();
	trig->retrigger_ellapsed = 0;
	trig->triggered = 0;
	
	trig->action = action;
	trig->position = position;
	
	push_array(g_triggers, trig);
}

void fireTrigger(t_trigger* trig)
{
	if ( trig->triggered == 0 ) {
		trig->triggered = 1;
		trig->action();
		//printf("Fired trigger...\n");
	}

	else if ( trig->retrigger != 0 ) {
		trig->retrigger_ellapsed = getSeconds();
		if ( trig->retrigger_ellapsed - trig->retrigger_start_time > trig->retrigger_interval ) {
			trig->triggered = 0;
			fireTrigger(trig);
		}
	}
}
