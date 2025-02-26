#ifndef __MAZE_GAME_RES_H__
#define __MAZE_GAME_RES_H__

typedef enum {
	ASSET_MODEL,
	ASSET_IMAGE,
	ASSET_SOUND,
	ASSET_MUSIC,
	
	MAX_ASSET_TYPE
} asset_type_t;

/* represents assets to be loaded from file: image, sound, model, etc. */
typedef struct {
	int 					asset_id;		// globally unique identifier
	asset_type_t 			type;
	const char 				*filename;
} map_asset_descriptor_t;

int f_load_map_asset_file(const map_asset_descriptor_t *desc);
// note: once an asset has been loaded it is automatically discarted

typedef struct {
	int 					asset_id;		// globally unique identifier
	const char 				*vertex_filename;
	const char 				*fragment_filename;
} shader_asset_descriptor_t;

int f_load_shader_asset_files(const shader_asset_descriptor_t *desc);

/* represents assets which are loaded and converted to subsystem objects */
typedef struct{
	asset_type_t 			type;			// asset class type
	int 					asset_id;		// globally unique idendifier
	
	void 					*pdata;			// generic pointer to asset data

	// note: subsystems are responsible for setting this
	// pointer when creating the asset and only they know
	// how to dereference this pointer to a meaningful type.
} map_asset_t;

map_asset_t *get_asset(int id);
// map_asset_t *get_asset(const char *name);





// typedef struct resource_descriptor {
// 	uint id;				// id of the resource
// 	uint type;				// resource type
// 	char* filename;			// filename to the resource
// } resource_descriptor_t;

// typedef struct texture_resource_descriptor {
// 	uint id;					// internal resource handle
// 	uint gl_id;					// OpenGL texture handle
// 	uint width;					// image width in pixels
// 	uint height;				// image height in pixels
// 	uint gl_colors;				// number of coulours (1-4)
// 	uint gl_color_ordering;		// ex. GL_RGBA
// 	uint gl_color_encoding;		// ex. GL_UNSIGNED_BYTE
// 	uint gl_filtering;			// ex. GL_LINEAR
// } texture_resource_descriptor_t;

// typedef struct shader_descriptor {
// 	uint id;
// 	uint gl_id;					// OpenGL handle
// 	const char *vertex_filename;
// 	const char *fragment_filename;
// } shader_descriptor_t;





typedef struct res_s {
	struct res_s* prev_resource;		// pointer to the previous resource in the list
	struct res_s* next_resource;		// pointer to the next resource in the list
	unsigned int id;					// id of the resource
	unsigned int type;					// resource type
	void* resource;						// pointer to the resource itself
} res_t;

#define RESOURCE_TYPE_IMAGE 	1
#define RESOURCE_TYPE_TEXTURE	2
#define RESOURCE_TYPE_SOUND		3

// resources linked-list
// SHOULD BE PRIVATE...
res_t* r_first_resource;
res_t* r_last_resource;
int r_resource_count;

int loadResourceFromFile(const resource_descriptor_t* res);
int loadResource(const uint id, const uint type, void* res);
void* getResource(const int id);

#endif