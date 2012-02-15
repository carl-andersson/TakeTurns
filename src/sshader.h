
#ifndef SSHADER_H
#define SSHADER_H

#include "gdt_gles2.h"



void sshaderInit();

GLuint linkProgram();
GLuint compileShader(string_t shaderCode, GLenum type);

void translate2f(float, float);
void setColor3f(float,float,float);


#endif //SSHADER_H
