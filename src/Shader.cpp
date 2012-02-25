/*
 * Shader.cpp
 *
 * Copyright (c) 2011 Sebastian Ärleryd
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

#include "Shader.h"

const string_t Shader::TAG = "Shader";

std::map<std::string, Shader> Shader::loadedShaders;

const Shader Shader::load(std::string vertFile, std::string fragFile){
	if (loadedShaders[vertFile+fragFile].programID!=-1){
		gdt_fatal(TAG, "Shader already loaded!: %s, %s", &vertFile[0],&fragFile[0]);
	}
	void * vertRawdata,*fragRawdata;
	int vertLength,fragLength;
	resource_t vertRes,fragRes;

	vertRes=gdt_resource_load(&vertFile[0]);
	vertLength = gdt_resource_length(vertRes);
	vertRawdata = gdt_resource_bytes(vertRes);

	fragRes=gdt_resource_load(&fragFile[0]);
	fragLength = gdt_resource_length(fragRes);
	fragRawdata = gdt_resource_bytes(fragRes);

	if (vertLength == 0 || fragLength == 0){
		gdt_fatal(TAG, "Unable to load shaders!: %s, %s", &vertFile[0],&fragFile[0]);
	}

	char *vertText = (char *) malloc(vertLength+1);
	memset(vertText, 0, vertLength+1);
	memcpy(vertText, vertRawdata, vertLength);

	char *fragText = (char *) malloc(fragLength+1);
	memset(fragText, 0, fragLength+1);
	memcpy(fragText, fragRawdata, fragLength);

	GLuint vertexShader = compileShader(vertText, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragText, GL_FRAGMENT_SHADER);

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
	//gdt_log(LOG_NORMAL, TAG, "test: %s\n%s",&text.vertData[0],&text.fragData[0]);
	loadedShaders[vertFile+fragFile]=Shader(program);
	gdt_resource_unload(vertRes);
	gdt_resource_unload(fragRes);

	free(vertText);
	free(fragText);

	return Shader(program);
}

GLuint Shader::compileShader(string_t shaderCode, GLenum type){
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

const Shader Shader::get(std::string vertFile,std::string fragFile){
	return loadedShaders[vertFile+fragFile];
}

Shader::Shader() : programID(-1) {}

Shader::Shader(GLint id) : programID(id) {}

void Shader::use(){
	glUseProgram(programID);
}

GLint Shader::getAttriLoc(string_t attri){
	return glGetAttribLocation(programID, attri);
}

bool Shader::setAttribute4f(string_t attri,float f1,float f2,float f3,float f4){
	GLint attriLoc=glGetAttribLocation(programID, attri);
	if(attriLoc==-1){
		return false;
	}
	glVertexAttrib4f(attriLoc,f1,f2,f3,f4);
	return true;
}

bool Shader::setAttribute3f(string_t attri,float f1,float f2,float f3){
	GLint attriLoc=glGetAttribLocation(programID, attri);
	if(attriLoc==-1){
		return false;
	}
	glVertexAttrib3f(attriLoc,f1,f2,f3);
	return true;
}

bool Shader::setAttribute2f(string_t attri,float f1,float f2){
	GLint attriLoc=glGetAttribLocation(programID, attri);
	if(attriLoc==-1){
		return false;
	}
	glVertexAttrib2f(attriLoc,f1,f2);
	return true;
}

bool Shader::setAttribute1f(string_t attri,float f1){
	GLint attriLoc=glGetAttribLocation(programID, attri);
	if(attriLoc==-1){
		return false;
	}
	glVertexAttrib1f(attriLoc,f1);
	return true;
}

bool Shader::setAttribute4f(string_t attri,float* f){
	GLint attriLoc=glGetAttribLocation(programID, attri);
	if(attriLoc==-1){
		return false;
	}
	glVertexAttrib4f(attriLoc,f[0],f[1],f[2],f[3]);
	return true;
}

bool Shader::setAttribute3f(string_t attri,float* f){
	GLint attriLoc=glGetAttribLocation(programID, attri);
	if(attriLoc==-1){
		return false;
	}
	glVertexAttrib3f(attriLoc,f[0],f[1],f[2]);
	return true;
}

bool Shader::setAttribute2f(string_t attri,float* f){
	GLint attriLoc=glGetAttribLocation(programID, attri);
	if(attriLoc==-1){
		return false;
	}
	glVertexAttrib2f(attriLoc,f[0],f[1]);
	return true;
}

bool Shader::setAttribute1f(string_t attri,float* f){
	GLint attriLoc=glGetAttribLocation(programID, attri);
	if(attriLoc==-1){
		return false;
	}
	glVertexAttrib1f(attriLoc,f[0]);
	return true;
}

bool Shader::setUniform4f(string_t unifo,float f1,float f2,float f3,float f4){
	GLint unifoLoc=glGetUniformLocation(programID, unifo);
	if(unifoLoc==-1){
		return false;
	}
	glUniform4f(unifoLoc,f1,f2,f3,f4);
	return true;
}

bool Shader::setUniform3f(string_t unifo,float f1,float f2,float f3){
	GLint unifoLoc=glGetUniformLocation(programID, unifo);
	if(unifoLoc==-1){
		return false;
	}
	glUniform3f(unifoLoc,f1,f2,f3);
	return true;
}

bool Shader::setUniform2f(string_t unifo,float f1,float f2){
	GLint unifoLoc=glGetUniformLocation(programID, unifo);
	if(unifoLoc==-1){
		return false;
	}
	glUniform2f(unifoLoc,f1,f2);
	return true;
}

bool Shader::setUniform1f(string_t unifo,float f1){
	GLint unifoLoc=glGetUniformLocation(programID, unifo);
	if(unifoLoc==-1){
		return false;
	}
	glUniform1f(unifoLoc,f1);
	return true;
}

bool Shader::setUniform4f(string_t unifo,float *f){
	GLint unifoLoc=glGetUniformLocation(programID, unifo);
	if(unifoLoc==-1){
		return false;
	}
	glUniform4f(unifoLoc,f[1],f[2],f[3],f[4]);
	return true;
}

bool Shader::setUniform3f(string_t unifo,float *f){
	GLint unifoLoc=glGetUniformLocation(programID, unifo);
	if(unifoLoc==-1){
		return false;
	}
	glUniform3f(unifoLoc,f[1],f[2],f[3]);
	return true;
}

bool Shader::setUniform2f(string_t unifo,float *f){
	GLint unifoLoc=glGetUniformLocation(programID, unifo);
	if(unifoLoc==-1){
		return false;
	}
	glUniform2f(unifoLoc,f[1],f[2]);
	return true;
}

bool Shader::setUniform1f(string_t unifo,float *f){
	GLint unifoLoc=glGetUniformLocation(programID, unifo);
	if(unifoLoc==-1){
		return false;
	}
	glUniform1f(unifoLoc,f[1]);
	return true;
}

bool Shader::setUniform1i(string_t unifo,int i){
	GLint unifoLoc=glGetUniformLocation(programID, unifo);
	if(unifoLoc==-1){
		return false;
	}
	glUniform1i(unifoLoc,i);
	return true;
}
