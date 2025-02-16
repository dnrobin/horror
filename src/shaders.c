#include "shared.h"
#include "shaders.h"

#include "glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static GLuint vertexShader;
static GLuint fragmentShader;
static GLuint shaderProgram;

static void _setShaderSource(const char** source, const GLenum type, int len)
{
	GLuint* shader;

	if(type == GL_VERTEX_SHADER)
		shader = &vertexShader;
	else
		shader = &fragmentShader;

	//Create a shader handle
	*shader = glCreateShader(type);

	//Send the vertex shader source code to GL
	glShaderSource(*shader, 1, (const GLchar**)source, NULL);

	//Compile the vertex shader
	glCompileShader(*shader);

	GLint isCompiled = 0;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &maxLength);
	 
		//The maxLength includes the NULL character
		GLchar* InfoLog = (GLchar*)malloc(sizeof(GLchar)*maxLength);
		glGetShaderInfoLog(*shader, maxLength, &maxLength, &InfoLog[0]);
	 
		//We don't need the shader anymore.
		glDeleteShader(*shader);
	 
		printf("\n\n-- SHADER COMPILE FAILED --\n\n%s", InfoLog);
		exit(1);
	 
		return;
	}
}

void setVertexShaderSource(const char** source, int len) {
	_setShaderSource(source, GL_VERTEX_SHADER, len);
}

void setFragmentShaderSource(const char** source, int len) {
	_setShaderSource(source, GL_FRAGMENT_SHADER, len);
}

void unloadShaderProgram() {
	glDeleteProgram(shaderProgram);
	//Don't leak shaders either.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void initShaderProgram() {
	 
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	shaderProgram = glCreateProgram();
	 
	//Attach our shaders to our program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	 
	//Link our program
	glLinkProgram(shaderProgram);
	 
	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *)&isLinked);
	if(isLinked == GL_FALSE)
	{
		GLsizei maxLength = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
	 
		//The maxLength includes the NULL character
		GLchar* linkInfoLog = (GLchar*)malloc(sizeof(GLchar) * maxLength);
		glGetProgramInfoLog(shaderProgram, maxLength+10, &maxLength, &linkInfoLog[0]);
	 
		//We don't need the program anymore.
		glDeleteProgram(shaderProgram);
		//Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	 
		//Use the infoLog as you see fit.
		printf("\n\n-- SHADER PROGRAM LINKING FAILED --\n\n%s", linkInfoLog);
		exit(1);
	 
		//Use the infoLog as you see fit.
	 
		return;
	}

	//Always detach shaders after a successful link.
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	// Tell GL to use programmable pipeline
	glUseProgram(shaderProgram);
}

int loadShaderSource(const char* filename, char** source, int *len)
{
	FILE* fp;
	size_t n;

	// get full include path to file
	const char filepath[256];
	strcpy(filepath, env_base_path);
	strcat(filepath, filename);

	// open the file for reading
	if ( !(fp = fopen(filepath, "r+")) ) {
		printf("Error loading shader source file!\n");
		return 0;
	}

	// get the file size in bytes
	fseek(fp, 0L, SEEK_END);
	*len = ftell(fp);

	// allocate memory
	*source = (char*)malloc(sizeof(char) * (*len + 2));
	if ( *source == NULL ) {
		printf("Error could not allocate memory for shader source!\n");
		return 0;
	}

	// read in the content
	fseek(fp, 0L, SEEK_SET);
	if ( !(n = fread(*source, sizeof(char), *len, fp)) ) {
		printf("Error could read input file!\n");
		return 0;
	}

	(*source)[*len] = '\0';

	// close the file
	fclose(fp);
}