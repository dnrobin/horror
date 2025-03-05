#include "shared.h"
#include "sound.h"

#include "gamedefs.h"
#include "game.h"
#include "res.h"

#include <stdio.h>
#include <stdlib.h>

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <OpenAL/alut.h>

static ALCdevice *device = NULL;
static ALCcontext *context = NULL;

static ALuint a_sound_buffers[MAX_SOUND_BUFFERS] = {0};
static int a_sound_buffers_set_count = 0;

static ALuint a_sound_sources[MAX_SOUND_SOURCES] = {0};
static int a_sound_sources_set_count = 0;


static sound_emitter_t *get_new_sound_emitter(const int sound_buffer_id)
{	
	sound_emitter_t *emitter;
	
	if( (emitter = (sound_emitter_t*)malloc(sizeof(sound_emitter_t))) == NULL ) {
		printf("Error: could not create sound emitter\n");
		return NULL;
	}
	
	// set default values
	emitter->options = 0x0;	// no flags set
	emitter->position = vec3(0.0, 0.0, 0.0);
	emitter->velocity = vec3(0.0, 0.0, 0.0);
	emitter->direction = vec3(0.0, 0.0, 0.0);
	emitter->gain = 1.0;	// nominal gain
	emitter->pitch = 1.0;
	emitter->gain_rolloff = 1.0;
	emitter->min_distance = 1.0;
	emitter->max_distance = SOUND_MAX_DISTANCE;
	emitter->min_gain = 0.0;	// NOTE: I NEVER CHECK THIS VALUE, DEFAULT IS ALWAYS 0.0
	emitter->max_gain = 1.0;
	emitter->cone_inner_angle = 360.0;		// global source
	emitter->cone_outer_angle = 360.0;		// non directional source
	emitter->cone_gain_factor = 1.0;
	emitter->buffer_id = sound_buffer_id;
	emitter->source_id = a_sound_sources_set_count;
	
	// increment number of sources created
	a_sound_sources_set_count++;
	
	return emitter;
}

static int add_sound_emitter_to_scene(sound_emitter_t* emitter)
{	
	int error;
	// clear errors
	alGetError();
	
	// set source buffer
	alSourcei(a_sound_sources[emitter->source_id], AL_BUFFER, a_sound_buffers[emitter->buffer_id]);
	
	// check errors
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not set sound source %d\n", error, alGetString(error), emitter->source_id);
	  return 0;
	}
	
	// set source position
	alSourcefv(a_sound_sources[emitter->source_id], AL_POSITION, (ALfloat*)&emitter->position);
	alSourcefv(a_sound_sources[emitter->source_id], AL_VELOCITY, (ALfloat*)&emitter->velocity);
	
	// buffer related settings
	alSourcef(a_sound_sources[emitter->source_id], AL_GAIN, emitter->gain);
	alSourcei(a_sound_sources[emitter->source_id], AL_LOOPING, ((emitter->options&SOUND_EMIT_LOOPED)!=0?AL_TRUE:AL_FALSE));
	alSourcef(a_sound_sources[emitter->source_id], AL_PITCH, emitter->pitch);
	
	// position/direction related settings
	if ( emitter->options & SOUND_EMIT_GLOBAL ) {
		// globally heard source
		alSourcei(a_sound_sources[emitter->source_id], AL_SOURCE_RELATIVE, AL_TRUE);
		ALfloat pos0[] = {0.0, 0.0, 0.0}; alSourcefv(a_sound_sources[emitter->source_id], AL_POSITION, pos0); // always at listern's position
		alSourcef(a_sound_sources[emitter->source_id], AL_REFERENCE_DISTANCE, 10000000);	// player is always in the clamped zone
		alSourcef(a_sound_sources[emitter->source_id], AL_MIN_GAIN, 1.0);					// clamp gain is nominal
		alSourcef(a_sound_sources[emitter->source_id], AL_CONE_INNER_ANGLE, 360.0);
		alSourcef(a_sound_sources[emitter->source_id], AL_CONE_OUTER_ANGLE, 360.0);
	} else {
		if ( emitter->options & SOUND_EMIT_DIRECTIONAL ) {
			alSourcefv(a_sound_sources[emitter->source_id], AL_DIRECTION, (ALfloat*)&emitter->direction);
			alSourcef(a_sound_sources[emitter->source_id], AL_CONE_INNER_ANGLE, emitter->cone_inner_angle);
			alSourcef(a_sound_sources[emitter->source_id], AL_CONE_OUTER_ANGLE, emitter->cone_outer_angle);
			alSourcef(a_sound_sources[emitter->source_id], AL_CONE_OUTER_GAIN, emitter->cone_gain_factor);
		} else {
			alSourcef(a_sound_sources[emitter->source_id], AL_CONE_INNER_ANGLE, 360.0);		// AL will ignore direction
			alSourcef(a_sound_sources[emitter->source_id], AL_CONE_OUTER_ANGLE, 360.0);
		}
		alSourcei(a_sound_sources[emitter->source_id], AL_SOURCE_RELATIVE, AL_FALSE);
		alSourcef(a_sound_sources[emitter->source_id], AL_ROLLOFF_FACTOR, emitter->gain_rolloff);		// the rolloff should be set according to max distance!
		alSourcef(a_sound_sources[emitter->source_id], AL_REFERENCE_DISTANCE, emitter->min_distance);
		// check max dist for proper attenuation!
		alSourcef(a_sound_sources[emitter->source_id], AL_MAX_DISTANCE, (emitter->max_distance > SOUND_MAX_DISTANCE ? SOUND_MAX_DISTANCE : emitter->max_distance));
		// do the same with minimum gain to prevent hearing the sound loud from far away
		alSourcef(a_sound_sources[emitter->source_id], AL_MIN_GAIN, 0.0);
		alSourcef(a_sound_sources[emitter->source_id], AL_MAX_GAIN, emitter->max_gain);
	}

	// check errors
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not set sound source %d values\n", error, alGetString(error), emitter->source_id);
	  return 0;
	}
	
	return 1;
}

void s_sound_update_listener(vec3_t* position, vec3_t* direction, vec3_t* up)
{	
	// orientation parameters
	ALfloat orientation[] = { direction->x, direction->y, direction->z, up->x, up->y, up->z };
	
	// set listener position
	alListenerfv(AL_POSITION, (ALfloat*)position);
	
	// set listener orientation
	alListenerfv(AL_ORIENTATION, orientation);
}

int s_create_sound_emitter(sound_emitter_descriptor_t *desc)
{
	map_asset_t *asset = get_asset(desc->asset_id);
	if (asset == NULL) {
		ERROR_RET("Invalid asset id in sound emitter definition!");
	}

	audio_buffer_t *buf = (audio_buffer_t*)asset->obj;
	sound_emitter_t *emitter = get_new_sound_emitter( buf->buffer_id );

	// set emitter
	emitter->options = desc->options;
	emitter->position = vec3(desc->position[0],desc->position[1],desc->position[2]);
	emitter->velocity = vec3(desc->velocity[0],desc->velocity[1],desc->velocity[2]);
	emitter->direction = vec3(desc->direction[0],desc->direction[1],desc->direction[2]);
	emitter->gain = desc->gain;
	emitter->gain_rolloff = desc->gain_rolloff;
	emitter->min_distance = desc->min_distance;
	emitter->max_distance = desc->max_distance;
	emitter->min_gain = desc->min_gain;
	emitter->max_gain = desc->max_gain;
	emitter->pitch = desc->pitch;
	emitter->cone_inner_angle = desc->cone_inner_angle;
	emitter->cone_outer_angle = desc->cone_outer_angle;
	emitter->cone_gain_factor = desc->cone_gain_factor;
	
	add_sound_emitter_to_scene(emitter);
	
	// store ids in resource
	desc->source_id = emitter->source_id;
	
	if ( emitter->options & SOUND_EMIT_AUTOPLAY ) {
		alSourcePlay(a_sound_sources[emitter->source_id]);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setSound(int source_id, int state_id)
{	
	int error; alGetError();
	ALuint al_state;
	alGetSourcei(a_sound_sources[source_id], AL_SOURCE_STATE, &al_state);
	
	switch( state_id ) {
		case G_SOUND_PLAYED:
			if ( al_state == AL_PAUSED || al_state == AL_STOPPED || al_state == AL_INITIAL ) {
				alSourcePlay(a_sound_sources[source_id]);
			}
			break;
		case G_SOUND_STOPPED:
			if ( al_state == AL_PLAYING ) {
				alSourceStop(a_sound_sources[source_id]);
			}
			break;
	}
	
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not set sound state %d\n", error, alGetString(error), source_id);
	  return;
	}
}

void playSound(int source_id)
{	
	int error; alGetError();
	
	alSourcePlay(a_sound_sources[source_id]);
	
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not play sound %d\n", error, alGetString(error), source_id);
	  return;
	}
}

void stopSound(int source_id)
{	
	int error; alGetError();
	
	alSourceStop(a_sound_sources[source_id]);
	
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not stop sound %d\n", error, alGetString(error), source_id);
	  return;
	}
}

void pauseSound(int source_id)
{
	int error; alGetError();
	
	alSourcePause(a_sound_sources[source_id]);
	
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not stop sound %d\n", error, alGetString(error), source_id);
	  return;
	}
}

void rewindSound(int source_id)
{
	int error; alGetError();
	
	alSourceRewind(a_sound_sources[source_id]);
	
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not stop sound %d\n", error, alGetString(error), source_id);
	  return;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int init_al()
{	
	int error;
	// clear errors
	alGetError();

	device = alcOpenDevice(NULL);
	if ( !device ) {
		printf("Error opening audio device <%d: %s>\n",alcGetError(device), alcGetString(device, alcGetError(device)));
		return 0;
	}
	
	// create an audio context
	context = alcCreateContext(device, NULL);
	if ( !context ) {
		printf("Error create audio context <%d: %s>\n",alcGetError(device), alcGetString(device, alcGetError(device)));
		return 0;
	}
	
	// make current context
	alcMakeContextCurrent(context);
	if ( alcGetError(device) != ALC_NO_ERROR ) {
		printf("Error setting audio context <%d: %s>\n",alcGetError(device), alcGetString(device, alcGetError(device)));
		return 0;
	}
	
	// Create the sound buffers
	alGenBuffers(MAX_SOUND_BUFFERS, a_sound_buffers);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not generate sound buffer\n", error, alGetString(error));
	  return 0;
	}
	
	// keep track of buffers set
	a_sound_buffers_set_count = 0;
	
	// create sound sources
	alGenSources(MAX_SOUND_SOURCES, a_sound_sources);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not generate sound sources\n", error, alGetString(error));
	  return 0;
	}
	
	// set distance attenuation method
	alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	
	// adjust main volume
	alListenerf(AL_GAIN, 3.2);
	
	return 1;
}

int shutdown_al()
{	
	int error;
	// clear errors
	alGetError();
	
	// free buffers
	alDeleteSources(MAX_SOUND_SOURCES, a_sound_sources);
	alDeleteBuffers(MAX_SOUND_BUFFERS, a_sound_buffers);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not destroy sound buffers\n", error, alGetString(error));
	  return 0;
	}
	
	// destroy audio context
	ALCcontext* context = alcGetCurrentContext();
	alcDestroyContext(context);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not destroy context\n", error, alGetString(error));
	  return 0;
	}
	
	// close audio device
	ALCdevice* device = alcGetContextsDevice(context);
	alcCloseDevice(device);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not close device\n", error, alGetString(error));
	  return 0;
	}
	
	// final clean up
	alutExit();
	
	return 1;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int f_load_sound_file(const char* filename, audio_buffer_t **out)
{
	int error;
	// clear errors
	alGetError();

	audio_buffer_t *buf;
	
	if( (buf = (audio_buffer_t*)malloc(sizeof(audio_buffer_t))) == NULL ) {
		printf("Error: could not allocate sound descriptor!\n");
		return STATUS_FAILURE;
	}

	// load wav file data 
	alutLoadWAVFile((ALbyte*)filename, &buf->format, &buf->data, &buf->size, &buf->freq);
	
	// check errors
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not load sound file %s\n", error, alGetString(error), filename);
	  shutdown_al();
	  return STATUS_FAILURE;
	}
	
	// keep buffer source_id for sound
	buf->buffer_id = a_sound_buffers_set_count;
	
	// increment set buffer number
	a_sound_buffers_set_count++;
	
	// load buffer data
	alBufferData(a_sound_buffers[buf->buffer_id], buf->format, buf->data, buf->size, buf->freq);
	
	// check errors
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not set sound buffer data\n", error, alGetString(error));
	  shutdown_al();
	  return STATUS_FAILURE;
	}
	
	// unload wav data
	alutUnloadWAV(buf->format, buf->data, buf->size, buf->freq);
	
	// check errors
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not unload sound data\n", error, alGetString(error));
	  shutdown_al();
	  return STATUS_FAILURE;
	}

	*out = buf;
	
	return STATUS_SUCCESS;
}