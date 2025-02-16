#include "shared.h"
#include "res.h"

#include "bitmap.h"
#include "sound.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// init resource count
int r_resource_count = 0;

int loadResourcesFromFile(const int resc, const t_resource_descriptor* resv) {
	int i;
	t_res* res;
	t_res* pres = r_last_resource;		// point pres to last in list
	char filename[256];				// max 256 chars in file path!
	
	for ( i = 0; i < resc; i ++ ) {
		
		// create a new resource struct
		res = (t_res*)malloc(sizeof(t_res));
		
		// when this is the first ever resource to be loaded
		if ( r_resource_count == 0 ) {
			r_first_resource = res;
			r_last_resource = res;
		}
		else {
			// link to previous
			pres->next_resource = res;
			res->prev_resource = pres;
			r_last_resource = res;
		}
		
		// set resource properties
		res->id = resv[i].id;
		res->type = resv[i].type;
		
		// set complete file path
		strcpy(filename, env_base_path);
		strcat(filename, resv[i].filename);
		
		#ifdef __DEBUG
			printf("-- loading resource %d from file %s\n",resv[i].id,filename);
		#endif
		
		switch ( res->type ) {
			case RESOURCE_TYPE_IMAGE:
				// only supports BMP for now
				res->resource = (void*)loadBitmapImageFromFile(filename);
				break;
			case RESOURCE_TYPE_SOUND:
				// only supports WAV for now
				res->resource = (void*)loadSoundFromFile(filename);
		}
		
		// increment the count
		r_resource_count++;
		
		// move up
		pres = res;
	}
	
	return 1;
}

int loadResource(const uint id, const uint type, void* resource) {
	
	t_res* res;
	
	// create a new resource struct
	res = (t_res*)malloc(sizeof(t_res));
	
	// link to previous
	r_last_resource->next_resource = res;
	res->prev_resource = r_last_resource;
	r_last_resource = res;
	
	res->id = id;
	res->type = type;
	res->resource = resource;
	
	return 1;
}

void* getResource(const int id) {
	int i;
	t_res* res = r_first_resource;
	
	for ( i = 0; i < r_resource_count; i ++ ) {
		if ( res->id == id ) {
			return res->resource;
		}
		res = res->next_resource;
	}
	
	return NULL;
}
