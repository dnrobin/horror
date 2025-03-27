#ifndef __JAS_ENV_H__
#define __JAS_ENV_H__

struct 
env_s {
    const char          *base_path;
    const char          *logs_path;
    const char          *asset_path;
    const char          *machine;
    const char          *version;
    const char          *system;
} *penv;

void j_init_env(int argc, const char *argv[]);
void j_free_env();
void j_print_env();

#endif