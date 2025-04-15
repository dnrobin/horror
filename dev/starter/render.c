#include "shared.h"
#include "render.h"

#define CGLTF_IMPLEMENTATION
#include "cgltf.h"
#include "glad.h"

#include <string.h>

const char *vs_default_str =
"in vec2 v_Position;\n"
"uniform vec2 u_xy;\n"
"void main() {\n"
"    gl_Position = vec4(u_xy + v_Position, 0, 1);\n"
"}";

const char *fs_default_str =
"out vec4 finalColor;"
"void main() {\n"
"   finalColor = vec4(1, 0, 0, 1);\n"
"}";

unsigned int r_compile_shader_attachment(GLenum att, const char **src, int *len)
{
    GLuint id = glCreateShader(att);
    glShaderSource(id, 1, src, len);
    glCompileShader(id);

    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
{
        char log[1024]; int sz;
        glGetShaderInfoLog(id, 1024, &sz, log);
        LOGTRACE_ERROR("%s shader compilation error: '%s'"
            , (att == GL_VERTEX_SHADER ? "vertex" : "fragment"), log);

        return 0;
    }

    return id;
}
static GLuint gl_create_shader(const char *vs_str, const char *fs_str)
{
    GLuint vs = r_compile_shader_attachment(GL_VERTEX_SHADER, vs_str, strlen(vs_str));
    GLuint fs = r_compile_shader_attachment(GL_FRAGMENT_SHADER, fs_str, strlen(fs_str));

    GLuint id = glCreateProgram();
    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);

    int status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char log[1024]; int sz;
        glGetProgramInfoLog(id, 1024, &sz, log);
        LOGTRACE_ERROR("failed to link shader: '%s'", log);

        return 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return id;
}
shader_t r_load_shader_sources(const char *vs_src, const char *fs_src)
{
    GLuint id = gl_create_shader(vs_src, fs_src);

    return (shader_t){ .handle = id, .locs = {0} };
}
shader_t r_load_shader_files(const char *vs_file, const char *fs_file)
{
    char *vs_src = f_read_text_file(vs_file);
    char *fs_src = f_read_text_file(fs_file);

    GLuint id = gl_create_shader(vs_src, fs_src);

    free(vs_src);
    free(fs_src);

    return (shader_t){ .handle = id, .locs = {0} };
}
void r_reload_shader_sources(shader_t *shader, const char *vs_src, const char *fs_src)
{
    glDeleteProgram(shader->handle);

    GLuint id = gl_create_shader(vs_src, fs_src);
    
    *shader = (shader_t){ .handle = id, .locs = {0} };
}
void r_reload_shader_files(shader_t *shader, const char *vs_file, const char *fs_file)
{
    glDeleteProgram(shader->handle);

    char *vs_src = f_read_text_file(vs_file);
    char *fs_src = f_read_text_file(fs_file);

    GLuint id = gl_create_shader(vs_src, fs_src);

    free(vs_src);
    free(fs_src);

    *shader = (shader_t){ .handle = id, .locs = {0} };
}
void r_delete_shader(shader_t *shader)
{
    glDeleteProgram(shader->handle);
    shader->handle = 0;
}
void r_bind_shader(shader_t *shader)
{
    glUseProgram(shader->handle);
}
void r_map_shader_location(shader_t *shader, int loc, const char *name)
{
    shader->locs[loc] = glGetUniformLocation(shader->handle, name);
}
void r_shader_set_int(shader_t *shader, int loc, int i)
{
    glUniform1i(loc, i);
}
void r_shader_set_vec2i(shader_t *shader, int loc, const int *v)
{
    glUniform2iv(loc, 1, v);
}
void r_shader_set_vec3i(shader_t *shader, int loc, const int *v)
{
    glUniform3iv(loc, 1, v);
}
void r_shader_set_vec4i(shader_t *shader, int loc, const int *v)
{
    glUniform4iv(loc, 1, v);
}
void r_shader_set_uint(shader_t *shader, int loc, unsigned int i)
{
    glUniform1ui(loc, i);
}
void r_shader_set_vec2ui(shader_t *shader, int loc, const unsigned int *v)
{
    glUniform2uiv(loc, 1, v);
}
void r_shader_set_vec3ui(shader_t *shader, int loc, const unsigned int *v)
{
    glUniform3uiv(loc, 1, v);
}
void r_shader_set_vec4ui(shader_t *shader, int loc, const unsigned int *v)
{
    glUniform4uiv(loc, 1, v);
}
void r_shader_set_float(shader_t *shader, int loc, float f)
{
    glUniform1f(loc, f);
}
void r_shader_set_vec2(shader_t *shader, int loc, const float *v)
{
    glUniform2fv(loc, 1, v);
}
void r_shader_set_vec3(shader_t *shader, int loc, const float *v)
{
    glUniform3fv(loc, 1, v);
}
void r_shader_set_vec4(shader_t *shader, int loc, const float *v)
{
    glUniform4fv(loc, 1, v);
}
void r_shader_set_mat2(shader_t *shader, int loc, bool transpose, const float *m)
{
    glUniformMatrix2fv(loc, 1, transpose, m);
}
void r_shader_set_mat3(shader_t *shader, int loc, bool transpose, const float *m)
{
    glUniformMatrix3fv(loc, 1, transpose, m);
}
void r_shader_set_mat4(shader_t *shader, int loc, bool transpose, const float *m)
{
    glUniformMatrix4fv(loc, 1, transpose, m);
}
mesh_t r_load_mesh_gltf(const cgltf_primitive *prim)
{
    GLuint id, vbo, ebo;

    int num_vertices = 0;
    int num_indices = 0;

    glGenVertexArrays(1, &id);
    glBindVertexArray(id);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW);

    void *data = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    for (int i = 0; i < prim->attributes_count; ++i)
    {
        prim->attributes[i].type;
        
        cgltf_accessor *a = prim->attributes[i].data;

        char *base = (char*)a->buffer_view->buffer + a->offset;

        int num_comps;
        switch (a->type) {
        	case cgltf_type_scalar:
                num_comps = 1;
                break;
            case cgltf_type_vec2:
                num_comps = 2;
                break;
            case cgltf_type_vec3:
                num_comps = 3;
                break;
            case cgltf_type_vec4:
                num_comps = 4;
                break;
            case cgltf_type_mat2:
                num_comps = 4;
                break;
            case cgltf_type_mat3:
                num_comps = 9;
                break;
            case cgltf_type_mat4:
                num_comps = 16;
                break;
            default:
                num_comps = 0;
                break;
        }

        for (int n = 0; n < a->count; ++a) {
            void *attr = base + n * a->stride;

            for (int c = 0; c < num_comps; ++c) {
                
            }
        }
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    

    GLenum draw_mode;
    switch (prim->type) {
        case cgltf_primitive_type_points:
            draw_mode = GL_POINTS;
            break;
        case cgltf_primitive_type_lines:
            draw_mode = GL_LINES;
            break;
        case cgltf_primitive_type_line_loop:
            draw_mode = GL_LINE_LOOP;
            break;
        case cgltf_primitive_type_line_strip:
            draw_mode = GL_LINE_STRIP;
            break;
        case cgltf_primitive_type_triangles:
            draw_mode = GL_TRIANGLES;
            break;
        case cgltf_primitive_type_triangle_strip:
            draw_mode = GL_TRIANGLE_STRIP;
            break;
        case cgltf_primitive_type_triangle_fan:
            draw_mode = GL_TRIANGLE_FAN;
            break;
        default:
            draw_mode = 0;
            break;
    }

        // switch (prim->attributes[i].type) {
        //     case cgltf_attribute_type_position:
        //         break;
        //     case cgltf_attribute_type_normal:
        //         break;
        //     case cgltf_attribute_type_tangent:
        //         break;
        //     case cgltf_attribute_type_texcoord:
        //         break;
        //     case cgltf_attribute_type_color:
        //         break;
        //     case cgltf_attribute_type_joints:
        //         break;
        //     case cgltf_attribute_type_weights:
        //         break;
        //     case cgltf_attribute_type_custom:
        //         break;
        // }

    cgltf_accessor *ind = prim->indices;

    if (ind) {
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER
            , ind->buffer_view->size
            , ind->buffer_view->buffer
            , GL_STATIC_DRAW);

        num_indices = prim->indices->count;
    }

    if (prim->material) {
        // 
    }

    glBindVertexArray(0);

    return (mesh_t) {
        .handle = id,
        .buffer = { vbo, ebo },
        .draw_mode = draw_mode,
        .num_vertices = num_vertices,
        .num_indices = num_indices,
        .material = prim->material,
        .data = prim
    };
}

void r_reload_mesh_gltf(mesh_t *mesh, const cgltf_primitive *prim)
{
    r_delete_mesh(mesh);
    mesh_t m = r_load_mesh_gltf(prim);
    mesh->handle = m.handle;
}

void r_delete_mesh(mesh_t *mesh)
{
    glDeleteVertexArrays(1, &mesh->handle);
    mesh->handle = 0;

    // delete buffers!!
}

void r_draw_mesh(mesh_t *mesh)
{
    glBindVertexArray(mesh->handle);

    if (mesh->num_indices > 0) {
        glDrawElements(mesh->draw_mode, 0, mesh->num_indices, NULL);
    }
    else {
        glDrawArrays(mesh->draw_mode, 0, mesh->num_vertices);
    }

    glBindVertexArray(0);
}