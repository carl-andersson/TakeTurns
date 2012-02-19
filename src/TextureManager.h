




#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <string.h>
#include <gdt/gdt_gles2.h>

typedef struct{
	std::vector<unsigned char> data;
	long unsigned int width,height;
} Image;


class TextureManager{
private:
	static const string_t TAG;


	std::map<std::string,int> loadedResources;
	std::map<std::string,Image> loadedImage;
	GLuint texture[GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS];
	GLuint storedTextures;

	GLuint createTexture(GLubyte *data,GLuint width,GLuint height);

public:

	TextureManager(){
		storedTextures=0;
	}

	bool loadImagePNG(std::string filename);

	GLuint linkTexture(std::string filename);

	GLuint getTextureId(std::string text);

	GLuint createTexture(std::string filename,GLubyte *data,GLuint width,GLuint height);

};

#endif //TEXTUREMANAGER_H
