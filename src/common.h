#ifndef H_COMMON
#define H_COMMON

#include <stdio.h>	// for debug print
#include <sys/time.h>

// UNIX COLOR CODES FOR SHELL OUTPUT
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int g_textures[1024];

// print debug info to console
#define __DEBUG 1
#define GL_DEBUG_WITH_MIN false
#define GL_DEBUG_GEOMETRY_MODE false

//#define DEBUG_GAME true

/* environment variables */
char* env_base_path;

#ifndef bool
    typedef unsigned char bool;
    #define false 	0
    #define true 	!false
#endif

typedef unsigned int uint;
typedef unsigned char uchar;

bool g_troubleshoot;

#endif