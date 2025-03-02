#include "shared.h"
#include "shader.h"

#include "file.h"
#include "glad.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int create_shader_with_source(GLuint *shader, GLenum type, const char* source, int *len)
{
	GLuint handle = 0;
	const char *src = &source;

	handle = glCreateShader(type);

	glShaderSource(handle, 1, &src, len);

	glCompileShader(handle);

	GLint shader_compiled;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &shader_compiled);
	if (shader_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar info_log[1024];
		glGetShaderInfoLog(handle, 1024, &log_length, info_log);
		
		glDeleteShader(handle);
		
		ERROR_RET("\n\n-- %s SHADER COMPILATION ERROR --\n\n%s", 
			type==GL_VERTEX_SHADER?"VERTEX":"FRAGMENT", info_log)
	}

	*shader = handle;

	return STATUS_SUCCESS;
}

int r_create_shader_source(shader_t *shader, const char *vertex_shader_source, int vertex_shader_length, const char *fragment_shader_source, int fragment_shader_length)
{
	GLuint vertex_shader;

	if (STATUS_FAILURE == create_shader_with_source(&vertex_shader, GL_VERTEX_SHADER, vertex_shader_source, &vertex_shader_length)) {
		return STATUS_FAILURE;
	}

	GLuint fragment_shader;

	if (STATUS_FAILURE == create_shader_with_source(&fragment_shader, GL_FRAGMENT_SHADER, fragment_shader_source, &fragment_shader_length)) {
		return STATUS_FAILURE;
	}

	shader->gl_handle = glCreateProgram();
	glAttachShader(shader->gl_handle, vertex_shader);
	glAttachShader(shader->gl_handle, fragment_shader);
	
	glLinkProgram(shader->gl_handle);
	 
	GLint program_linked;
	glGetProgramiv(shader->gl_handle, GL_LINK_STATUS, &program_linked);
	if (program_linked != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar info_log[1024];
		glGetProgramInfoLog(shader->gl_handle, 1024, &log_length, info_log);

		glDeleteProgram(shader->gl_handle);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		
		ERROR_RET("\n\n-- SHADER LINK ERROR --\n\n%s", info_log)
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return STATUS_SUCCESS;
}

int r_load_shader_files(shader_t *shader, const char *vertex_file, const char *fragment_file)
{
	char *vertex_shader_source;
	int vertex_shader_length;

	char vertex_full_file[1024];
	strcpy(vertex_full_file, env_base_path);
	strcat(vertex_full_file, vertex_file);

	f_read_text_file(vertex_full_file, vertex_shader_source, &vertex_shader_length);

	char *fragment_shader_source;
	int fragment_shader_length;

	char fragment_full_file[1024];
	strcpy(fragment_full_file, env_base_path);
	strcat(fragment_full_file, fragment_file);

	f_read_text_file(fragment_full_file, fragment_shader_source, &fragment_shader_length);

	return r_create_shader_source(shader, vertex_shader_source, vertex_shader_length, fragment_shader_source, fragment_shader_length);
}

void r_delete_shader(shader_t *shader)
{
	glDeleteProgram(shader->gl_handle);
}