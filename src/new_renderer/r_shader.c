#include "shared.h"
#include "r_shader.h"

#include "glad.h"


// static GLuint compile_shader_source(GLuint type, const char **source)
// {
//     GLuint shader;
//     GLint success;

//     shader = glCreateShader(type);

//     glShaderSource(shader, 1, source, NULL);
//     glCompileShader(shader);

//     glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

//     if (success != GL_TRUE) {
//         int len;
//         GLchar infoLog[1024];
//         glGetShaderInfoLog(shader, sizeof(infoLog), &len, infoLog);
//         printf(">>> Shader Compile Error: %s\n", infoLog);
//         shader = 0;
//     }

//     return shader;
// }

// int r_create_shader_source(const char **vertex_source, const char **fragment_source)
// {
//     GLuint prog;
//     GLint success;

//     GLuint vertex_shader = compile_shader_source(GL_VERTEX_SHADER, vertex_source);
//     GLuint fragment_shader = compile_shader_source(GL_FRAGMENT_SHADER, fragment_source);

//     prog = glCreateProgram();
//     glAttachShader(prog, vertex_shader);
//     glAttachShader(prog, fragment_shader);
//     glLinkProgram(prog);

//     glGetProgramiv(prog, GL_LINK_STATUS, &success);

//     if (success != GL_TRUE) {
//         int len;
//         GLchar infoLog[1024];
//         glGetProgramInfoLog(prog, sizeof(infoLog), &len, infoLog);
//         printf(">>> Shader Compile Error: %s\n", infoLog);
//         prog = 0;
//     }

//     glDeleteShader(vertex_shader);
//     glDeleteShader(fragment_shader);

//     return prog;
// }

// void r_delete_shader(int *handle)
// {
//     if (*handle > 0) {
//         glDeleteProgram((GLuint)*handle);
//     }
//     *handle = 0;
// }
