

#include <unistd.h>
#include <string.h>

#include "sshader.h"

string_t TAG="StandardShader";

GLuint SHADER_VERTEX_COLOR;
GLuint SHADER_VERTEX_TRANSLATION;
GLuint SHADER_VERTEX_POSITION;

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
    SHADER_VERTEX_COLOR = glGetAttribLocation(PROGRAM_ID, "color");
    SHADER_VERTEX_POSITION = glGetAttribLocation(PROGRAM_ID, "position");
    SHADER_VERTEX_TRANSLATION=glGetAttribLocation(PROGRAM_ID, "translation");
    gdt_log(LOG_NORMAL, TAG, "Shader created");
    glUseProgram(PROGRAM_ID);
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

void setColor3f(float x, float y,float z){
	glUniform4f(SHADER_VERTEX_COLOR, x, y,z,1.0f);
}

void translate2f(float x, float y){
	glUniform4f(SHADER_VERTEX_TRANSLATION, x, y,0.0f,0.0f);
}
