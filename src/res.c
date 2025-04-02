#include "shared.h"
#include "res.h"

#include "sound.h"
#include "shader.h"
#include "texture.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

static map_asset_t *_map_assets_head = NULL;
static map_asset_t *_map_assets_tail = NULL;
static size_t _map_asset_count = 0;

static const char *_debug_asset_type_names[] = {
	"ASSET_MODEL",
	"ASSET_IMAGE",
	"ASSET_SOUND",
	"ASSET_MUSIC",
	"ASSET_SHADER",
};

void _debug_print_asset_list()
{
	map_asset_t *a = _map_assets_head;

	printf("~~~ debug print asset list:\n");
	for (int i = 0; i < _map_asset_count; ++i)
	{
		printf("asset #%d: %s\n", a->id, _debug_asset_type_names[a->type]);

		a = a->next;
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
}

static void add_asset(map_asset_t *asset)
{
	asset->next = NULL;

	if (_map_assets_head == NULL) {
		_map_assets_head = asset;
	}
	
	else {
		_map_assets_tail->next = asset;
	}

	_map_assets_tail = asset;

	// printf("Added asset [%d -> %d].\n", _map_asset_count, asset->id);

	_map_asset_count++;
}

map_asset_t *get_asset(int id)
{
	map_asset_t *a = _map_assets_head;
	for (int i = 0; i < _map_asset_count; ++i)
	{
		// printf("\tlooking for asset %d at [%d]\n", id, asset->id);

		if (a->id == id) {
			return a;
		}

		a = a->next;
	}

	printf("Asset %d not found!\n",id);

	return NULL;
}

static texture_t *create_texture_image_from_file(const char *filename)
{
	/* TODO: maybe move the image loading stuff to texture.c just like sound.c */

	texture_t *obj;

	int w, h, n;
	unsigned char *data = stbi_load(filename, &w, &h, &n, 4);

	obj = (texture_t*)calloc(1, sizeof(texture_t));
	if (!obj) {
		return STATUS_FAILURE;
	}

	if (r_create_texture_buf(obj, w, h, n, data) == STATUS_FAILURE) {
		return NULL;
	}

	stbi_image_free(data);

	return obj;
}

static audio_buffer_t * create_sound_buffer_from_file(const char *filename)
{
	audio_buffer_t *obj;

	if (f_load_sound_file(filename, &obj) == STATUS_FAILURE) {
		return NULL;
	}

	return obj;
}

int f_load_map_asset_file(const map_asset_descriptor_t *desc)
{
	char filename[1024];
	strcpy(filename, env_asset_path);
	strcat(filename, desc->filename);

	#ifdef __DEBUG
		printf("-- loading asset %d from file %s\n", desc->asset_id, filename);
	#endif

	map_asset_t *asset = (map_asset_t*)calloc(1, sizeof(map_asset_t));

	if (!asset) {
		FATAL_RET("failed to create map asset storage!");
	}

	asset->id = desc->asset_id;
	asset->type = desc->type;

	int status = STATUS_SUCCESS;

	switch (asset->type) {

		case ASSET_IMAGE:
			asset->obj = create_texture_image_from_file(filename);
			break;

		case ASSET_SOUND:
			asset->obj = create_sound_buffer_from_file(filename);
			break;
	}

	add_asset(asset);

	return status;
}

int f_load_map_shader_file(const map_shader_descriptor_t *desc)
{
	int status;
	shader_t *shader;

	char vertex_filename[1024];
	strcpy(vertex_filename, env_asset_path);
	strcat(vertex_filename, desc->vertex_filename);

	char fragment_filename[1024];
	strcpy(fragment_filename, env_asset_path);
	strcat(fragment_filename, desc->fragment_filename);

	map_asset_t *asset = (map_asset_t*)calloc(1, sizeof(map_asset_t));
	if (!asset) {
		return STATUS_FAILURE;
	}

	asset->id = desc->asset_id;
	asset->type = ASSET_SHADER;

	if( (shader = (shader_t*)malloc(sizeof(shader_t))) == NULL ) {
		ERROR_RET("Error creating shader.");
	}

	status  = r_load_shader_files(shader, vertex_filename, fragment_filename);
	if (status == STATUS_FAILURE) {
		return status;
	}

	#ifdef __DEBUG
		printf("-- loaded shader %d from files: %s, %s, (gl id %d)\n", desc->asset_id, desc->vertex_filename, desc->fragment_filename, shader->gl_handle);
	#endif

	asset->obj = (void*)shader;

	add_asset(asset);

	return STATUS_SUCCESS;
}