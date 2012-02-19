/*
 * sshader.h
 *
 * Copyright (c) 2011 Rickard Edström
 * CopyRight (c) 2012 Carl Andersson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <unistd.h>
#include <string.h>

#include "sshader.h"

string_t TAG="StandardShader";

GLuint SHADER_VERTEX_COLOR;
GLuint SHADER_VERTEX_TRANSLATION;
GLuint SHADER_VERTEX_POSITION;
GLuint SHADER_VERTEX_SCALE;

GLuint PROGRAM_ID;

string_t vertexShaderCode = "\
precision highp float; \
\
attribute vec4 translation;  \
attribute vec4 position;\
attribute vec4 vertColor;	\
\
varying vec4 color;	\
\
void main(void) { \
	color = vertColor; \
    gl_Position = position+ vec4(translation.x, translation.y, 0, 0);\
}\
";

string_t fragmentShaderCode = "         \
precision highp float; \
\
varying vec4 color;	\
\
void main(void) {                      \
    gl_FragColor = vec4(color);   \
}                                      \
";

void sshaderInit(){
	PROGRAM_ID=linkProgram();
    SHADER_VERTEX_COLOR = glGetAttribLocation(PROGRAM_ID, "vert_color");
    SHADER_VERTEX_POSITION = glGetAttribLocation(PROGRAM_ID, "position");
    SHADER_VERTEX_SCALE = glGetAttribLocation(PROGRAM_ID, "scale");
    SHADER_VERTEX_TRANSLATION=glGetAttribLocation(PROGRAM_ID, "translation");
    gdt_log(LOG_NORMAL, TAG, "Shader created. Id:%i \nPointers: %i %i %i %i",PROGRAM_ID,SHADER_VERTEX_COLOR,SHADER_VERTEX_POSITION,SHADER_VERTEX_TRANSLATION,SHADER_VERTEX_SCALE);
    glUseProgram(PROGRAM_ID);
}

GLuint getShaderId(){
	return PROGRAM_ID;
}

GLuint linkProgram() {
    GLuint vertexShader = compileShader(vertexShaderCode, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderCode, GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
		//Get the length of the error log
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

		//Get and print the error log and then exit with error
		char *infoLog = (char *) malloc(logLength);
		glGetProgramInfoLog(program, logLength, NULL, infoLog);
		gdt_fatal(TAG, "Error linking program: %s", infoLog);
    }

    return program;
}

GLuint compileShader(string_t shaderCode, GLenum type) {
    GLuint shader = glCreateShader(type);

    int len = strlen(shaderCode);
    glShaderSource(shader, 1, &shaderCode, &len);

    glCompileShader(shader);


    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
    		//Get the length of the error log
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        //Get and print the error log and then exit with error
        char *infoLog = (char *) malloc(logLength);
        glGetShaderInfoLog(shader, logLength, NULL, infoLog);
        gdt_fatal(TAG, "Error compiling shader: %s", infoLog);
    }
    return shader;
}

void setColor3f(float r, float g,float b){
	glVertexAttrib4f(SHADER_VERTEX_COLOR, r, g,b,1.0f);
}

void setColor4f(float r, float g,float b,float a){
	glVertexAttrib4f(SHADER_VERTEX_COLOR, r, g,b,a);
}

void translate2f(float x, float y){
	glVertexAttrib4f(SHADER_VERTEX_TRANSLATION, x, y,0.0f,0.0f);
}

void setScale2f(float sx ,float sy){
	glVertexAttrib2f(SHADER_VERTEX_SCALE, sx, sy);
}


