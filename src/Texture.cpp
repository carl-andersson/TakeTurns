


#include "Texture.h"

const string_t Texture::TAG = "Texture";

std::map<std::string,Texture> Texture::loadedTextures;

GLuint Texture::texture[3];

std::vector<GLuint> Texture::textureIDs;

void Texture::init(){

	gdt_log(LOG_NORMAL, TAG, "Max textures: %d",3);

	for(int i=3-1;i>=0;i--)
		textureIDs.push_back(i);
	glGenTextures(3, texture);
}

const Texture Texture::loadPNG(std::string filename){

	if(loadedTextures[filename].textureID!=-1){
		gdt_fatal(TAG, "Texture already loaded!: %s", &filename[0]);
	}
	std::vector<unsigned char> data;
	GLubyte *rawdata;
	unsigned long int width,height;
	int length;

	resource_t res=gdt_resource_load(&filename[0]);
	length=gdt_resource_length(res);
	if (length == 0){
		return Texture(-1);
	}
	rawdata =(GLubyte*) gdt_resource_bytes (res);

	int status = decodePNG(data,width,height,rawdata,length);

	gdt_log(LOG_NORMAL, TAG, "decodePNG status = %d", status);
	gdt_log(LOG_NORMAL, TAG, "decodePNG returned data of length %d", data.size());

	GLuint id=createTexture(&data[0],width,height);

	loadedTextures[filename]=Texture(id);

	gdt_resource_unload(res);

	return loadedTextures[filename];
}

const Texture Texture::get(std::string filename){
	return loadedTextures[filename];
}

GLuint Texture::createTexture(GLubyte *data,GLuint width,GLuint height){
	GLuint texture;
	glGenTextures(1, &texture);

	gdt_log(LOG_NORMAL, TAG, "Got a new texture from OpenGL: %d", texture);

	//GLuint textureID = textureIDs.back();
	//textureIDs.pop_back();
	//glActiveTexture(GL_TEXTURE0+textureID);
	//glBindTexture(GL_TEXTURE_2D, texture[textureID]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	//gdt_log(LOG_NORMAL, TAG, "texture[textureID] = %d", texture[textureID]);
	//gdt_log(LOG_NORMAL, TAG, "textureID = %d", textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(
		GL_TEXTURE_2D, 0,           /* target, level of detail */
		GL_RGBA,                    /* internal format */
		width,height, 0,           /* width, height, border */
		GL_RGBA, GL_UNSIGNED_BYTE,   /* external format, type */
		(void*)data                      /* pixels */
	);

	GLenum error = glGetError();
	if(error == GL_NO_ERROR)
		gdt_log(LOG_NORMAL, TAG, "No errors from OpenGL when creating texture.");
	else
		gdt_log(LOG_ERROR, TAG, "Got error from OpenGL when creating texture.");

	//return textureID;
	return texture;
}
