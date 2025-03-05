#include "shared.h"
#include "shader.h"

#include "file.h"
#include "glad.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int create_shader_with_source(GLuint *shader, GLenum type, const char* const* source, int *len)
{
	GLuint handle = 0;

	handle = glCreateShader(type);

	glShaderSource(handle, 1, source, NULL);

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

int r_create_shader_source(shader_t *shader, const char * const* vertex_shader_source, int vertex_shader_length, const char * const* fragment_shader_source, int fragment_shader_length)
{
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint shader_program;

	if (STATUS_FAILURE == create_shader_with_source(&vertex_shader, GL_VERTEX_SHADER, vertex_shader_source, &vertex_shader_length)) {
		return STATUS_FAILURE;
	}

	if (STATUS_FAILURE == create_shader_with_source(&fragment_shader, GL_FRAGMENT_SHADER, fragment_shader_source, &fragment_shader_length)) {
		return STATUS_FAILURE;
	}

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);

	// TODO: define fixed locations here...

	glLinkProgram(shader_program);
	 
	GLint program_linked;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &program_linked);
	if (program_linked != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar info_log[1024];
		glGetProgramInfoLog(shader_program, 1024, &log_length, info_log);

		glDeleteProgram(shader_program);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		
		ERROR_RET("\n\n-- SHADER LINK ERROR --\n\n%s", info_log)
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	shader->gl_handle = shader_program;

	return STATUS_SUCCESS;
}

int r_load_shader_files(shader_t *shader, const char *vertex_file, const char *fragment_file)
{
	char *vertex_shader_source;
	int vertex_shader_length;

	f_read_text_file(vertex_file, &vertex_shader_source, &vertex_shader_length);

	// CA PEUT PAS ETRE ZERO!!!!
	printf("%x\n",vertex_shader_source);

	printf("~~~\n%s\n~~~\n", vertex_shader_source);

	char *fragment_shader_source;
	int fragment_shader_length;

	f_read_text_file(fragment_file, &fragment_shader_source, &fragment_shader_length);

	printf("~~~\n%s\n~~~\n", fragment_shader_source);

	return r_create_shader_source(shader, &vertex_shader_source, vertex_shader_length, &fragment_shader_source, fragment_shader_length);
}

void r_delete_shader(shader_t *shader)
{
	glDeleteProgram(shader->gl_handle);
}