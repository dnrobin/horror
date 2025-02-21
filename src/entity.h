#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "math.h"

/* Entity state flags */
#define ENT_STATE_ACTIVE		0x01
#define ENT_STATE_VISIBLE		0x02
#define ENT_STATE_UNUSED0		0x04
#define ENT_STATE_UNUSED1		0x08
#define ENT_STATE_UNUSED2		0x10
#define ENT_STATE_UNUSED3		0x20
#define ENT_STATE_UNUSED4		0x40
#define ENT_STATE_UNUSED5		0x80

/* Entity types */
typedef enum {
	ent_static_prop,			// defines any scene props (ex. chair, table, door, ...) possible to interact with
	ent_static_light,			// defines all static lights used to precalculate light maps
	ent_dynamic_light,			// defines animated and/or moving light sources (actual GL_LIGHT binding)
	ent_static_sound_emitter,	// defines position sound sources located in the map (can emit globally)
	ent_particle_generator,		// defines statically positioned particle system source
	ent_anim_model,				// defines animated model with no ai (ex. tree moving in wind, )
	ent_camera,					// defines camera model
	ent_trigger,				// defines invisible collisions that trigger events
	ent_timer,					// defines globally set timers for events
	ent_ai						// defines animated (or not) npc's in the world (ex. ennemies)
} e_entity_type;

/* structures */
typedef struct entity {
	vec3_t position;			// center world coordinates
	vec3_t direction;			// front facing normal
	vec3_t up;					// up facing normal
	unsigned char collides; 	// wether a collision map should be implemented
	unsigned char state;		// state flags
	unsigned char type;			// type of entity
} t_entity, *h_entity;

/* function prototypes */
h_entity g_create_new_entity();							// returns new entety handle
unsigned int g_register_entity(h_entity);				// returns entity id once added to list
unsigned int g_unregister_entity(unsigned int);			// removes entity from list by id
int g_destroy_entity(h_entity);							// destroy entity object
void g_position_entity();
void g_rotate_entity();
void g_point_entity(h_entity, vec3_t);
void g_point_entity_to_entity(h_entity, h_entity);
void g_set_entity_state(h_entity, unsigned char state_id, unsigned char state);

#endif
