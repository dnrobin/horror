#ifndef MAZ_TIMING_H
#define MAZ_TIMING_H

#include "mem.h"

typedef struct timer {
	unsigned int interval;
	unsigned int start_time;
	unsigned int time;
	char state;
	void (*callback)();
} t_timer, *h_timer;

h_array g_timers;

// enum for timers
enum { 
	TIMER_PLAYER_MOVEMENT, 
	TIMER_PHYSICS_TIMING,
	TIMER_LIGHT_ANIMATION,
	TIMER_PLAYER_ANIMATION,
	TIMER_FPS,
	TIMER0,
	TIMER1,
	TIMER2,
	TIMER3,
	TIMER4,
	TIMER5,
	TIMER6,
	TIMER7,
	TIMER8,
	TIMER9
};

// hold timer values
// struct timeval g_time_keepers[16];

void addTimer(const unsigned int interval, void(*callback)());
//void setTimer();
//void restartTimer();
void updateTimers();

float getSeconds();
unsigned int getMillisec();
float getEllapsedSeconds(const int timer);

#endif