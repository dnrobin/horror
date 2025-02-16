#include "shared.h"
#include "input.h"

#include <GLFW/glfw3.h>

static bool keys[GLFW_KEY_LAST] = {0};
static bool btns[GLFW_MOUSE_BUTTON_LAST] = {0};
static double mouse_x, mouse_y;

bool get_key(int key)
{
    if (key < 0 || key >= GLFW_KEY_LAST) {
        return false;
    }

    return keys[key];
}

bool get_mouse_button(int button)
{
    if (button < 0 || button >= GLFW_MOUSE_BUTTON_LAST) {
        return false;
    }

    return btns[button];
}

void get_mouse_pos(double *x, double *y)
{
    *x = mouse_x;
    *y = mouse_y;
}

void i_handle_key_down(int key, int modifiers)
{
	keys[key] = true;
}

void i_handle_key_up(int key, int modifiers)
{
	keys[key] = false;
}

void i_handle_mouse_button_down(int button)
{
    btns[button] = true;
}

void i_handle_mouse_button_up(int button)
{
    btns[button] = false;
}

void i_handle_mouse_motion(double x, double y)
{
    mouse_x = x;
    mouse_y = y;
}
