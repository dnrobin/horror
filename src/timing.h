#ifndef __MAZE_GAME_TIMING_H__
#define __MAZE_GAME_TIMING_H__

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

void add_timer(const unsigned int interval, void(*callback)());
//void set_timer();
//void restart_timer();
void update_timers();

float getSeconds();
unsigned int getMillisec();
float getEllapsedSeconds(const int timer);

#endif