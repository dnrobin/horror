#include "shared.h"
#include "shaders.h"

#include "file.h"
#include "glad.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int create_shader_with_source(GLuint *shader, GLenum type, const char** source, size_t len)
{
	*shader = glCreateShader(type);
	glShaderSource(*shader, 1, (const char**)source, len);
	glCompileShader(*shader);

	GLint shader_compiled;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &shader_compiled);
	if (shader_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar info_log[1024];
		glGetShaderInfoLog(*shader, 1024, &log_length, info_log);
		
		glDeleteShader(*shader);
		
		ERROR_RET("\n\n-- %s SHADER COMPILATION ERROR --\n\n%s", 
			type==GL_VERTEX_SHADER?"VERTEX":"FRAGMENT", info_log)
	}

	return STATUS_SUCCESS;
}

int r_create_shader_source(GLuint *program, const char *vertex_shader_source, const char *fragment_shader_source)
{
	GLuint vertex_shader;

	if (STATUS_FAILURE == create_shader_with_source(&vertex_shader, GL_VERTEX_SHADER, &vertex_shader_source, NULL)) {
		return STATUS_FAILURE;
	}

	GLuint fragment_shader;

	if (STATUS_FAILURE == create_shader_with_source(&fragment_shader, GL_FRAGMENT_SHADER, &fragment_shader_source, NULL)) {
		return STATUS_FAILURE;
	}

	*program = glCreateProgram();
	glAttachShader(*program, vertex_shader);
	glAttachShader(*program, fragment_shader);
	
	glLinkProgram(*program);
	 
	GLint program_linked;
	glGetProgramiv(*program, GL_LINK_STATUS, &program_linked);
	if (program_linked != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar info_log[1024];
		glGetProgramInfoLog(*program, 1024, &log_length, info_log);

		glDeleteProgram(*program);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		
		ERROR_RET("\n\n-- SHADER LINK ERROR --\n\n%s", info_log)
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return STATUS_SUCCESS;
}

int r_load_shader_files(GLuint *program, const char *vertex_file, const char *fragment_file)
{
	char *vertex_shader_source;
	int vertex_shader_length;

	char vertex_full_file[1024];
	strcpy(vertex_full_file, env_base_path);
	strcat(vertex_full_file, vertex_file);

	f_read_text_file(vertex_full_file, &vertex_shader_source, &vertex_shader_length);

	char *fragment_shader_source;
	int fragment_shader_length;

	char fragment_full_file[1024];
	strcpy(fragment_full_file, env_base_path);
	strcat(fragment_full_file, fragment_file);

	f_read_text_file(fragment_full_file, &fragment_shader_source, &fragment_shader_length);

	return r_load_shader_source(program, vertex_shader_source, fragment_shader_source);
}

void r_delete_shader(GLuint program)
{
	glDeleteProgram(program);
}