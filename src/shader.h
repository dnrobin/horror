#ifndef __MAZE_GAME_SHADERS_H__
#define __MAZE_GAME_SHADERS_H__

typedef struct {

    uint                gl_handle;      // OpenGL handle to object

    int                 mvp_location;   // shader layout location of mvp matrix
    int                 tex1_location;
    int                 tex2_location;
    int                 tex3_location;
    int                 tex4_location;
    int                 time_location;  // time for shader animation
} shader_t;

/**
 * TODO: bind locations for standard material attribs and mvp, etc.
 */

int r_load_shader_files(shader_t *shader, const char *vertex_file, const char *fragment_file);
int r_create_shader_source(shader_t *shader, const char * const*vertex_shader_source, int vertex_shader_length, const char * const*fragment_shader_source, int fragment_shader_length);
void r_delete_shader(shader_t *shader);

#endif