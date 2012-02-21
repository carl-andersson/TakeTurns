




#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <map>
#include <string>
#include <string.h>
#include <gdt/gdt_gles2.h>

typedef struct{
	std::string vertData;
	std::string fragData;
	long unsigned int vertLength,fragLength;
} TextData;

class ShaderManager{
private:

	static const string_t TAG;
	std::map<std::string,TextData> loadedTextData;
	std::map<std::string,int> loadedShaders;
	GLuint currentProgram;
public:
	bool loadShaderProgram(std::string vert,std::string frag);

	//GLuint getShaderProgram(std::string vert,std::string frag);
};





#endif //SHADERMANAGER_H
