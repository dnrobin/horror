#include "shared.h"
#include "input.h"

static struct { int x; int y; } mouse_position = {0};
static bool keys[MAX_KEYS] = {0};
static bool btns[GLFW_MOUSE_BUTTON_LAST] = {0};

void i_handle_mouse_position_change(int x, int y)
{
    mouse_position.x = x;
    mouse_position.y = y;
}

void i_get_mouse_coordinates(int *x, int *y)
{
    *x = mouse_position.x;
    *y = mouse_position.y;
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