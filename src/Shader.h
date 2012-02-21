

#ifndef SHADER_H
#define SHADER_H

#include <gdt/gdt_gles2.h>
#include <string>
#include <map>

class Shader{
private:
	static const string_t TAG;
	GLint programID;
	static std::map<std::string,Shader> loadedShaders;
	static GLuint compileShader(string_t shaderCode, GLenum type);
public:
	Shader(){
		programID=-1;
	}
	Shader(GLint id){
		programID=id;
	}

	void use(){
		glUseProgram(programID);
	}
	static const Shader load(std::string vertFile,std::string fragFile);
	static const Shader get(std::string vertFile,std::string fragFile);

	bool setUniform1i(string_t unifo,int i);

	GLint getAttriLoc(string_t);

	bool setAttribute4f(string_t attri,float f1,float f2,float f3,float f4);
	bool setAttribute3f(string_t attri,float f1,float f2,float f3);
	bool setAttribute2f(string_t attri,float f1,float f2);
	bool setAttribute1f(string_t attri,float f1);

	bool setAttribute4f(string_t attri,float* f);
	bool setAttribute3f(string_t attri,float* f);
	bool setAttribute2f(string_t attri,float* f);
	bool setAttribute1f(string_t attri,float* f);


	bool setUniform4f(string_t unifo,float f1,float f2,float f3,float f4);
	bool setUniform3f(string_t unifo,float f1,float f2,float f3);
	bool setUniform2f(string_t unifo,float f1,float f2);
	bool setUniform1f(string_t unifo,float f1);

	bool setUniform4f(string_t unifo,float *f);
	bool setUniform3f(string_t unifo,float *f);
	bool setUniform2f(string_t unifo,float *f);
	bool setUniform1f(string_t unifo,float *f);

};


#endif //SHADER_H
