

#ifndef SHADER_H
#define SHADER_H
#include <gdt/gdt_gles2.h>
#include <map>

class Shader{
private:
	static const string_t TAG;
	GLuint programID;
	static std::map<std::string,GLuint> loadedShaders;
public:
	static void load(std::string vertFile,std::string::fragFile);

};


#endif //SHADER_H
