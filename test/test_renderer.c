#include "shared.h"
#include "r_mesh.h"
#include "r_shader.h"
#include "r_render.h"

#include "glad.h"

static GLFWwindow *win;
static int win_width = 800;
static int win_height = 600;

static bool keys[GLFW_KEY_LAST] = {0};

static float look_pitch = 0;
static float look_yaw = M_PI;
static vec3_t eye = { 0, 0, -5 };

static GLuint prog;

static mesh_t cube_mesh;

static GLuint vao;
static int num_indices;

static const char *vertex_source = 
"#version 330\n"
"layout(location = 0) in vec3 pos;\n"
"layout(location = 1) in vec3 col;\n"
"uniform mat4 m_Model;\n"
"uniform mat4 m_View;\n"
"uniform mat4 m_Proj;\n"
"out vec3 v_color;\n"
"void main() {\n"
"   gl_Position = m_Proj * m_View * m_Model * vec4(pos, 1);\n"
"   v_color = col;"
"}\n";

static const char *fragment_source = 
"#version 330\n"
"in vec3 v_color;\n"
"out vec4 color;\n"
"void main() {\n"
"   color = vec4(v_color, 1);\n"
"}\n";

//==========================================================================================

// create a simple test mesh and render it.

void r_mesh_debug_cube(mesh_t *mesh)
{
    #if 1

    ///////////////////////////////////////////////////////
    // cube mesh

    float vertices[] = {
        -1, -1, -1,  // 0
        -1, -1, +1,  // 1
        -1, +1, -1,  // 2
        -1, +1, +1,  // 3
        +1, -1, -1,  // 4
        +1, -1, +1,  // 5
        +1, +1, -1,  // 6
        +1, +1, +1,  // 7
    };

    float colors[] = {
        0, 0, 1,
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        0, 1, 0,
        0, 1, 1,
        1, 1, 1,
        0, 0, 0,
    };

    unsigned int indices[] = {
        0, 4, 6,
        0, 6, 2,

        4, 5, 7,
        4, 7, 6,

        5, 1, 3,
        5, 3, 7,

        1, 0, 2,
        1, 2, 3,
    };

    num_indices = sizeof(indices) / sizeof(unsigned int);

    #else

    ///////////////////////////////////////////////////////
    // triangle mesh
    
    float vertices[] = {
        -1, -1, 0,
         1, -1, 0,
         0,  1, 0,
    };

    float colors[] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    #endif

    GLuint vbo1, vbo2, ibo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
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

    glUseProgram(prog);

    // set view transform
    loc = glGetUniformLocation(prog, "m_View");
    glUniformMatrix4fv(loc, 1, GL_FALSE, v[0]);
    loc = glGetUniformLocation(prog, "m_Proj");
    glUniformMatrix4fv(loc, 1, GL_FALSE, p[0]);

        glBindVertexArray(vao);

        mat4_t m;
        mat4_identity(m);
        loc = glGetUniformLocation(prog, "m_Model");
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
