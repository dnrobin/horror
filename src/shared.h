#ifndef MAZ_SHARED_H
#define MAZ_SHARED_H

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <stdio.h>
#include <sys/time.h>

#include "types.h"
#include "mem.h"
#include "math.h"

#include "common.h"

#ifdef __DEBUG
#define debug_print(fmt,...) printf(fmt ## __VA_ARGS__);
#else
#define debug_print(fmt,...)
#endif

#endif