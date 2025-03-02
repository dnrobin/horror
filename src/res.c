#include "shared.h"
#include "res.h"

#include "bitmap.h"
#include "sound.h"
#include "shader.h"
#include "texture.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static map_asset_t *_map_assets_head = NULL;
static map_asset_t *_map_assets_tail = NULL;
static size_t _map_asset_count = 0;

static void add_asset(map_asset_t *asset)
{
	asset->next = NULL;

	if (_map_asset_count == 0) {
		_map_assets_head = asset;
		_map_assets_tail = asset;
	}
	
	else {
		_map_assets_tail->next = asset;
	}

	_map_asset_count++;
}

map_asset_t *get_asset(int id)
{
	for (map_asset_t *asset = _map_assets_head; 
		asset->next != NULL; 
		asset = asset->next) 
	{
		if (asset->asset_id == id) {
			return asset;
		}
	}

	return NULL;
}

static int load_image_asset_from_file(map_asset_t *asset, const char *filename)
{
	return f_load_bitmap_file(filename, (bitmap_t*)asset->pdata);
}

static int load_sound_asset_from_file(map_asset_t *asset, const char *filename)
{
	return f_load_sound_file(filename, (audio_buffer_t*)asset->pdata);
}

int f_load_map_asset_file(const map_asset_descriptor_t *desc)
{
	char filename[1024];
	strcpy(filename, env_base_path);
	strcat(filename, desc->filename);

	#ifdef __DEBUG
		printf("-- loading resource %d from file %s\n", desc->asset_id, filename);
	#endif

	map_asset_t *asset = (map_asset_t*)calloc(1, sizeof(map_asset_t));

	if (!asset) {
		FATAL_RET("failed to create map asset storage!");
	}

	asset->asset_id = desc->asset_id;
	asset->type = desc->type;

	int status = STATUS_SUCCESS;

	switch (asset->type) {

		case ASSET_IMAGE:
			status = load_image_asset_from_file(asset, filename);
			break;

		case ASSET_SOUND:
			status = load_sound_asset_from_file(asset, filename);
			break;
	}

	add_asset(asset);

	return status;
}

int f_load_map_shader_file(const map_shader_descriptor_t *desc)
{
	map_asset_t *asset = (map_asset_t*)calloc(1, sizeof(map_asset_t));

	asset->asset_id = desc->asset_id;
	asset->type = ASSET_SHADER;

	char vertex_filename[1024];
	strcpy(vertex_filename, env_base_path);
	strcat(vertex_filename, desc->vertex_filename);

	char fragment_filename[1024];
	strcpy(fragment_filename, env_base_path);
	strcat(fragment_filename, desc->fragment_filename);

	shader_t *shader;
	if( (shader = (shader_t*)malloc(sizeof(bitmap_t))) == NULL ) {
		ERROR_RET("Error creating shader.");
	}

	int status  = r_load_shader_files(shader, vertex_filename, fragment_filename);

	asset->pdata = shader;
	// what the..
	shader->asset_id = asset->asset_id;

	add_asset(asset);

	return status;
}