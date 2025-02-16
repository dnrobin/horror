#ifndef SHADERS_H
#define SHADERS_H

void setVertexShaderSource(const char** source, int len);
void setFragmentShaderSource(const char** source, int len);
void unloadShaderProgram();
void initShaderProgram();
int loadShaderSource(const char* filename, char** source, int *len);

#endif