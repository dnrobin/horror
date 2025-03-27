#ifndef __MAZE_GAME_SHARED_H__
#define __MAZE_GAME_SHARED_H__

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

// #define USE_MODERN_PIPELINE

#include "logging.h"
#include "types.h"
#include "linmath.h"

#include "mem.h"    // array stuff, string table, memory arena

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// some debug modes
#define GL_DEBUG_WITH_MIN false
#define GL_DEBUG_GEOMETRY_MODE false
#define DEBUG_GAME true

/* environment variables */
extern char *env_asset_path;

/* window state variables */
uint g_window_width;
uint g_window_height;
uint g_frame_millisec;

#endif