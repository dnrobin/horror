#ifndef __RENDER_H__
#define __RENDER_H__

#include "glad.h"
#include "cgltf.h"

#include "fileio.h"

// static const int gl_attach[3] = {
//     GL_GEOMETRY_SHADER,
//     GL_VERTEX_SHADER,
//     GL_FRAGMENT_SHADER,
// };

// typedef struct {
//     const char          **files;
//     int                 num_files;
// } attachment_info_t;

// typedef struct {
//     attachment_info_t   attachments[3];
//     const char          **loc_names;
//     unsigned int        *loc_index;
//     int                 num_locations;
// } shader_info_t;

// void f_load_shader(shader_info_t *info)
// {
//     for (int i = 0; i < 3; ++i) {

//         char **src = calloc(info->attachments[i].num_files, sizeof(char*));
//         int *len = calloc(info->attachments[i].num_files, sizeof(int));

//         for (int n = 0; n < info->attachments[i].num_files; ++n) {
//             src[n] = f_read_text_file(info->attachments[i].files[n]);
//             len[n] = strlen(src);
//         }

//         unsigned int i = r_compile_shader_source(gl_attach[i], src, len);
//     }
// }

typedef struct {
    unsigned int        handle;
    unsigned int        locs[GL_MAX_UNIFORM_LOCATIONS];
    // shader_info_t       *info;
} shader_t;

typedef enum {
    ATTRIB_LOC_POSITION,
    ATTRIB_LOC_TANGENT,
    ATTRIB_LOC_NORMAL,
    ATTRIB_LOC_COLOR,
    ATTRIB_LOC_TEXCOORD0,
    ATTRIB_LOC_TEXCOORD1,
    ATTRIB_LOC_TEXCOORD2,
    ATTRIB_LOC_TEXCOORD3,

    MAX_ATTRIB_LOCATION
} attrib_loc_t;

typedef struct {
    unsigned int handle;    // vao
    unsigned int buffer[2]; // vbo, ebo

    int num_vertices;
    int num_indices;
    int draw_mode;          // ex. GL_TRIANGLE

    cgltf_material const *material;
    cgltf_primitive const *data;
} mesh_t;

unsigned int r_compile_shader_attachment(GLenum att, const char **src, int *len);

shader_t r_load_shader_files(const char *vs_file, const char *fs_file);
void r_reload_shader_files(shader_t *shader, const char *vs_file, const char *fs_file);
shader_t r_load_shader_sources(const char *vs_src, const char *fs_src);
void r_reload_shader_sources(shader_t *shader, const char *vs_src, const char *fs_src);
void r_map_shader_location(shader_t *shader, int loc, const char *name);
void r_delete_shader(shader_t *shader);
void r_bind_shader(shader_t *shader);
void r_shader_set_int(shader_t *shader, int loc, int i);
void r_shader_set_vec2i(shader_t *shader, int loc, const int *v);
void r_shader_set_vec3i(shader_t *shader, int loc, const int *v);
void r_shader_set_vec4i(shader_t *shader, int loc, const int *v);
void r_shader_set_uint(shader_t *shader, int loc, unsigned int i);
void r_shader_set_vec2ui(shader_t *shader, int loc, const unsigned int *v);
void r_shader_set_vec3ui(shader_t *shader, int loc, const unsigned int *v);
void r_shader_set_vec4ui(shader_t *shader, int loc, const unsigned int *v);
void r_shader_set_float(shader_t *shader, int loc, float f);
void r_shader_set_vec2(shader_t *shader, int loc, const float *v);
void r_shader_set_vec3(shader_t *shader, int loc, const float *v);
void r_shader_set_vec4(shader_t *shader, int loc, const float *v);
void r_shader_set_mat2(shader_t *shader, int loc, bool transpose, const float *m);
void r_shader_set_mat3(shader_t *shader, int loc, bool transpose, const float *m);
void r_shader_set_mat4(shader_t *shader, int loc, bool transpose, const float *m);

mesh_t r_load_mesh_gltf(const cgltf_primitive *prim);
void r_reload_mesh_gltf(mesh_t *mesh, const cgltf_primitive *prim);
void r_delete_mesh(mesh_t *mesh);
void r_draw_mesh(mesh_t *mesh);

#endif