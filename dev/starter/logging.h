#ifndef __LOG_H__
#define __LOG_H__

#define LOG_DEBUG   1

#define K0        "\e[0m"
#define KK        "\e[30m"
#define KR        "\e[31m"
#define KG        "\e[32m"
#define KY        "\e[33m"
#define KB        "\e[34m"
#define KM        "\e[35m"
#define KC        "\e[36m"
#define KW        "\e[37m"

#include <stdio.h>
#include <stdarg.h>

#define MAX_LOG_LENGTH 1024

static inline void logfile_trace(const char *file, int lineno, FILE *fp, const char *msg, ...)
{
    char buf[MAX_LOG_LENGTH] = {0};

    va_list ap;
    va_start(ap, msg);
    vsnprintf(buf, MAX_LOG_LENGTH, msg, ap);
    va_end(ap);

    fprintf(fp, "[game] %s:%d: %s\n", file, lineno, buf);
}

static inline void logfile(FILE *fp, const char *msg, ...)
{
    char buf[MAX_LOG_LENGTH] = {0};

    va_list ap;
    va_start(ap, msg);
    vsnprintf(buf, MAX_LOG_LENGTH, msg, ap);
    va_end(ap);

    fprintf(fp, "[game] %s\n", buf);
}

#if LOG_DEBUG
#define _LOGTRACE(file,msg,...) logfile_trace(__FILE__,__LINE__,file,msg,##__VA_ARGS__)
#else
#define _LOGTRACE(file,msg,...) logfile(file,msg,##__VA_ARGS__)
#endif
#define LOGTRACE_FATAL(msg,...) do { \
    _LOGTRACE(stderr, KR "fatal: " K0 msg, ## __VA_ARGS__); \
    exit(EXIT_FAILURE); \
} while (0);
#define LOGTRACE_ERROR(msg,...) _LOGTRACE(stderr, KR "error: " K0 msg, ## __VA_ARGS__)
#define LOGTRACE_WARNING(msg,...) _LOGTRACE(stderr, KY "warning: " K0 msg, ## __VA_ARGS__)
#define LOGTRACE_NOTICE(msg,...) _LOGTRACE(stdout, KW "note: " K0 msg, ## __VA_ARGS__)
#define LOGTRACE(msg,...) LOGTRACE_NOTICE(msg, ## __VA_ARGS__)

#endif