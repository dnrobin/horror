#ifndef __MAZE_GAME_CONTROLS_H__
#define __MAZE_GAME_CONTROLS_H__

/* GLUT callbacks to handle game controls */
void handleSpecialKeyDown(int key, int x, int y);
void handleKeyDown(unsigned char key, int x, int y);
void handleKeyUp(unsigned char key, int x, int y);
void handleMouseDown(int button, int state, int x, int y);
void handleMouseMove(const int x, const int y);

void c_init_controls();
void c_update_controls();

#endif