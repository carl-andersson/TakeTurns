

#include "TextureManager.h"
#include "gdt.h"
#include "picopng.h"

const string_t TextureManager::TAG="TextureManager";


bool TextureManager::loadImagePNG(std::string filename){
	Image& im=loadedImage[filename];
	GLubyte *rawdata;
	int length;


	string_t file=&filename[0];
	resource_t res=gdt_resource_load(file);
	length=gdt_resource_length(res);
	rawdata =(GLubyte*) gdt_resource_bytes (res);

	decodePNG(im.data,im.width,im.height,rawdata,length);
	gdt_resource_unload(res);

	return true;
}
GLuint TextureManager::linkTexture(std::string filename){
	Image& im=loadedImage[filename];
	GLuint id=createTexture(&im.data[0],im.width,im.height);
	loadedResources[filename]=id;
	im.data.clear();
	return id;
}


GLuint TextureManager::getTextureId(std::string text){
	return loadedResources[text];
}


GLuint TextureManager::createTexture(std::string text,GLubyte *data,GLuint width,GLuint height){
	GLuint id=createTexture(data,width,height);
	loadedResources[text]=id;
	return id;
}

GLuint TextureManager::createTexture(GLubyte *data,GLuint width,GLuint height){

	glActiveTexture(GL_TEXTURE0+storedTextures);
	glGenTextures(1, &texture[storedTextures]);
	glBindTexture(GL_TEXTURE_2D, texture[storedTextures]);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(
		GL_TEXTURE_2D, 0,           /* target, level of detail */
		GL_RGBA,                    /* internal format */
		width,height, 0,           /* width, height, border */
		GL_RGBA, GL_UNSIGNED_BYTE,   /* external format, type */
		(void*)data                      /* pixels */
	);

	return storedTextures++;
}
