#ifndef __JAS_LOGGING_H__
#define __JAS_LOGGING_H__

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#define E_RST "\x1B[0m"
#define E_RED "\x1B[31m"
#define E_GRN "\x1B[32m"
#define E_YEL "\x1B[33m"
#define E_BLU "\x1B[34m"
#define E_MAG "\x1B[35m"
#define E_CYN "\x1B[36m"
#define E_WHT "\x1B[37m"

extern FILE* logfile;

static inline void new_log()
{
    logfile = fopen("log.txt", "w");
}

static inline void open_log()
{
    logfile = fopen("log.txt", "a");
}

static inline void close_log()
{
    fclose(logfile);
}

static inline void __log(const char *fmt, ...)
{
    time_t rawtime;
    struct tm *timeinfo;
    char buf[4096];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    strftime(buf, sizeof(buf), "%A, %d %B %Y", timeinfo);
    
    fprintf(logfile, "%s: %s\n", buf);
}

#define _log(file,fmt,...) __log(file, fmt "\n" E_RST, ## __VA_ARGS__);

#ifdef DEBUG
#define LOG_FILE logfile
#define ERR_FILE logfile
#else
#define LOG_FILE stdout
#define ERR_FILE stderr
#endif

#define log(fmt,...) _log(LOG_FILE              \
    , E_YEL fmt , ## __VA_ARGS__);
#define log_error(fmt,...) _log(ERR_FILE        \
    , E_RED "Error in '%s' at line %d: " fmt    \
    , __FILE__ , __LINE__ , ## __VA_ARGS__);
#define log_warning(fmt,...) _log(ERR_FILE      \
    , E_YEL "Warning in '%s' at line %d: " fmt  \
    , __FILE__ , __LINE__ , ## __VA_ARGS__);
#define log_error_no_trace(fmt,...) _log(ERR_FILE   \
    , E_RED "Error: " fmt , ## __VA_ARGS__);
#define log_warning_no_trace(fmt,...) _log(ERR_FILE \
    , E_YEL "Warning: " fmt , ## __VA_ARGS__);

#endif