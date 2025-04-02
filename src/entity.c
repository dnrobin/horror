#include "shared.h"
#include "entity.h"

#include <stdlib.h>

h_entity new_entity() {
	h_entity entity;
	
	// allocate instance
	if( (entity = (h_entity)malloc(sizeof(t_entity))) == NULL ) {
		printf("Error: could not create new entity\n");
		return NULL;
	}
	
	// initialize entity
	vec3(entity->position, 0.0, 0.0, 0.0);
	vec3(entity->direction, 0.0, 0.0, 1.0);
	vec3(entity->up, 0.0, 1.0, 0.0);
	entity->state = 0x0;
	
	// add instance to array
	// push_array(&g_entities, entity);
	
	return entity;
}

void position_entity(h_entity ent, vec3_t p) {
	vec3_copy(ent->position, p);
}

void move_entity(h_entity ent, vec3_t d) {
	vec3_add(ent->position, ent->position, d);
}

void rotate_entity(h_entity ent, vec3_t r) {
	// vec3_rotate(&ent->direction, r[0], r[1], r[2]);
	// vec3_rotate(&ent->up, r[0], r[1], r[2]);
}

void point_entity(h_entity ent, vec3_t p) {
}