#include "shared.h"
#include "res.h"

#include "bitmap.h"
#include "sound.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// private asset linked list
struct list_item {
	struct list_item *prev;
	struct list_item *next;
	map_asset_t asset;
};

struct list_item *head;
struct list_item *tail;

static void insert_asset(map_asset_t *asset)
{
	
}


int f_load_shader_asset_files(const shader_asset_descriptor_t *desc)
{

}







// init resource count
int r_resource_count = 0;

int loadResourceFromFile(const resource_descriptor_t* desc)
{
	res_t* pres = r_last_resource;		// point pres to last in list
	char filename[256];					// max 256 chars in file path!
	
	// create a new resource struct
	res_t *res = (res_t*)malloc(sizeof(res_t));
	
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
	res->id = desc->id;
	res->type = desc->type;
	
	// set complete file path
	strcpy(filename, env_base_path);
	strcat(filename, desc->filename);
	
	#ifdef __DEBUG
		printf("-- loading resource %d from file %s\n",desc->id,filename);
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
	
	return 1;
}

int loadResource(const uint id, const uint type, void* resource) {
	
	res_t* res;
	
	// create a new resource struct
	res = (res_t*)malloc(sizeof(res_t));
	
	// link to previous
	r_last_resource->next_resource = res;
	res->prev_resource = r_last_resource;
	r_last_resource = res;
	
	res->id = id;
	res->type = type;
	res->resource = resource;
	
	return 1;
}

void* getResource(const int id)
{
	res_t* res = r_first_resource;
	
	for (int i = 0; i < r_resource_count; i++) {
		if ( res->id == id ) {
			return res->resource;
		}
		res = res->next_resource;
	}
	
	return NULL;
}

int loadTexture(const texture_resource_descriptor_t *res)
{
	bitmap_t* image = (bitmap_t*)getResource(res->id);
	
	#ifdef __DEBUG
		printf("-- uploading texture id %d\n",res->gl_id);
	#endif
	
    r_create_texture(&res->gl_id, image);
	
	// save texture id for reference
	g_textures[res->id] = res->gl_id;
	
	return 0;
}