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
	entity->position = vec3(0.0, 0.0, 0.0);
	entity->direction = vec3(0.0, 0.0, 1.0);
	entity->up = vec3(0.0, 1.0, 0.0);
	entity->state = 0x0;
	
	// add instance to array
	// push_array(&g_entities, entity);
	
	return entity;
}

void position_entity(h_entity ent, vec3_t p) {
	ent->position = p;
}

void move_entity(h_entity ent, vec3_t d) {
	ent->position = vec3_add(ent->position, d);
}

void rotate_entity(h_entity ent, vec3_t r) {
	vec3_rotate(&ent->direction, r.x, r.y, r.z);
	vec3_rotate(&ent->up, r.x, r.y, r.z);
}

void point_entity(h_entity ent, vec3_t p) {
}