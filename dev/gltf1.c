#include "types.h"
#include "linmath.h"

#define CGLTF_IMPLEMENTATION
#include "cgltf.h"
#include "glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//========================================================================================
//  low-level fileio
//========================================================================================

char *f_read_text_file(const char *filename)
{
    FILE *fp;
    size_t sz;

    fp = fopen(filename, "r");

    if (!fp) {
        fprintf(stderr, "file not found!\n");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *data = malloc(sz + 1);
    if (!data) {
        fprintf(stderr, "failed to allocate memory for text file!\n");
        return NULL;
    }

    if (fread(data, sz, 1, fp) == 0) {
        fprintf(stderr, "failed to read text file!\n");
        return NULL;
    }

    fclose(fp);

    return data;
}

void f_write_text_file(const char *filename, const char *data)
{
    FILE *fp;
    size_t sz;

    fp = fopen(filename, "w");

    if (!fp) {
        fprintf(stderr, "file not found!\n");
        return;
    }

    if (fwrite(data, sz, 1, fp) == 0) {
        fprintf(stderr, "failed to write text file!\n");
        return;
    }

    fclose(fp);
}

//========================================================================================
//  geometry/mesh api
//========================================================================================

// static int gltf_load_primitive(const cgltf_data *ctx, const cgltf_primitive *prim)
// {
//     GLuint ao, n = 0;
//     cgltf_buffer_view *buffer_views[cgltf_attribute_type_max_enum] = {0};
    
//     glGenVertexArrays(1, &ao);
//     glBindVertexArray(ao);

//     for (int i = 0; i < prim->attributes_count; ++i)
//     {
//         cgltf_accessor *a = prim->attributes[i].data;

//         // a->buffer_view INDEX
//         glBindBuffer(GL_ARRAY_BUFFER, a->buffer_view);

//         GLint components;
//         switch (a->type) {
//             case cgltf_type_scalar:
//              components = 1;
//             case cgltf_type_vec2:
//              components = 2;
//             case cgltf_type_vec3:
//              components = 3;
//             case cgltf_type_vec4:
//              components = 4;
//             case cgltf_type_mat2:
//              components = 4;
//             case cgltf_type_mat3:
//              components = 9;
//             case cgltf_type_mat4:
//              components = 16;
//         }

//         GLenum datatype;
//         switch (a->component_type) {
//             case cgltf_component_type_r_8: /* BYTE */
//                 datatype = GL_BYTE;
//             case cgltf_component_type_r_8u: /* UNSIGNED_BYTE */
//                 datatype = GL_UNSIGNED_BYTE;
//             case cgltf_component_type_r_16: /* SHORT */
//                 datatype = GL_SHORT;
//             case cgltf_component_type_r_16u: /* UNSIGNED_SHORT */
//                 datatype = GL_UNSIGNED_SHORT;
//             case cgltf_component_type_r_32u: /* UNSIGNED_INT */
//                 datatype = GL_UNSIGNED_INT;
//             case cgltf_component_type_r_32f: /* FLOAT */
//                 datatype = GL_FLOAT;
//         }

//         int id = prim->attributes[i].type - 1;  // type enum - 1 maps to layout(location=#)

//         glEnableVertexAttribArray(id);
//         glVertexAttribPointer(id
//             , components
//             , datatype
//             , a->normalized ? GL_TRUE : GL_FALSE
//             , a->stride
//             , (void*)a->offset);
        
//         // bool new_buffer = true;
//         // cgltf_buffer_view **b = &buffer_views[0];
//         // do {
//         //     if (a->buffer_view == *b) {
//         //         new_buffer = false;
//         //         break;
//         //     }
//         // } while (*b++ > 0);
        
//         // if (new_buffer) {
//         //     glGenBuffers(1, &bo[n++]);
//         //     glBindBuffer(GL_ARRAY_BUFFER, bo[n-1]);
//         //     glBufferData(GL_ARRAY_BUFFER
//         //         , a->buffer_view->buffer->size
//         //         , a->buffer_view->buffer->data
//         //         , GL_STATIC_DRAW);
//         // }
//     }

//     glUnmapBuffer(GL_ARRAY_BUFFER);

//     if (prim->indices) {
//         glGenBuffers(1, &bo[n++]);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo[n-1]);
//         glBufferData(GL_ELEMENT_ARRAY_BUFFER
//             , prim->indices->buffer_view->buffer->size
//             , prim->indices->buffer_view->buffer->data
//             , GL_STATIC_DRAW);
//     }

//     glBindVertexArray(0);

//     return ao;
// }


// static void gltf_load_mesh(const cgltf_data *ctx, const cgltf_mesh *mesh, mat4 tform)
// {
//     printf(" > creating '%s' mesh instance.\n", mesh->name);
// }

// static void gltf_get_node_transform(const cgltf_node *node, tform *out)
// {
//     tform_identity(out);

//     if (node->has_matrix) {
//         tform_from_mat4(out, (vec4*)node->matrix);
//     }

//     else {

//         if (node->has_translation) {
//             vec3_copy(out->translation, node->translation);
//         }

//         if (node->has_rotation) {
//             quat_copy(out->rotation, node->rotation);
//         }

//         if (node->has_scale) {
//             vec3_copy(out->scaling, node->scale);
//         }
//     }
// }

// static void gltf_process_node(const cgltf_data *ctx, const cgltf_node *node, tform T)
// {
//     tform local;
//     gltf_get_node_transform(node, &local);
//     tform_apply_transform(&local, &local, &T);

//     for (int i = 0; i < node->children_count; ++i) {
//         gltf_process_node(ctx, node->children[i], local);
//     }
// }

// static void gltf_load_scene(const cgltf_data *ctx, const cgltf_scene *scene)
// {
//     tform T;
//     tform_identity(&T);

//     for (int i = 0; i < scene->nodes_count; ++i) {
//         gltf_process_node(ctx, scene->nodes[i], T);
//     }
// }


void free_gltf_data(cgltf_data **data)
{
    cgltf_free(*data);
    *data = NULL;
}

cgltf_data *load_gltf_file(const char *filename)
{
    cgltf_options options = {0};
    cgltf_data* data = NULL;
    
    cgltf_result result = cgltf_parse_file(&options, filename, &data);
    if (result != cgltf_result_success) {
        fprintf(stderr, "error loading model file!");
        exit(-1);
    }

    return data;
}

//========================================================================================
// rendering api
//========================================================================================

enum {

    UNIFORM_LOCATION_TIME,
    UNIFORM_LOCATION_MAP_ALBEDO,
    UNIFORM_LOCATION_MAP_NORMAL,
    UNIFORM_LOCATION_MAP_HEIGHT,
    UNIFORM_LOCATION_MAP_ROUGHNESS,
    UNIFORM_LOCATION_MAP_METALNESS,
    UNIFORM_LOCATION_MAP_WETNESS,
    UNIFORM_LOCATION_MAP_AO,
    UNIFORM_LOCATION_MAP_MASK,
    UNIFORM_LOCATION_MODEL_MATRIX,
    UNIFORM_LOCATION_VIEW_MATRIX,
    UNIFORM_LOCATION_PROJ_MATRIX,

    MAX_UNIFORM_LOCATION
};

#define UNIFORM_LOCATION_MAP_DIFFUSE  UNIFORM_LOCATION_MAP_ALBEDO
#define UNIFORM_LOCATION_MAP_SPECULAR UNIFORM_LOCATION_MAP_METALNESS

typedef struct shader {
    unsigned int        gl_id;
    unsigned int        locs[MAX_UNIFORM_LOCATION];
} shader;


static GLuint compile_shader_attachment(int type, const char *str, int len)
{
    GLuint id;
    
    id = glCreateShader(type);
    glShaderSource(id, 1, &str, &len);
    glCompileShader(id);

    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        GLsizei len = 0;
        GLchar log[1024];
        glGetShaderInfoLog(id, 1024, &len, log);
        fprintf(stderr, "Error during %s shader compilation:\n%s\n"
            , type == GL_VERTEX_SHADER ? "vertex" : "fragment", log);

        return 0;
    }

    return id;
}

unsigned int r_load_shader_source(const char *vs, int vs_len, const char *fs, int fs_len)
{
    GLuint id, vs_id, fs_id;

    vs_id = compile_shader_attachment(GL_VERTEX_SHADER, vs, vs_len);
    fs_id = compile_shader_attachment(GL_FRAGMENT_SHADER, fs, fs_len);

    id = glCreateProgram();
    glAttachShader(id, vs_id);
    glAttachShader(id, fs_id);
    glLinkProgram(id);

    int status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        GLsizei len = 0;
        GLchar log[1024];
        glGetProgramInfoLog(id, sizeof(log), &len, log);
        fprintf(stderr, "Error linking shader:\n%s\n", log);

        return 0;
    }

    glDeleteShader(vs_id);
    glDeleteShader(fs_id);

    return id;
}

unsigned int r_load_shader_files(const char *vs_file, const char *fs_file)
{
    char *vs_source = f_read_text_file(vs_file);
    char *fs_source = f_read_text_file(fs_file);

    int id = r_load_shader_source(vs_source, strlen(vs_source), fs_source, strlen(fs_source));
    
    free(vs_source);
    free(fs_source);
    
    return id;
}

//========================================================================================
// world/gameplay api
//========================================================================================

typedef struct {
    unsigned int        *meshes;
} model_t;

typedef struct {

    // render api
    unsigned int        *meshes;
    unsigned int        *buffers;
    unsigned int        *textures;
    unsigned int        *samplers;

    int                 num_models;
    model_t             *models;

    cgltf_data          *map;   // gltf map data struct

} world_struct;

typedef struct {
    void *gltf_buffer_view_ptr;
    unsigned int gl_buffer_obj;
} buffer_obj_t;







static buffer_obj_t *buffers = NULL;
static int num_buffers;
static int buffers_idx;

static void init_buffers()
{
    num_buffers = 2;
    buffers_idx = 0;
    buffers = malloc(num_buffers * sizeof(buffer_obj_t));
}

static void free_buffers()
{
    if (buffers) {
        free(buffers);
        buffers = NULL;
    }
    num_buffers = 0;
}

static unsigned int *add_buffer(void *ptr, unsigned int obj)
{
    buffers[buffers_idx].gltf_buffer_view_ptr = ptr;
    buffers[buffers_idx].gl_buffer_obj = obj;
    buffers_idx;

    if (++buffers_idx >= num_buffers) {
        num_buffers *= 2;
        buffers = realloc(buffers, num_buffers * sizeof(buffer_obj_t));
    }
}

static unsigned int get_buffer(void *ptr)
{
    for (int i = 0; i < buffers_idx; ++i) {
        if (buffers[i].gltf_buffer_view_ptr == ptr) {
            return buffers[i].gl_buffer_obj;
        }
    }

    return 0;
}

static bool is_buffer(void *ptr)
{
    for (int i = 0; i < buffers_idx; ++i) {
        if (buffers[i].gltf_buffer_view_ptr == ptr) {
            return true;
        }
    }

    return false;
}

void load_map(const char *filename, world_struct *world)
{
    cgltf_data *data = load_gltf_file(filename);

    printf("GLTF Map Info:\n");
    printf(" textures: %zu\n", data->textures_count);
    printf(" materials: %zu\n", data->materials_count);
    printf(" meshes: %zu\n", data->meshes_count);
    printf(" scenes: %zu\n", data->scenes_count);
    printf(" nodes: %zu\n", data->nodes_count);

    // world->map = data;

    // // import textures
    // for (int i = 0; i < data->textures_count; ++i) {
    //     cgltf_texture *texture = &data->textures[i];
    // }

    // // import materials
    // for (int i = 0; i < data->materials_count; ++i) {
    //     cgltf_material *material = &data->materials[i];
    // }

    world->models = calloc(data->meshes_count, sizeof(model_t));

    // load models (gltf mesh)
    for (int n = 0; n < data->meshes_count; ++n) {

        cgltf_mesh *mesh = &data->meshes[n];

        model_t *model = &world->models[n];
        
        model->meshes = calloc(mesh->primitives_count, sizeof(unsigned int));

        // load meshes (gltf primitive)
        for (int i = 0; i < mesh->primitives_count; ++i) {
            cgltf_primitive *prim = &mesh->primitives[i];

            glGenVertexArrays(1, &model->meshes[i]);
            glBindVertexArray(model->meshes[i]);

            for (int a = 0; a < prim->attributes_count; ++a) {
                
                cgltf_attribute_type type = prim->attributes[a].type;

                // convert attrib type enum to fixed attrib index
                int attrib_index = type - 1;

                cgltf_accessor *acc = prim->attributes[a].data;

                unsigned int vbo;

                if (!is_buffer(acc->buffer_view)) {
                    glGenBuffers(1, &vbo);
                    glBindBuffer(GL_ARRAY_BUFFER, vbo);
                    glBufferData(GL_ARRAY_BUFFER
                        , acc->buffer_view->size
                        , acc->buffer_view->buffer
                        , GL_STATIC_DRAW);
                    add_buffer(acc->buffer_view, vbo);
                } else {
                    vbo = get_buffer(acc->buffer_view);
                    glBindBuffer(GL_ARRAY_BUFFER, vbo);
                }

                unsigned int numcomps;
                switch (acc->type) {
                    case cgltf_type_scalar:
                        numcomps = 1;
                        break;
                    case cgltf_type_vec2:
                        numcomps = 2;
                        break;
                    case cgltf_type_vec3:
                        numcomps = 3;
                        break;
                    case cgltf_type_vec4:
                        numcomps = 4;
                        break;
                    case cgltf_type_mat2:
                        numcomps = 4;
                        break;
                    case cgltf_type_mat3:
                        numcomps = 9;
                        break;
                    case cgltf_type_mat4:
                        numcomps = 16;
                        break;
                }

                unsigned int datatype;
                switch (acc->component_type) {
                    case cgltf_component_type_r_8:
                        datatype = GL_BYTE;
                        break;
                    case cgltf_component_type_r_8u:
                        datatype = GL_UNSIGNED_BYTE;
                        break;
                    case cgltf_component_type_r_16:
                        datatype = GL_SHORT;
                        break;
                    case cgltf_component_type_r_16u:
                        datatype = GL_UNSIGNED_SHORT;
                        break;
                    case cgltf_component_type_r_32u:
                        datatype = GL_UNSIGNED_INT;
                        break;
                    case cgltf_component_type_r_32f:
                        datatype = GL_FLOAT;
                        break;
                }

                glEnableVertexAttribArray(attrib_index);
                glVertexAttribPointer(attrib_index
                    , numcomps
                    , datatype
                    , acc->normalized
                    , acc->stride
                    , (void*)acc->offset);
            }
        }

        glBindVertexArray(0);
    }
}

void unload_map(world_struct *world)
{
    glDeleteBuffers(num_buffers, buffers);
    free_buffers();

    free_gltf_data(&world->map);
}


//========================================================================================
//========================================================================================
//========================================================================================
// main program
//========================================================================================
//========================================================================================
//========================================================================================

static GLFWwindow *win;
static int screen_width = 800;
static int screen_height = 600;

unsigned char keys[GLFW_KEY_LAST] = {0};

float base_speed = 10.0;

vec3 camera_eye, camera_local_z, camera_local_x, camera_local_y;
float camera_yfov, camera_znear, camera_zfar;
float camera_look_pitch, camera_look_yaw, camera_look_roll;

GLuint main_shader;
unsigned int main_UNIFORM_LOCATIONs[MAX_UNIFORM_LOCATION] = {0};

static world_struct world = {0};

static const char vs_str[] = 
    "#version 410\n"
    "layout (location=0) in vec3 position;\n"
    "layout (location=1) in vec3 bitangent;\n"
    "layout (location=2) in vec3 tangent;\n"
    "layout (location=3) in vec3 normal;\n"
    "layout (location=4) in vec3 color;\n"
    "uniform mat4 m_Model;\n"
    "uniform mat4 m_View;\n"
    "uniform mat4 m_Proj;\n"
    "out vec4 v_position;\n"
    "out vec3 v_color;\n"
    "void main() {\n"
    "   v_position = m_Proj * m_View * m_Model * vec4(position, 1.0);\n"
    "   v_color = color;\n"
    "}";

static const char fs_str[] = 
    "#version 410\n"
    "in vec3 v_color;\n"
    "out vec4 final_color;\n"
    "void main() {\n"
    "   final_color = vec4(v_color, 1.0);\n"
    "}";

void game_init()
{
    main_shader = r_load_shader_source(vs_str, strlen(vs_str), fs_str, strlen(fs_str));
    main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_MODEL_MATRIX] = glGetUniformLocation(main_shader, "m_Model");
    main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_VIEW_MATRIX]  = glGetUniformLocation(main_shader, "m_View");
    main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_PROJ_MATRIX]  = glGetUniformLocation(main_shader, "m_Proj");

    load_map("res/maps/map0.glb", &world);
}

void game_cleanup()
{
    unload_map(&world);
}

void game_update(double time, double dt)
{
    const float move_speed = base_speed * dt;

    ///////////////////////////////////////////////////////
    // define the look vector by its orientation
    vec3_set(camera_local_z
        , m_cos(camera_look_pitch) * m_sin(camera_look_yaw)
        ,-m_sin(camera_look_pitch)
        , m_cos(camera_look_pitch) * m_cos(camera_look_yaw)
    );
    vec3_normalize(camera_local_z);

    vec3_cross(camera_local_x, camera_local_z, VEC3_Y);
    vec3_normalize(camera_local_x);

    vec3_cross(camera_local_y, camera_local_x, camera_local_z);
    vec3_normalize(camera_local_y);

    ///////////////////////////////////////////////////////
    // compute displacement vector
    vec2 dir = {0, 0};

    if (keys[GLFW_KEY_W]) {
        dir[1] += +1;
    }
    if (keys[GLFW_KEY_A]) {
        dir[0] += -1;
    }
    if (keys[GLFW_KEY_S]) {
        dir[1] += -1;
    }
    if (keys[GLFW_KEY_D]) {
        dir[0] += +1;
    }

    vec2_normalize(dir);

    ///////////////////////////////////////////////////////
    // move eye to new position
    vec3 d = {
        move_speed*dir[0]*camera_local_x[0] - move_speed*dir[1]*camera_local_z[0],
        0,
        move_speed*dir[0]*camera_local_x[2] - move_speed*dir[1]*camera_local_z[2],
    };
    vec3_add(camera_eye, camera_eye, d);
}

static void draw_scene_nodes(const cgltf_node *node)
{
    for (int i = 0; i < node->children_count; ++i)
    {
        draw_scene_nodes(node->children[i]);
    }
}

static void draw_map(const cgltf_data *map)
{
    draw_scene_nodes(map->scene);
}

void game_render()
{
    glClearColor(0.15, 0.18, 0.2, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    
    glUseProgram(main_shader);

    mat4 view_matrix;
    mat4_identity(view_matrix);

    view_matrix[0][0] = camera_local_x[0];
    view_matrix[1][0] = camera_local_x[1];
    view_matrix[2][0] = camera_local_x[2];
    
    view_matrix[0][1] = camera_local_y[0];
    view_matrix[1][1] = camera_local_y[1];
    view_matrix[2][1] = camera_local_y[2];
    
    view_matrix[0][2] = camera_local_z[0];
    view_matrix[1][2] = camera_local_z[1];
    view_matrix[2][2] = camera_local_z[2];

    view_matrix[3][0] = -vec3_dot(camera_eye, camera_local_x);
    view_matrix[3][1] = -vec3_dot(camera_eye, camera_local_y);
    view_matrix[3][2] = -vec3_dot(camera_eye, camera_local_z);

    glUniformMatrix4fv(main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_VIEW_MATRIX], 1, GL_FALSE, (const float *)view_matrix);

    mat4 proj_matrix;
    mat4_perspective(proj_matrix, screen_width/screen_height, camera_yfov, camera_znear, camera_zfar);
    glUniformMatrix4fv(main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_PROJ_MATRIX], 1, GL_FALSE, (const float *)proj_matrix);
    
    // for (int i = 0; i < world.num_models; ++i)
    // {
    //     model_t *model = &world.models[i];

    //     for (int j = 0; j < model->num_meshes; ++j)
    //     {
    //         mesh_t *mesh = &model->meshes[i];
        
    //         glBindVertexArray(mesh->gl_id);

    //         glUniformMatrix4fv(main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_MODEL_MATRIX], 1, GL_FALSE, (const float *)model->localtoworld);

    //         // set material properties
    //         material *mat = mesh->material;
    //         glUniform1i(main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_MAP_DIFFUSE], mat->diffuse_map);
    //         glUniform1i(main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_MAP_SPECULAR], mat->specular_map);

    //         if (mesh->indices) {
    //             glDrawElements(mesh->draw_mode, mesh->num_indices, GL_UNSIGNED_INT, 0);
    //         }
    //         else {
    //             glDrawArrays(mesh->draw_mode, 0, mesh->num_vertices);
    //         }
    //     }

    //     glBindVertexArray(0);
    // }

    glUseProgram(0);
}

//========================================================================================
//
//========================================================================================

void app_init()
{
    // TODO: init all subsystems

    game_init();
}

void app_quit()
{
    // TODO: quit all subsystems

    game_cleanup();
}

void app_update()
{
    static double oldtime = 0;
    
    if (oldtime == 0) {
        oldtime = glfwGetTime();
    }

    double time = glfwGetTime();
    double dt = time - oldtime;
    if (dt > 0.0167)
    {
        // TODO: update all subsystems here

        game_update(time, dt);
        game_render();
        
        glfwSwapBuffers(win);
        oldtime = time;
    }
}

void app_key_cb(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(win, 1);
    }

    keys[key] = (action == GLFW_PRESS);
}

void app_mouse_cb(GLFWwindow* window, double xpos, double ypos)
{

}

//========================================================================================
// main executable
//========================================================================================

static void glfw_err_cb(int error_code, const char* description)
{
    fprintf(stderr, "GLFW Error (%d): %s\n", error_code, description);
}

int main(int argc, char const *argv[])
{
    if (glfwInit() == GLFW_FALSE) {
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    win = glfwCreateWindow(screen_width, screen_height, "Horror Maze", NULL, NULL);
    if (!win) {
        fprintf(stderr, "failed to create window.\n");
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(win);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    printf("Runnning OpenGL Version %d.%d\n", GLVersion.major, GLVersion.minor);

    glfwSetErrorCallback(glfw_err_cb);
    glfwSetKeyCallback(win, app_key_cb);
    glfwSetCursorPosCallback(win, app_mouse_cb);

    app_init();

    while (!glfwWindowShouldClose(win))
    {
        app_update();
        glfwPollEvents();
    }

    app_quit();

    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}