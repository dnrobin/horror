#include "types.h"
#include "linmath.h"

//=====================================================================================
// logging
//=====================================================================================

#define LOG_DEBUG   1

#define K0        "\e[0m"
#define KK        "\e[30m"
#define KR        "\e[31m"
#define KG        "\e[32m"
#define KY        "\e[33m"
#define KB        "\e[34m"
#define KM        "\e[35m"
#define KC        "\e[36m"
#define KW        "\e[37m"

#include <stdarg.h>

#define MAX_LOG_LENGTH 1024

static inline void logfile_trace(const char *file, int lineno, FILE *fp, const char *msg, ...)
{
    char buf[MAX_LOG_LENGTH] = {0};

    va_list ap;
    va_start(ap, msg);
    vsnprintf(buf, MAX_LOG_LENGTH, msg, ap);
    va_end(ap);

    fprintf(fp, "(squid) %s:%d: %s\n", file, lineno, buf);
}

static inline void logfile(FILE *fp, const char *msg, ...)
{
    char buf[MAX_LOG_LENGTH] = {0};

    va_list ap;
    va_start(ap, msg);
    vsnprintf(buf, MAX_LOG_LENGTH, msg, ap);
    va_end(ap);

    fprintf(fp, "(squid) %s\n", buf);
}

#if LOG_DEBUG
#define _LOGTRACE(file,msg,...) logfile_trace(__FILE__,__LINE__,file,msg,##__VA_ARGS__)
#else
#define _LOGTRACE(file,msg,...) logfile(file,msg,##__VA_ARGS__)
#endif
#define LOGTRACE_FATAL(msg,...) do { \
    _LOGTRACE(stderr, KR "fatal: " K0 msg, ## __VA_ARGS__); \
    exit(EXIT_FAILURE); \
} while (0);
#define LOGTRACE_ERROR(msg,...) _LOGTRACE(stderr, KR "error: " K0 msg, ## __VA_ARGS__)
#define LOGTRACE_WARNING(msg,...) _LOGTRACE(stderr, KY "warning: " K0 msg, ## __VA_ARGS__)
#define LOGTRACE_NOTICE(msg,...) _LOGTRACE(stdout, KW "note: " K0 msg, ## __VA_ARGS__)
#define LOGTRACE(msg,...) LOGTRACE_NOTICE(msg, ## __VA_ARGS__)

//=====================================================================================
// file i/o
//=====================================================================================

#include <stdio.h>
#include <string.h>

char *f_read_text_file(const char *filename)
{
    FILE *fp;
    size_t sz;

    char *data = NULL;

    fp = fopen(filename, "r");
    if (!fp) {
        LOGTRACE_ERROR("failed to open file '%s' for reading.", filename);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    data = malloc(sz + 1);
    if (!data) {
        LOGTRACE_ERROR("failed to allocating memory for file '%s' with size %zu bytes.", filename, sz);
        goto err;
    }

    if (fread(data, sz, 1, fp) == 0) {
        LOGTRACE_ERROR("failed to read file '%s'.", filename);
        goto err;
    }

    data[sz] = '\0';

    fclose(fp);

    return data;

err:
    if (data) free(data);
    fclose(fp);
    return NULL;
}

void f_write_text_file(const char *filename, const char *data)
{
    FILE *fp;
    size_t sz;

    fp = fopen(filename, "w");
    if (!fp) {
        LOGTRACE_ERROR("failed to open file '%s' for writing.", filename);
        return;
    }

    sz = strlen(data);

    if (fwrite(data, sz, 1, fp) == 0) {
        LOGTRACE_ERROR("failed to write file '%s'.", filename);
    }

    fclose(fp);
}

void f_append_text_file(const char *filename, const char *data)
{
    FILE *fp;
    size_t sz;

    fp = fopen(filename, "a");
    if (!fp) {
        LOGTRACE_ERROR("failed to open file '%s' for writing.", filename);
        return;
    }

    sz = strlen(data);

    if (fwrite(data, sz, 1, fp) == 0) {
        LOGTRACE_ERROR("failed to write file '%s'.", filename);
    }

    fclose(fp);
}

void *f_read_file_binary(const char *filename, size_t *sz)
{
    FILE *fp;

    void *data = NULL;

    fp = fopen(filename, "rb");
    if (!fp) {
        LOGTRACE_ERROR("failed to open file '%s' for reading.", filename);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    *sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    data = malloc(*sz);
    if (!data) {
        LOGTRACE_ERROR("failed to allocating memory for file '%s' with size %zu bytes.", filename, *sz);
        goto err;
    }

    if (fread(data, *sz, 1, fp) == 0) {
        LOGTRACE_ERROR("failed to read file '%s'.", filename);
        goto err;
    }

    fclose(fp);

    return data;

err:
    if (data) free(data);
    fclose(fp);
    return NULL;
}

void f_write_file_binary(const char *filename, const void *data, size_t sz)
{
    FILE *fp;

    fp = fopen(filename, "wb");
    if (!fp) {
        LOGTRACE_ERROR("failed to open file '%s' for writing.", filename);
        return;
    }

    if (fwrite(data, sz, 1, fp) == 0) {
        LOGTRACE_ERROR("failed to write file '%s'.", filename);
    }

    fclose(fp);
}

//=====================================================================================
// main program
//=====================================================================================

#include "glad.h"
#include <GLFW/glfw3.h>

GLFWwindow *win;
GLuint shader;
GLuint vao, vbo;

void update(double time, double dt)
{

}

void render()
{
    glClearColor(0.1, 0.12, 0.21, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glBindVertexArray(0);

    glUseProgram(0);
}

#include <string.h>

bool app_init()
{
    const char *vs_str = "#version 460\n"
    "layout (location=0) in vec2 xy;\n"
    "void main() {\n"
    "    gl_Position = vec4(xy, 0, 1);\n"
    "}";

    const char *fs_str = "#version 460\n"
    "layout (location=0) in vec2 xy;\n"
    "void main() {\n"
    "   gl_Position = vec4(xy, 0, 1);\n"
    "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_str, NULL);
    glCompileShader(vs);

    int status;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    if (status == )
    {
        
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_str, NULL);
    glCompileShader(fs);

    shader = glCreateProgram();
    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);

    glDeleteShader(vs);
    glDeleteShader(fs);

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

static int screen_width = 1920;
static int screen_height = 1080;

static int framebuffer_width, framebuffer_height;

void glfw_err(int error_code, const char* description)
{
    if (error_code == GLFW_NO_ERROR) {
        return;
    }

    fprintf(stderr, "(glfw)" KR " error (" KY);

    switch (error_code) {

        case GLFW_NO_ERROR:
            fprintf(stderr, "GLFW_NO_ERROR");
            break;
        
        case GLFW_NOT_INITIALIZED:
            fprintf(stderr, "GLFW_NOT_INITIALIZED");
            break;
        
        case GLFW_NO_CURRENT_CONTEXT:
            fprintf(stderr, "GLFW_NO_CURRENT_CONTEXT");
            break;
        
        case GLFW_INVALID_ENUM:
            fprintf(stderr, "GLFW_INVALID_ENUM");
            break;
        
        case GLFW_INVALID_VALUE:
            fprintf(stderr, "GLFW_INVALID_VALUE");
            break;
        
        case GLFW_OUT_OF_MEMORY:
            fprintf(stderr, "GLFW_OUT_OF_MEMORY");
            break;
        
        case GLFW_API_UNAVAILABLE:
            fprintf(stderr, "GLFW_API_UNAVAILABLE");
            break;
        
        case GLFW_VERSION_UNAVAILABLE:
            fprintf(stderr, "GLFW_VERSION_UNAVAILABLE");
            break;
        
        case GLFW_PLATFORM_ERROR:
            fprintf(stderr, "GLFW_PLATFORM_ERROR");
            break;
        
        case GLFW_FORMAT_UNAVAILABLE:
            fprintf(stderr, "GLFW_FORMAT_UNAVAILABLE");
            break;
        
        case GLFW_NO_WINDOW_CONTEXT:
            fprintf(stderr, "GLFW_NO_WINDOW_CONTEXT");
            break;
        
        case GLFW_CURSOR_UNAVAILABLE:
            fprintf(stderr, "GLFW_CURSOR_UNAVAILABLE");
            break;
        
        case GLFW_FEATURE_UNAVAILABLE:
            fprintf(stderr, "GLFW_FEATURE_UNAVAILABLE");
            break;
        
        case GLFW_FEATURE_UNIMPLEMENTED:
            fprintf(stderr, "GLFW_FEATURE_UNIMPLEMENTED");
            break;
        
        case GLFW_PLATFORM_UNAVAILABLE:
            fprintf(stderr, "GLFW_PLATFORM_UNAVAILABLE");
            break;
    }

    fprintf(stderr, KR ")" K0 ": %s\n", description);
}

void gl_check_error_cb(const char *name, void *funcptr, int len_args, ...)
{
    GLuint error_code = glad_glGetError();

    if (error_code == GL_NO_ERROR) {
        return;
    }

    fprintf(stderr, "(opengl)" KR " error (" KY);

    switch (error_code) {
        case GL_INVALID_ENUM:
            fprintf(stderr, "GL_INVALID_ENUM");
            break;
        case GL_INVALID_VALUE:
            fprintf(stderr, "GL_INVALID_VALUE");
            break;
        case GL_INVALID_OPERATION:
            fprintf(stderr, "GL_INVALID_OPERATION");
            break;
        case GL_OUT_OF_MEMORY:
            fprintf(stderr, "GL_OUT_OF_MEMORY");
            break;
    }

    fprintf(stderr, KR ")" K0 " in call to '%s'\n", name);
}

int main(int argc, char const *argv[])
{
    glfwInit();

    glfwSetErrorCallback(glfw_err);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
    #endif

    win = glfwCreateWindow(screen_width, screen_height, "Window", NULL, NULL);

    if (!win) {
        LOGTRACE_FATAL("failed to create OpenGL window.");
    }

    glfwMakeContextCurrent(win);

    // rescales when retina/high-dp display
    float display_scale_x, display_scale_y;
    glfwGetWindowContentScale(win, &display_scale_x, &display_scale_y);
    glfwSetWindowSize(win, screen_width / display_scale_x, screen_height / display_scale_y);

    // center window on display
    int real_window_width, real_window_height;
    glfwGetWindowSize(win, &real_window_width, &real_window_height);
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(win, (mode->width - real_window_width) / 2, (mode->height - real_window_height) / 2);

    // load OpenGL API
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    printf("OpenGL API Version %d.%d\n", GLVersion.major, GLVersion.minor);
    glad_set_post_callback_gl(gl_check_error_cb);

    glfwGetFramebufferSize(win, &framebuffer_width, &framebuffer_height);
    glViewport(0, 0, framebuffer_width, framebuffer_height);
    glfwSwapInterval(1);

    if (!app_init()) {
        goto err;
    }

    while (!glfwWindowShouldClose(win))
    {
        app_tick();
        glfwPollEvents();
        if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(win, GLFW_TRUE);
        }
    }

    app_quit();

    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;

err:
    if (win) glfwDestroyWindow(win);
    glfwTerminate();
    return EXIT_FAILURE;
}
