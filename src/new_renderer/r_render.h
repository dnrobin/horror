#ifndef __R_RENDER_H__
#define __R_RENDER_H__

#include "r_mesh.h"
#include "r_light.h"

// typedef enum {
//     RENDER_TYPE_MESH = 0,

//     MAX_RENDER_TYPES
// } render_type_t;

// typedef struct {
//     render_type_t type;
//     union {
//         mesh_t *mesh;
//     } obj;
// } render_obj_t;

// typedef enum {
//     RENDER_PASS_GEOMETRY = 0,
//     RENDER_PASS_LIGHTING,
//     RENDER_PASS_SCREEN_EFFECTS,
//     RENDER_PASS_UI,
    
//     MAX_RENDER_PASS_TYPES
// } render_pass_type_t;

// typedef struct {
//     render_pass_type_t  type;
// } render_pass_t;

#define MESH_NULL           0
#define MESH_SOLID          (1 << 0)
#define MESH_TRANSPARENCY   (1 << 1)

typedef struct {
    unsigned char       flags;
    mat4_t              transform;
    mesh_t              *mesh;
} render_mesh_t;

typedef struct {
    render_mesh_t       *meshes;
    int                 num_meshes;

    light_t             *lights;
    int                 num_lights;

    color_t             sky_color;
    color_t             fog_color;
    float               fog_density;
    float               fog_falloff;
    float               fog_distance;
} render_scene_t;

#endif //__R_RENDER_H__