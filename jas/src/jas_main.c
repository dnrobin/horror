#include "private.h"

#include <GLFW/glfw3.h>

FILE* logfile = NULL;

static bool jas_is_init = false;

static void process_error()
{

}

static void parse_cmdline(int argc, char const *argv[])
{

}

int jas_init(int argc, char const *argv[])
{
    parse_cmdline(argc, argv);

    atexit(jas_quit);

    jas_is_init = true;

    return 0;
}

int jas_main()
{
    
    return 0;
}

void jas_quit()
{
    if (jas_is_init) {

    }

    jas_is_init = false;
}