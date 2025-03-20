#include "shared.h"

#include "graphics.h"
#include "sound.h"
#include "input.h"
#include "shader.h"

#include "controls.h"
#include "timing.h"
#include "trigger.h"
#include "timing.h"
#include "render.h"

#include "res.h"
#include "map.h"

#include "game.h"

#include <string.h>
#include <stdlib.h>

static GLFWwindow *win = NULL;
GLFWwindow *g_win;

uint g_window_width = 1080;
uint g_window_height = 675;
uint g_window_x = 100;
uint g_window_y = 100;
char* g_window_title = "Dark Maze";
bool g_fullscreen = true;
uint g_frame_millisec = 26;


char *env_asset_path = "./res/";

// void env_get_paths(char* unixpath)
// {
// 	char* str = strrchr(unixpath, '/');
	
// 	unsigned int len = strlen(unixpath) - strlen(str) + 1; // +1 to keep last '/'
	
// 	env_base_path = (char*)malloc(len);
	
// 	// store base path
// 	strncpy(env_base_path, unixpath, len);
// }

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	g_window_width = width;
	g_window_height = height;
}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_REPEAT) {
		return;
	}

			// MOVE THIS
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}

	if (action == GLFW_PRESS) {
		i_handle_key_down(key, mods);
	}
	else {
		i_handle_key_up(key, mods);
	}
}

void joystick_callback(int jid, int event)
{
	// TODO ?
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	i_handle_mouse_position_change(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
		i_handle_mouse_button_down(button);
	}
	else {
		i_handle_mouse_button_up(button);
	}
}

int main(int argc, char* argv[])
{
	// // SAVE NEW MAP
	// //saveMap(facesCount, &map, "build/res/maps/map5.map");
	// //exit(0);

	glfwInit();

	m_srand((int)glfwGetTime() << 1234);

    glfwSetErrorCallback(error_callback);

	#ifdef USE_MODERN_PIPELINE
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#endif

	win = glfwCreateWindow(800,600,"Horror Maze Game",NULL,NULL);

	g_win = win;

    glfwMakeContextCurrent(win);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	printf(KMAG "\n==System Depencies Profile==\n" KNRM);
	printf("-- OpenGl Version: %s\n",  glGetString(GL_VERSION));
	printf("-- GL Extensions Present: %s\n",  glGetString(GL_EXTENSIONS));
	printf("-- GL Shading Language Present: %s\n",  glGetString(GL_SHADING_LANGUAGE_VERSION));

    int width, height;
    glfwGetFramebufferSize(win, &width, &height);
    glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(win, resize_callback);
    glfwSetKeyCallback(win, key_callback);
	glfwSetJoystickCallback(joystick_callback);
	glfwSetCursorPosCallback(win, mouse_move_callback);
	glfwSetMouseButtonCallback(win, mouse_button_callback);

    glfwSwapInterval(1);
    glfwShowWindow(win);

	glfwSetInputMode(win, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetInputMode(win, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	if (glfwRawMouseMotionSupported()) {
		// glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    	glfwSetInputMode(win, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}

	printf("Launching from: %s\n\n",argv[0]);
	
	// env_get_paths(argv[0]);				// get launch base path for loading resources
	
	if ( g_fullscreen && strcmp(argv[argc-1],"-f") == 0 ) glfwMaximizeWindow(win);		// Put into full screen
	
	debug_print(KMAG "\n== Initializing graphics ==\n" KNRM);
	
	init_gl();									// initialize OpenGl state
	
	debug_print(KMAG "\n== Initializing sound ==\n" KNRM);
	
	init_al();									// initialize AL state
	
	game_code_init();		// init game environment
	
	double oldtime = glfwGetTime();

    while (!glfwWindowShouldClose(win))
    {
        double time = glfwGetTime();
		double dt = (time - oldtime);
        if (dt > 0.0067)
        {
			game_code_update(dt);

            glfwSwapBuffers(win);

            oldtime = time;
        }

        glfwPollEvents();
    }
	
	debug_print("\n== Shutting down ==\n");

	game_code_shutdown();

	shutdown_al();

    glfwDestroyWindow(win);
    glfwTerminate();
	
	return 0;
}