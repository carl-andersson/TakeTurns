



#ifndef TEXTURE_H
#define TEXTURE_H

#include <gdt/gdt_gles2.h>
#include <string>
#include <vector>
#include <map>
#include "picopng.h"


class Texture{
private:

	static const string_t TAG;
	static std::map<std::string,Texture> loadedTextures;
	static std::vector<GLuint> textureIDs;
	static GLuint texture[];
	Texture(GLint id){
		textureID=id;
	}
	static GLuint createTexture(GLubyte *data,GLuint width,GLuint height);
public:
	Texture(){
		textureID=-1;
	}
	static void init();
	GLint textureID;
	bool isValid(){
		if (textureID==-1)
			return false;
		else{
			return true;
		}
	}

	static const Texture loadPNG(std::string filename);
	static const Texture get(std::string filename);

};



#endif //TEXTURE_H
