#ifndef __MAZE_GAME_SHARED_H__
#define __MAZE_GAME_SHARED_H__

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <stdio.h>

#include "logging.h"
#include "types.h"
#include "math.h"
#include "mem.h"

#ifdef __DEBUG
#define debug_print(fmt,...) printf(fmt ## __VA_ARGS__);
#else
#define debug_print(fmt,...)
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// print debug info to console
#define __DEBUG 1
#define GL_DEBUG_WITH_MIN false
#define GL_DEBUG_GEOMETRY_MODE false

//#define DEBUG_GAME true

/* environment variables */
extern char *env_asset_path;

bool g_troubleshoot;

/* TO BE REMOVED */
extern GLFWwindow *g_win;

#endif