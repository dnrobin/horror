#include "shared.h"
#include "timing.h"

#include <stdlib.h>
#include <sys/time.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

struct timeval g_time_keepers[16];

void add_timer(const unsigned int interval, void(*callback)()) {

	h_timer timer;
	
	if( (timer = (h_timer)malloc(sizeof(t_timer))) == NULL ) {
		printf("Error while trying to create new timer!\n");
		return;
	}
	
	timer->interval = interval;
	timer->callback = callback;
	timer->start_time = getMillisec();
	timer->time = 0;
	timer->state = 1; 	// active
	
	printf("New timer added with start interval %d\n",timer->interval);
	
	push_array(g_timers, timer);
}

void update_timers() {

	int i;
	h_timer timer;
	
	if ( g_timers->count == 0 )
		return;
	
	array_set_internal_position(g_timers, 0);
	for ( i = 0; i < g_timers->count; i ++ ) {
		
		timer = array_next(g_timers);
		
		if ( !timer->state ) continue;
		
		timer->time = getMillisec() - timer->start_time;
		
		if ( timer->time > timer->interval ) {
			timer->callback();
			timer->state = 0;
		}
	}
}

unsigned int getMillisec() {
	// struct timeval t;
	// gettimeofday(&t, NULL);
	// return (unsigned int)( t.tv_sec * 1000.0 + floor(t.tv_usec / 1000.0) );

	return (unsigned int)(glfwGetTime() * 1000);
}

float getSeconds() {
	// struct timeval t;
	// gettimeofday(&t, NULL);
	// return (float)( t.tv_usec + 1000000.0 * t.tv_sec ) / 1000000.0;

	return (unsigned int)(glfwGetTime());
}

float getEllapsedSeconds(const int timer) {
	
	struct timeval t;
	
	if( g_time_keepers[timer].tv_usec == 0 ) {
		gettimeofday(&g_time_keepers[timer], NULL);
	}
	
	gettimeofday(&t, NULL);
	
	float delta = (float)( (t.tv_usec + 1000000 * t.tv_sec) - (g_time_keepers[timer].tv_usec + 1000000 * g_time_keepers[timer].tv_sec) ) / 1000000;
	
	g_time_keepers[timer] = t;
	
	return delta;
}