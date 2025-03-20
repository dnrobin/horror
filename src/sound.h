#ifndef __MAZE_GAME_SOUND_H__
#define __MAZE_GAME_SOUND_H__

#include <OpenAL/al.h>

#define MAX_SOUND_BUFFERS 32	// MAX POSSIBLE, ACTUAL NUMBER DEFINED AT RUNTIME
#define MAX_SOUND_SOURCES 32	// SAME

#define SOUND_MAX_DISTANCE 100			// max distance to start clipping when sound is not global

#define SOUND_EMIT_GLOBAL		0x01		// sound source emits everywhere
#define SOUND_EMIT_LOOPED		0x02		// sound source should loop playback
#define SOUND_EMIT_DIRECTIONAL	0x04		// when set, uses directional sound cone for calculations
#define SOUND_EMIT_AUTOPLAY		0x08
#define SOUND_EMIT_UNASSIGNED0	0x10
#define SOUND_EMIT_UNASSIGNED1	0x20
#define SOUND_EMIT_UNASSIGNED2	0x40
#define SOUND_EMIT_UNASSIGNED3	0x80

typedef struct {
	ALenum     format;
	ALsizei    size;
	ALsizei    freq;
	ALboolean  loop;
	ALvoid*    data;
	unsigned int buffer_id;
} audio_buffer_t;

int f_load_sound_file(const char* filename, audio_buffer_t **buf);

typedef struct {

	int asset_id; // here because we need the previously loaded buffer

	unsigned char options;		// option bits
	float position[3];			// position in world
	float velocity[3];			// velocity if moving to calculate dopler shift
	float direction[3];			// direction the sound is being emitted
	float gain;					// nominal gain value
	float pitch;				// pitch shift amount (1 octave for every 50% of nominal value 1.0)
	float gain_rolloff;			// gain rolloff factor per unit of distance to the source is source is not global
	float min_distance;			// minimum distance where to clip gain to a max value
	float max_distance;			// maximum distance where to clip gain to a min value
	float min_gain;				// lower limit for gain after computation before gain application
	float max_gain;				// upper limit for gain after computation before gain application
	float cone_inner_angle;		// inner cone angle (0.0 - 360.0)
	float cone_outer_angle;		// outer cone angle (0.0 - 360.0)
	float cone_gain_factor;		// gain multiplier for cone calculations
	unsigned int buffer_id;		// sound buffer id
	unsigned int source_id;		// emitter id (sound source id)
} sound_emitter_descriptor_t;

typedef struct {

	unsigned char options;		// option bits
	vec3_t position;			// position in world
	vec3_t velocity;			// velocity if moving to calculate dopler shift
	vec3_t direction;			// direction the sound is being emitted
	float gain;					// nominal gain value
	float pitch;				// pitch shift amount (1 octave for every 50% of nominal value 1.0)
	float gain_rolloff;			// gain rolloff factor per unit of distance to the source is source is not global
	float min_distance;			// minimum distance where to clip gain to a max value
	float max_distance;			// maximum distance where to clip gain to a min value
	float min_gain;				// lower limit for gain after computation before gain application
	float max_gain;				// upper limit for gain after computation before gain application
	float cone_inner_angle;		// inner cone angle (0.0 - 360.0)
	float cone_outer_angle;		// outer cone angle (0.0 - 360.0)
	float cone_gain_factor;		// gain multiplier for cone calculations
	unsigned int buffer_id;		// sound buffer id
	unsigned int source_id;		// emitter id (sound source id)
} sound_emitter_t;


void s_sound_update_listener(vec3_t position, vec3_t direction, vec3_t up);
int s_create_sound_emitter(sound_emitter_descriptor_t *desc);

void setSound(int source_id, int state_id);
void playSound(int source_id);
void stopSound(int source_id);
void pauseSound(int source_id);
void rewindSound(int source_id);


int init_al();
int shutdown_al();

#endif