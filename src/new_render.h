#ifndef __MAZE_RENDER_H__
#define __MAZE_RENDER_H__

/* mesh */

typedef enum {
    VERTEX_ATTRIB_POSITION = 0,
    VERTEX_ATTRIB_TANGENT,
    VERTEX_ATTRIB_NORMAL,
    VERTEX_ATTRIB_COLOR0,
    VERTEX_ATTRIB_COLOR1,
    VERTEX_ATTRIB_TEXCOORD0,
    VERTEX_ATTRIB_TEXCOORD1,
    VERTEX_ATTRIB_TEXCOORD2,
    VERTEX_ATTRIB_TEXCOORD3,
    MAX_VERTEX_ATTRIB
} attrib_type_t;

typedef struct {
    unsigned int 
} attrib_t;

typedef struct {
    attrib_t        attribs[MAX_VERTEX_ATTRIB];
    size_t          vertexsize;
} mesh_t;

/* texture */

/* material */

/* light */

/* shader */

typedef enum {
    SHADER_LOC_VERTEX_POSITION = 0,
    SHADER_LOC_VERTEX_TANGENT,
    SHADER_LOC_VERTEX_NORMAL,
    SHADER_LOC_VERTEX_COLOR0,
    SHADER_LOC_VERTEX_COLOR1,
    SHADER_LOC_VERTEX_TEXCOORD0,
    SHADER_LOC_VERTEX_TEXCOORD1,
    SHADER_LOC_VERTEX_TEXCOORD2,
    SHADER_LOC_VERTEX_TEXCOORD3,
    SHADER_LOC_ALBEDO_MAP,
    SHADER_LOC_NORMAL_MAP,
    SHADER_LOC_HEIGHT_MAP,
    SHADER_LOC_ROUGHNESS_MAP,
    SHADER_LOC_METALNESS_MAP,
    SHADER_LOC_AO_MAP,
    SHADER_LOC_MODELMATRIX,
    SHADER_LOC_VIEWMATRIX,
    SHADER_LOC_PROJMATRIX,
    SHADER_LOC_TIME,
    MAX_SHADER_LOCATION
} shader_loc_t;

typedef struct {
    unsigned int id;
    unsigned int locs[MAX_SHADER_LOCATION];
} shader_t;

/* framebuffer */


#endif