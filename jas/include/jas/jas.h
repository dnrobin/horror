#ifndef __JAS_H__
#define __JAS_H__

int jas_init(int argc, const char *argv[]);
int jas_main();
void jas_quit();

void jas_set_title(const char *title);
void jas_set_window_size(int w, int h);
void jas_set_window_fullscreen();
void jas_set_window_normal();
void jas_minimize();
void jas_maximize();
void jas_hide();
void jas_show();

void jas_pause();
void jas_resume();

#endif