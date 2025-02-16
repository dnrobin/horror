#ifndef __RES_H__
#define __RES_H__

#include "common.h"

typedef struct resource_descriptor {
	uint id;				// id of the resource
	uint type;				// resource type
	char* filename;			// filename to the resource
} t_resource_descriptor, *h_resource_descriptor;

typedef struct t_res {
	struct t_res* prev_resource;		// pointer to the previous resource in the list
	struct t_res* next_resource;		// pointer to the next resource in the list
	unsigned int id;					// id of the resource
	unsigned int type;					// resource type
	void* resource;						// pointer to the resource itself
} t_res, *h_res;

#define RESOURCE_TYPE_IMAGE 	1
#define RESOURCE_TYPE_TEXTURE	2
#define RESOURCE_TYPE_SOUND		3

t_res* r_first_resource;
t_res* r_last_resource;
int r_resource_count;

int loadResourcesFromFile(const int resc, const t_resource_descriptor* resv);
int loadResource(const uint id, const uint type, void* resource);
void* getResource(const int id);

#endif