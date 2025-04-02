#include "jas/jas.h"

int main(int argc, char const *argv[])
{
    if (jas_init(argc, argv)) {
        return 1;
    }

    jas_set_title("Horrified");
    jas_set_window_size(800, 600);

    return jas_main();
}