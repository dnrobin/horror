#ifndef __R_SHADER_H__
#define __R_SHADER_H__

int r_create_shader_source(const char **vertex_source, const char **fragment_source);
void r_delete_shader(int *handle);

#endif // __R_SHADER_H__
