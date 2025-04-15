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
// world/map api
//========================================================================================

typedef struct {
    
    // texture_t           *textures;
    // material_t          *materials;

    // model_t             *models;
    // model_t             *lights;

    cgltf_data          *data;
} world_t;

void load_model(world_t *world, const cgltf_data *data)
{
    for (int n = 0; n < data->meshes_count; ++n) {

        cgltf_mesh *mesh = &data->meshes[n];

        // gltf primitives are converted to single mesh objects
        for (int i = 0; i < mesh->primitives_count; ++i) {

            cgltf_primitive *prim = &mesh->primitives[i];

            unsigned int vao;
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

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
    }

    glBindVertexArray(0);
}

void load_map(world_t *world, const char *filename)
{
    cgltf_data *data = load_gltf_file(filename);

    world->data = data;

    printf("GLTF Map Info:\n");
    printf(" textures: %zu\n", data->textures_count);
    printf(" materials: %zu\n", data->materials_count);
    printf(" meshes: %zu\n", data->meshes_count);
    printf(" scenes: %zu\n", data->scenes_count);
    printf(" nodes: %zu\n", data->nodes_count);

    for (int i = 0; i < data->meshes_count; ++i) {
        load_model(world, &data->meshes[i]);
    }
}

void unload_map(cgltf_data *data)
{
    free_gltf_data(data);
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

static world_t world = {0};

static char map[100][100] = {0};

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

#define NORTH_WALL  0x01
#define EAST_WALL   0x02
#define SOUTH_WALL  0x04
#define WEST_WALL   0x08

static void construct_maze(char *map[], int w, int h, int x, int y, int depth)
{
    int d = (int)m_rand_btw(0, 4);

    int x1 = x;
    int y1 = y;

    switch (d) {
        case 0:
            y1 += 1;
            break;
        case 1:
            x1 += 1;
            break;
        case 2:
            y1 -= 1;
            break;
        case 3:
            x1 -= 1;
            break;
    }

    if (x1 < 0 || x1 >= w 
     || y1 < 0 || y1 >= h) {
        return;
    }

    if (map[x1][y1] > 0) {
        return;
    }

    switch (d) {
        case 0:
            map[x][y]   &= ~NORTH_WALL;
            map[x1][y1] &= ~SOUTH_WALL;
            break;
        case 1:
            map[x][y]   &= ~EAST_WALL;
            map[x1][y1] &= ~WEST_WALL;
            break;
        case 2:
            map[x][y]   &= ~SOUTH_WALL;
            map[x1][y1] &= ~NORTH_WALL;
            break;
        case 3:
            map[x][y]   &= ~WEST_WALL;
            map[x1][y1] &= ~EAST_WALL;
            break;
    }
    
    construct_maze(map, w, h, x, y, depth + 1);
}

void app_init()
{
    // create shader
    main_shader = r_load_shader_source(vs_str, strlen(vs_str), fs_str, strlen(fs_str));
    main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_MODEL_MATRIX] = glGetUniformLocation(main_shader, "m_Model");
    main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_VIEW_MATRIX]  = glGetUniformLocation(main_shader, "m_View");
    main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_PROJ_MATRIX]  = glGetUniformLocation(main_shader, "m_Proj");

    // load meshes
    load_map(&world, "res/maps/map0.glb");

    // generate maze
    construct_maze(map, 100, 100, 50, 50, 0);
}

void app_quit()
{
    unload_map(&world);
}

//------------------------------------------------------------------------------------------------------

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

static void draw_mesh(mesh_t *mesh, tform *tform)
{
    glBindVertexArray(mesh->gl_id);

    glUniformMatrix4fv(main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_MODEL_MATRIX], 1, GL_FALSE, (const float *)mesh->localtoworld);

    // set material properties
    material_t *mat = mesh->material;
    glUniform1i(main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_MAP_DIFFUSE], mat->diffuse_map);
    glUniform1i(main_UNIFORM_LOCATIONs[UNIFORM_LOCATION_MAP_SPECULAR], mat->specular_map);

    if (mesh->indices) {
        glDrawElements(mesh->draw_mode, mesh->num_indices, GL_UNSIGNED_INT, 0);
    }
    else {
        glDrawArrays(mesh->draw_mode, 0, mesh->num_vertices);
    }

    glBindVertexArray(0);
}

static void draw_map()
{
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {

            // place floor & ceiling

            if (map[i][j] & NORTH_WALL) {
                // place wall
                // place corner
            }

            if (map[i][j] & EAST_WALL) {
                // place wall
                // place corner
            }

            if (map[i][j] & SOUTH_WALL) {
                // place wall
                // place corner
            }

            if (map[i][j] & WEST_WALL) {
                // place wall
                // place corner
            }
        }
    }
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
    
    draw_map();

    glUseProgram(0);
}

//========================================================================================
//
//========================================================================================

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