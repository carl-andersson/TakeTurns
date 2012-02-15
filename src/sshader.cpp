

#include <unistd.h>
#include <string.h>
#include "gdt_gles2.h"
#include "sshader.h"

string_t TAG="StandardShader";

GLuint SHADER_VERTEX_COLOR;
GLuint SHADER_VERTEX_TRANSLATION;
GLuint SHADER_VERTEX_POSITION;

GLuint PROGRAM_ID;

string_t vertexShaderCode = "\
attribute vec4 translation;  \
attribute vec4 position;\
attribute vec4 color;\
varying vec4 color;	\
void main(void) { \
    gl_Position = position+ vec4(translation.x, translation.y, 0, 0);\
	gl_Color=color;\
}\
";

string_t fragmentShaderCode = "         \
varying vec4 color;	\
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
        gdt_fatal(TAG, "Error linking program");
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
        gdt_fatal(TAG, "Error compiling shader");
    }
    return shader;
}

void setColor3f(float x, float y,float z){
	glUniform4f(SHADER_VERTEX_COLOR, x, y,z,1.0f);
}

void translate2f(float x, float y){
	glUniform4f(SHADER_VERTEX_TRANSLATION, x, y,0.0f,0.0f);
}
