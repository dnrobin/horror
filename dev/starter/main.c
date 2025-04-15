#include "shared.h"

#include "glad.h"
#include <GLFW/glfw3.h>

extern bool app_init();
extern void app_quit();
extern void app_tick();

GLFWwindow *win;

static int screen_width = 1920;
static int screen_height = 1080;

static int framebuffer_width, framebuffer_height;

static bool keys[GLFW_KEY_LAST] = {0};

bool getkey(int key)
{
    if (key >= GLFW_KEY_LAST) {
        return false;
    }

    return keys[key];
}

void glfw_key_cb(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_REPEAT) {
        return;
    }
    
    keys[key] = (action == GLFW_PRESS);
}

//-------------------------------------------------------------------------------

void glfw_error_cb(int error_code, const char* description)
{
    if (error_code == GLFW_NO_ERROR) {
        return;
    }

    fprintf(stderr, "[glfw]" KR " error(" KY);

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

    fprintf(stderr, KR "):" K0 "%s\n", description);
}

void gl_check_error_cb(const char *name, void *funcptr, int len_args, ...)
{
    GLuint error_code = glad_glGetError();

    if (error_code == GL_NO_ERROR) {
        return;
    }

    fprintf(stderr, "[opengl]" KR " error(" KY);

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

    fprintf(stderr, KR "):" K0 " in call to " KC "%s" K0 "\n", name);
}

int main(int argc, char const *argv[])
{
    glfwInit();

    glfwSetErrorCallback(glfw_error_cb);

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

    glfwSetKeyCallback(win, glfw_key_cb);
    glfwMakeContextCurrent(win);

    // capture mouse
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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
        glfwDestroyWindow(win);
        glfwTerminate();
        exit(EXIT_FAILURE);
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
}