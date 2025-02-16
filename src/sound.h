#ifndef __SOUND_H__
#define __SOUND_H__

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

typedef struct audio_buffer_descriptor {
	ALenum     format;
	ALsizei    size;
	ALsizei    freq;
	ALboolean  loop;
	ALvoid*    data;
	unsigned int buffer_id;
} t_audio_buffer_descriptor, *h_audio_buffer_descriptor;

typedef struct sound_resource_descriptor {
	uint id;
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
} t_sound_resource_descriptor, *h_sound_resource_descriptor;

typedef struct sound_emitter {
	unsigned char options;		// option bits
	t_vec3 position;			// position in world
	t_vec3 velocity;			// velocity if moving to calculate dopler shift
	t_vec3 direction;			// direction the sound is being emitted
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
} t_sound_emitter, *h_sound_emitter;

int initAL();
int shutdownAL();
h_audio_buffer_descriptor loadSoundFromFile(const char* filename);
h_sound_emitter get_new_sound_emitter(const int sound_buffer_id);
int add_sound_emitter_to_scene(h_sound_emitter emitter);
void sound_update_listener(t_vec3* position, t_vec3* direction, t_vec3* up);
void load_sound_emitters(const int soundc, t_sound_resource_descriptor* soundv);
void soundSetState(const int source_id, const int state_id);
void playSound(const int source_id);
void stopSound(const int source_id);

#endif