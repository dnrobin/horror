#ifndef __MAZE_GAME_ANIMATION_H__
#define __MAZE_GAME_ANIMATION_H__

/**
 * - simple animations can be to perform update on timer
 * - computed animations with a function executed every frame
 * - key frame animations with time regular time interval between frames
 * all of this is governed by a high-level sequencer which updates avery frame.
 */

 #define MAX_ANIMATION_TRACKS 64

typedef enum {
    ANIM_TYPE_CALLBACK,
    ANIM_TYPE_KEYFRAME,
    MAX_ANIM_TYPES
} anim_type_t;

typedef struct {
    int start_tick_index;
    int duration_tick_index;
    union {

    } content;
} anim_frame_t;

typedef struct {
    anim_type_t type;
    union {
        void (*callback_0p)(void);
        void (*callback_1p)(float);
        anim_frame_t *frames;
    } props;
    float next_update;  // if -1 update every frame
    float interval;
    bool is_done;
} animation_t;

typedef struct {
    animation_t animation_tracks[MAX_ANIMATION_TRACKS];
} animator_t;


void add_animation();
void update_animations(float timeStep);

#endif