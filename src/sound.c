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

ALCdevice *device = NULL;
ALCcontext *context = NULL;

ALuint a_sound_buffers[MAX_SOUND_BUFFERS] = {0};
ALuint a_sound_sources[MAX_SOUND_SOURCES] = {0};
int a_sound_buffers_set_count = 0;
int a_sound_sources_set_count = 0;

int initAL() {
	
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

int shutdownAL() {
	
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

//==============================================================================================================

h_audio_buffer_descriptor loadSoundFromFile(const char* filename) {
	
	h_audio_buffer_descriptor sound;
	
	int error;
	// clear errors
	alGetError();
	
	if( (sound = (h_audio_buffer_descriptor)malloc(sizeof(t_audio_buffer_descriptor))) == NULL ) {
		printf("Error: could not allocate sound descriptor!\n");
		return NULL;
	}

	// load wav file data 
	alutLoadWAVFile((ALbyte*)filename, &sound->format, &sound->data, &sound->size, &sound->freq);
	
	// check errors
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not load sound file %s\n", error, alGetString(error), filename);
	  shutdownAL();
	  return NULL;
	}
	
	// keep buffer source_id for sound
	sound->buffer_id = a_sound_buffers_set_count;
	
	// increment set buffer number
	a_sound_buffers_set_count++;
	
	// load buffer data
	alBufferData(a_sound_buffers[sound->buffer_id], sound->format, sound->data, sound->size, sound->freq);
	
	// check errors
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not set sound buffer data\n", error, alGetString(error));
	  shutdownAL();
	  return 0;
	}
	
	// unload wav data
	alutUnloadWAV(sound->format, sound->data, sound->size, sound->freq);
	
	// check errors
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not unload sound data\n", error, alGetString(error));
	  shutdownAL();
	  return 0;
	}
	
	return sound;
}

h_sound_emitter get_new_sound_emitter(const int sound_buffer_id) {
	
	h_sound_emitter emitter;
	
	// create new emitter instance
	if( (emitter = (h_sound_emitter)malloc(sizeof(t_sound_emitter))) == NULL ) {
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

int add_sound_emitter_to_scene(h_sound_emitter emitter) {
	
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

void sound_update_listener(vec3_t* position, vec3_t* direction, vec3_t* up) {
	
	// orientation parameters
	ALfloat orientation[] = { direction->x, direction->y, direction->z, up->x, up->y, up->z };
	
	// set listener position
	alListenerfv(AL_POSITION, (ALfloat*)position);
	
	// set listener orientation
	alListenerfv(AL_ORIENTATION, orientation);
}

void load_sound_emitters(const int soundc, t_sound_resource_descriptor* soundv) {

	int i;
	h_audio_buffer_descriptor res;
	h_sound_emitter emitter;
	
	for ( i = 0; i < soundc; i ++ ) {
		res = getResource(soundv[i].id);
		
		emitter = get_new_sound_emitter( res->buffer_id );

		// set emitter
		emitter->options = soundv[i].options;
		emitter->position = vec3(soundv[i].position[0],soundv[i].position[1],soundv[i].position[2]);
		emitter->velocity = vec3(soundv[i].velocity[0],soundv[i].velocity[1],soundv[i].velocity[2]);
		emitter->direction = vec3(soundv[i].direction[0],soundv[i].direction[1],soundv[i].direction[2]);
		emitter->gain = soundv[i].gain;
		emitter->gain_rolloff = soundv[i].gain_rolloff;
		emitter->min_distance = soundv[i].min_distance;
		emitter->max_distance = soundv[i].max_distance;
		emitter->min_gain = soundv[i].min_gain;
		emitter->max_gain = soundv[i].max_gain;
		emitter->pitch = soundv[i].pitch;
		emitter->cone_inner_angle = soundv[i].cone_inner_angle;
		emitter->cone_outer_angle = soundv[i].cone_outer_angle;
		emitter->cone_gain_factor = soundv[i].cone_gain_factor;
		
		add_sound_emitter_to_scene(emitter);
		
		// store ids in resource
		soundv[i].source_id = emitter->source_id;
		
		if ( emitter->options & SOUND_EMIT_AUTOPLAY )
			alSourcePlay(a_sound_sources[emitter->source_id]);
	}
	
	// ERROR INCOMPLETE CODE EMITTER INFO IS LOST HERE MUST STORE IN RESMAN!!!!!!
}

void soundSetState(const int source_id, const int state_id) {
	
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
	//report any error
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not set sound state %d\n", error, alGetString(error), source_id);
	  return;
	}
}

//==============================================================================================================

void playSound(const int source_id) {
	
	int error; alGetError();
	
	alSourcePlay(a_sound_sources[source_id]);
	
	//report any error
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not play sound %d\n", error, alGetString(error), source_id);
	  return;
	}
}

void stopSound(const int source_id) {
	
	int error; alGetError();
	
	alSourceStop(a_sound_sources[source_id]);
	
	//report any error
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	  printf("Error (%d - %s): could not stop sound %d\n", error, alGetString(error), source_id);
	  return;
	}
}