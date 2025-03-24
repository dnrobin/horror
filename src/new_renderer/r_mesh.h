#ifndef __MESH_H__
#define __MESH_H__

typedef enum {
    /* this corresponds to layout(location=X) */
    VERTEX_ATTRIB_POSITION = 0,
    VERTEX_ATTRIB_TANGENT,
    VERTEX_ATTRIB_NORMAL,
    VERTEX_ATTRIB_COLOR,
    VERTEX_ATTRIB_TEXCOORD0,
    VERTEX_ATTRIB_TEXCOORD1,
    VERTEX_ATTRIB_TEXCOORD2,
    VERTEX_ATTRIB_TEXCOORD3,

    MAX_VERTEX_ATTRIBUTES
} attrib_type_t;

typedef struct {
    int                 type;       // GLenum, data type, ex. GL_FLOAT
    size_t              size;       // size of single component data
    size_t              comps;      // number of components
    size_t              stride;
    void                *pointer;
    bool                has_data;
} vertex_attrib_t;

typedef struct {
    uint                 gl_handle;
    vertex_attrib_t     attribs[MAX_VERTEX_ATTRIBUTES];
    size_t              vertex_size;
    void                *data;
} vertex_buffer_t;

typedef struct {
    int                 program_handle;
    color_t             base_color;
    int                 base_map;
    int                 normal_map;
    int                 height_map;
    int                 wet_map;
    int                 ao_map;
} material_t;

typedef struct {

    uint                gl_handle;  // handle to vao
    int                 draw_type;  // ex. GL_TRIANGLE

    size_t              num_vertices;
    size_t              num_buffers;
    vertex_buffer_t     *buffers;
    
    size_t              num_indices;
    size_t              size_indices;   // data type size
    unsigned int        *indices;

    material_t          material;
} mesh_t;

int r_create_mesh(mesh_t *mesh);
void r_delete_mesh(mesh_t *mesh);
void r_draw_mesh(const mesh_t *mesh);

#endif