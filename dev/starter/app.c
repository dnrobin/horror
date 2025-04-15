#include "shared.h"
#include "render.h"

#include "glad.h"
#include <GLFW/glfw3.h>

extern GLFWwindow *win;

GLuint vao, vbo;
GLuint shader;
GLuint u_xy_loc;

float x = 0;
float y = 0;

const char *vs_str =
"in vec2 v_Position;\n"
"uniform vec2 u_xy;\n"
"void main() {\n"
"    gl_Position = vec4(u_xy + v_Position, 0, 1);\n"
"}";

const char *fs_str =
"out vec4 finalColor;"
"void main() {\n"
"   finalColor = vec4(1, 0, 0, 1);\n"
"}";

void render()
{
    glClearColor(0.1, 0.12, 0.21, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);

        glBindVertexArray(vao);

        glUniform2f(u_xy_loc, x, y);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glBindVertexArray(0);

    glUseProgram(0);
}

void update(double time, double dt)
{
    static float speed = 0.5;

    float dir[2];

    if (getkey(GLFW_KEY_W) || getkey(GLFW_KEY_UP)) {
        dir[1] = +1;
    }
    if (getkey(GLFW_KEY_A) || getkey(GLFW_KEY_LEFT)) {
        dir[0] = -1;
    }
    if (getkey(GLFW_KEY_S) || getkey(GLFW_KEY_DOWN)) {
        dir[1] = -1;
    }
    if (getkey(GLFW_KEY_D) || getkey(GLFW_KEY_RIGHT)) {
        dir[0] = +1;
    }

    vec2_normalize(dir);

    x += dt * speed * dir[0];
    y += dt * speed * dir[1];
}

bool app_init()
{
    int status;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_str, NULL);
    glCompileShader(vs);

    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char log[1024]; int sz;
        glGetShaderInfoLog(vs, 1024, &sz, log);
        LOGTRACE_ERROR("vertex shader compilation error: '%s'", log);
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_str, NULL);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char log[1024]; int sz;
        glGetShaderInfoLog(fs, 1024, &sz, log);
        LOGTRACE_ERROR("fragment shader compilation error: '%s'", log);
    }

    shader = glCreateProgram();
    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char log[1024]; int sz;
        glGetProgramInfoLog(shader, 1024, &sz, log);
        LOGTRACE_ERROR("failed to link shader: '%s'", log);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    u_xy_loc = glGetUniformLocation(shader, "u_xy");

    //---------------------------------------------------------------

    float v[] = {
        -.1, -.1,
         .1, -.1,
         .1,  .1,
        -.1,  .1,
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

    glBindVertexArray(0);

    return true;
}

void app_quit()
{
    glDeleteProgram(shader);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void app_tick()
{
    static double oldtime = 0;
    
    if (oldtime == 0) {
        oldtime = glfwGetTime();
    }

    double time = glfwGetTime();
    double dt = time - oldtime;

    if (dt > 0.0167) {
        
        update(time, dt);
        render();

        glfwSwapBuffers(win);
        oldtime = time;
    }
}