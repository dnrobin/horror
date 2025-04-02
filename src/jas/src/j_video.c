#include "private.h"

#include <GLFW/glfw3.h>
#include "glad.h"

GLFWwindow *win = NULL;

int jas_create_window()
{
    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_FORWARD_COMPAT);
    #endif

    win = glfwCreateWindow(320, 240, "Game Window", NULL, NULL);

    glfwMakeContextCurrent(win);


}