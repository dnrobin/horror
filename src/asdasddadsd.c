#include "common.h"

#include "glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#ifdef DEBUG
void print_gl_error()
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        switch (err)
        {
            case 0x0500:
                printf("Error: GL_INVALID_ENUM\n");
                break;
            case 0x0501:
                printf("Error: GL_INVALID_VALUE\n");
                break;
            case 0x0502:
                printf("Error: GL_INVALID_OPERATION\n");
                break;
            case 0x0503:
                printf("Error: GL_STACK_OVERFLOW\n");
                break;
            case 0x0504:
                printf("Error: GL_STACK_UNDERFLOW\n");
                break;
            case 0x0505:
                printf("Error: GL_OUT_OF_MEMORY\n");
                break;
            case 0x0506:
                printf("Error: GL_INVALID_FRAMEBUFFER_OPERATION\n");
                break;
            case 0x0507:
                printf("Error: GL_CONTEXT_LOST (with OpenGL 4.5 or ARB_KHR_robustness)\n");
                break;
            case 0x8031:
                printf("Error: GL_TABLE_TOO_LARGE1\n");
                break;
        default:
            printf("GL ERROR: Unknown.\n");
            break;
        }
    }
}
#else
void print_gl_error() {}
#endif

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}



static GLFWwindow *win = NULL;
static GLuint vertex_array;
static GLuint program;
static GLint mvp_location;
static ALCdevice *dev = NULL;

int main(int argc, char const *argv[])
{

    

    dev = alcOpenDevice(NULL);

    // make_scene();

    double oldtime = glfwGetTime();

    for(;;)
    {
        if (glfwWindowShouldClose(win)) {
            break;
        }

        double time = glfwGetTime();
        if ((time - oldtime) > 0.0067)
        {
            // render_scene();

            glfwSwapBuffers(win);
            oldtime = time;
        }

        glfwPollEvents();
    }

    alcCloseDevice(dev);

    glfwDestroyWindow(win);

    glfwTerminate();

    return 0;
}