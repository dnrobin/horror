#include "shared.h"
#include "shader.h"

#include "file.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static GLuint create_shader_with_source(GLenum type, const char **source, int *len)
{
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, source, NULL);

	glCompileShader(shader);

	GLint shader_compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
	if (shader_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar info_log[1024];
		glGetShaderInfoLog(shader, 1024, &log_length, info_log);
		
		glDeleteShader(shader);
		
		LOG_ERR("\n\n-- %s SHADER COMPILATION ERROR --\n\n%s", 
			type==GL_VERTEX_SHADER?"VERTEX":"FRAGMENT", info_log);
		return 0;
	}

	return shader;
}

int r_create_shader_source(shader_t *shader, const char * const* vs_source, int vs_len, const char * const* fs_source, int fs_len)
{
	GLuint vs_handle;
	GLuint fs_handle;
	GLuint prog_handle;

	vs_handle = create_shader_with_source(GL_VERTEX_SHADER, vs_source, &vs_len);
	fs_handle = create_shader_with_source(GL_FRAGMENT_SHADER, fs_source, &fs_len);

	prog_handle = glCreateProgram();
	glAttachShader(prog_handle, vs_handle);
	glAttachShader(prog_handle, fs_handle);

	// TODO: define fixed locations here...?
	
	glLinkProgram(prog_handle);

	// don't need anymore
	glDeleteShader(vs_handle);
	glDeleteShader(fs_handle);
	 
	GLint program_linked;
	glGetProgramiv(prog_handle, GL_LINK_STATUS, &program_linked);
	if (program_linked != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar info_log[1024];
		glGetProgramInfoLog(prog_handle, 1024, &log_length, info_log);
		LOG_ERR("\n\n-- SHADER LINK ERROR --\n\n%s", info_log);

		glDeleteProgram(prog_handle);

		return 1;
	}

	shader->gl_handle = prog_handle;

	return 0;
}

int r_load_shader_files(shader_t *shader, const char *vertex_file, const char *fragment_file)
{
	const char *vs_source;
	int vs_len;
	f_read_text_file(vertex_file, &vs_source, &vs_len);

	const char *fs_source;
	int fs_len;
	f_read_text_file(fragment_file, &fs_source, &fs_len);

	return r_create_shader_source(shader, 
		&vs_source, vs_len, 
		&fs_source, fs_len
	);
}

void r_delete_shader(shader_t *shader)
{
	glDeleteProgram(shader->gl_handle);
	shader->gl_handle = 0;
}