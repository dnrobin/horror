#include "src/types.h"

#define CGLTF_IMPLEMENTATION
#include "src/cgltf.h"
#include "src/glad.h"
#include <GLFW/glfw3.h>

extern void app_init();
extern void app_quit();
extern void app_update();

GLFWwindow *win;
int screen_width = 1080;
int screen_height = 964;

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

    win = glfwCreateWindow(screen_width, screen_height, "App Window", NULL, NULL);
    if (!win) {
        fprintf(stderr, "failed to create window.\n");
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(win);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    printf("Runnning OpenGL Version %d.%d\n", GLVersion.major, GLVersion.minor);

    glfwSetErrorCallback(glfw_err_cb);

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
