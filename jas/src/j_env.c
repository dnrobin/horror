#include "jas_private.h"
#include "jas_env.h"

#include <sys/types.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef _WIN32
    #include <windows.h>
    #define getcwd _getcwd
    static const char pathsep = '\\';
#else
    #include <unistd.h>
    static const char pathsep = '/';
#endif

static struct env_s env = {0};
struct env_s *penv = &env;

static string_table_t env_st;

void rep_pathsep(char *path)
{
    int len = strlen(path);
    for (int i = 0; i < len; ++i) {
        if (path[i] == '/') {
            path[i] = pathsep;
        }
    }
}

char *make_path(char *buf, size_t size, const char *basepath, const char *path)
{
    size_t sz = size;
   
    strncpy(buf, basepath, MIN(strlen(basepath), sz));
    sz -= strlen(basepath);
    strncat(buf, path, MIN(strlen(basepath), sz));
    rep_pathsep(buf);

    return buf;
}

void init_env(int argc, const char *argv[])
{
    char buf[1024];

    st_alloc(&env_st);

    struct utsname name;
    if (uname(&name)) {
        fprintf(stderr, "failed to create environment.\n");
        exit(-1);
    }

    env.machine = st_store(&env_st, name.machine);
    env.version = st_store(&env_st, name.version);
    // env.system = st_store(&env_st, name.sysname);

    if (!getcwd(buf, 1024)) {
        fprintf(stderr, "failed to create environment.\n");
        exit(-1);
    }

    // env.base_path  = st_store(&env_st, buf);
    // env.logs_path  = st_store(&env_st, make_path(buf, sizeof(buf), env.base_path, "/log"));
    // env.asset_path = st_store(&env_st, make_path(buf, sizeof(buf), env.base_path, "/res"));

    print_env();
}

void free_env()
{
    st_free(&env_st);
}

void print_env()
{
    debug_print_string_table(&env_st);
    // return;
    printf("environment variables:\n");
    printf("  base_path: '%s'\n", env.base_path);
    printf("  logs_path: '%s'\n", env.logs_path);
    printf("  asset_path: '%s'\n", env.asset_path);
    printf("  machine: '%s'\n", env.machine);
    printf("  version: '%s'\n", env.version);
    printf("  system: '%s'\n\n", env.system);
}