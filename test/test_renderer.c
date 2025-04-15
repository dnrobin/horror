#include "shared.h"
// #include "r_mesh.h"
// #include "r_shader.h"
// #include "r_render.h"

#include "glad.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
// DEFINITIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////

enum {
    VERTEX_ATTRIB_POSITION = 0,
    VERTEX_ATTRIB_TANGENT,
    VERTEX_ATTRIB_NORMAL,
    VERTEX_ATTRIB_COLOR,
    VERTEX_ATTRIB_TEXCOORD0,
    VERTEX_ATTRIB_TEXCOORD1,
    VERTEX_ATTRIB_TEXCOORD2,
    VERTEX_ATTRIB_TEXCOORD3,

    MAX_VERTEX_ATTRIBUTE
} vertex_attrib_t;

enum {
    SHADER_UNIFORM_LOC_MODELMATRIX,
    SHADER_UNIFORM_LOC_VIEWMATRIX,
    SHADER_UNIFORM_LOC_PROJMATRIX,
    SHADER_UNIFORM_LOC_NORMALMATRIX,
    SHADER_UNIFORM_LOC_TIME,

    MAX_SHADER_UNIFORM_LOCATION
} vertex_attrib_t;



typedef struct {
    unsigned int id;        // open gl resource id (vao)
    
} mesh_t;

typedef struct {
    unsigned int id;        // open gl resource id
    unsigned int locs[MAX_SHADER_UNIFORM_LOCATION];
} shader_t;


/////////////////////////////////////////////////////////////////////////////////////////////////////
// RENDERING FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN PROGRAM
/////////////////////////////////////////////////////////////////////////////////////////////////////

// App
static GLFWwindow *win;
static int win_width = 800;
static int win_height = 600;

// Input
static bool keys[GLFW_KEY_LAST] = {0};

// Camera
static float look_pitch = 0;
static float look_yaw = M_PI;
static vec3_t eye = { 0, 0, -5 };

// World


// Render
static GLuint shader_id;
static GLuint vbo, ibo, vao;
static int num_vertices;
static int num_indices;

void make_cube_mesh()
{
#if 1
    static float cube_vertices[] = {
        -1, -1, -1, 1, 0, 0, -1, -1, 1,
         1, -1, -1, 1, 0, 0,  1, -1, 2,
         1,  1, -1, 1, 0, 0,  1,  1, 3,
    
        -1, -1, -1, 1, 0, 0, -1, -1, 4,
         1,  1, -1, 1, 0, 0,  1,  1, 5,
        -1,  1, -1, 1, 0, 0, -1,  1, 6,
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3*sizeof(float), (void*)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 3*sizeof(float), (void*)(3*sizeof(float)));

    glBindVertexArray(0);

#else
    static float cube_vertices[] = {
        -1, -1, -1,  // 0
        -1, -1, +1,  // 1
        -1, +1, -1,  // 2
        -1, +1, +1,  // 3
        +1, -1, -1,  // 4
        +1, -1, +1,  // 5
        +1, +1, -1,  // 6
        +1, +1, +1,  // 7
    };

    static float cube_colors[] = {
        0, 0, 1,
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        0, 1, 0,
        0, 1, 1,
        1, 1, 1,
        0, 0, 0,
    };

    static unsigned int cube_indices[] = {
        0, 4, 6,
        0, 6, 2,

        4, 5, 7,
        4, 7, 6,

        5, 1, 3,
        5, 3, 7,

        1, 0, 2,
        1, 2, 3,
    };

    GLuint vbo1, vbo2, ibo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);

    // position
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3*sizeof(float), (void*)(0));

    // color
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 3*sizeof(float), (void*)(0));

    // indices
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
#endif
}

//==========================================================================================

static void update_and_render(double dt)
{
    const float speed = 10 * dt;

    vec3_t local_z, local_x, local_y;

    ///////////////////////////////////////////////////////
    // define the look vector by its orientation
    vec3(local_z
        , m_cos(look_pitch) * m_sin(look_yaw)
        ,-m_sin(look_pitch)
        , m_cos(look_pitch) * m_cos(look_yaw)
    );
    vec3_normalize(local_z, local_z);

    vec3_cross(local_x, local_z, VEC3_UP);
    vec3_normalize(local_x, local_x);

    vec3_cross(local_y, local_x, local_z);
    vec3_normalize(local_y, local_y);

    ///////////////////////////////////////////////////////
    // compute displacement vector
    vec2_t d = {0, 0};

    if (keys[GLFW_KEY_W]) {
        d[1] += +1;
    }
    if (keys[GLFW_KEY_A]) {
        d[0] += -1;
    }
    if (keys[GLFW_KEY_S]) {
        d[1] += -1;
    }
    if (keys[GLFW_KEY_D]) {
        d[0] += +1;
    }

    vec2_normalize(d, d);

    ///////////////////////////////////////////////////////
    // move eye to new position
    vec3_t disp = {
        speed*d[0]*local_x[0] - speed*d[1]*local_z[0],
        0,
        speed*d[0]*local_x[2] - speed*d[1]*local_z[2],
    };
    vec3_add(eye, eye, disp);

    ///////////////////////////////////////////////////////
    // compute view matrix
    mat4_t v;

        mat4_identity(v);

        v[0][0] = local_x[0];
        v[1][0] = local_x[1];
        v[2][0] = local_x[2];
        
        v[0][1] = local_y[0];
        v[1][1] = local_y[1];
        v[2][1] = local_y[2];
        
        v[0][2] = local_z[0];
        v[1][2] = local_z[1];
        v[2][2] = local_z[2];

        v[3][0] = -vec3_dot(eye, local_x);
        v[3][1] = -vec3_dot(eye, local_y);
        v[3][2] = -vec3_dot(eye, local_z);

    // compute projection matrix
    mat4_t p;
    mat4_perspective(p, win_width/win_height, 70, 0.001, 100);

    ///////////////////////////////////////////////////////
    // do the rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int loc;

    glUseProgram(shader_id);

    // set view transform
    loc = glGetUniformLocation(shader_id, "m_View");
    glUniformMatrix4fv(loc, 1, GL_FALSE, v[0]);
    loc = glGetUniformLocation(shader_id, "m_Proj");
    glUniformMatrix4fv(loc, 1, GL_FALSE, p[0]);

        glBindVertexArray(vao);

        mat4_t m;
        mat4_identity(m);
        loc = glGetUniformLocation(shader_id, "m_Model");
        glUniformMatrix4fv(loc, 1, GL_FALSE, m[0]);

        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);

        // render meshes
        // r_draw_mesh(&cube_mesh);

        glBindVertexArray(0);

    glUseProgram(0);
}

static void init()
{
    r_mesh_debug_cube(&cube_mesh);
    prog = r_create_shader_source(&vertex_source, &fragment_source);

    // glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.25, 0.15, .4, 1);
}

static void cleanup()
{
    r_delete_mesh(&cube_mesh);
}

//==========================================================================================

const vec2_t mouse_speed = { 0.002, 0.001 };
static float last_x, last_y;
static void mouse_move(GLFWwindow* window, double xpos, double ypos)
{
    static bool first_event = true;

    if (first_event) {
        last_x = xpos;
        last_y = ypos;
        first_event = false;
    }

    float dx = xpos - last_x;
    float dy = ypos - last_y;

    // update look angles
    look_yaw   +=  dx * mouse_speed[0];
    look_pitch += -dy * mouse_speed[1];

    last_x = xpos;
    last_y = ypos;
    
    if (look_pitch > +M_PI_2) look_pitch = +M_PI_2;
    if (look_pitch < -M_PI_2) look_pitch = -M_PI_2;
}

static void key_change(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (keys[GLFW_KEY_ESCAPE]) {
        glfwSetWindowShouldClose(win, 1);
    }

    if (action == GLFW_REPEAT) {
        return;
    }

    keys[key] = (action == GLFW_PRESS);
}

//==========================================================================================

int main(int argc, char const *argv[])
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    win = glfwCreateWindow(win_width, win_height, "rendere test", NULL, NULL);

    // capture mouse
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(win);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    printf("OpenGL version %d.%d (core)\n", GLVersion.major, GLVersion.minor);
    printf("Shading language version %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glfwSetKeyCallback(win, key_change);
    glfwSetCursorPosCallback(win, mouse_move);
    
    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(win, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    double x, y;
    glfwGetCursorPos(win, &x, &y);
    mouse_move(win, x, y);

    init();

    double oldtime = glfwGetTime();
    while (!glfwWindowShouldClose(win))
    {
        double time = glfwGetTime();
        if (time - oldtime > 0.0167) {
            update_and_render(time - oldtime);
            glfwSwapBuffers(win);
            oldtime = time;
        }

        glfwPollEvents();
    }

    cleanup();

    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}
