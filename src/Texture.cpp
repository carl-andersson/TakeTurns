


#include "Texture.h"


const string_t Texture::TAG = "Texture";

std::map<std::string,Texture> Texture::loadedTextures;

GLuint Texture::texture[GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS];

std::vector<GLuint> Texture::textureIDs;

void Texture::init(){

	gdt_log(LOG_NORMAL, TAG, "Max textures: %d",GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

	for(int i=GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS-1;i>=0;i--)
		textureIDs.push_back(i);
	glGenTextures(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, texture);
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
	if (length==0){
		return Texture(-1);
	}
	rawdata =(GLubyte*) gdt_resource_bytes (res);

	decodePNG(data,width,height,rawdata,length);

	GLuint id=createTexture(&data[0],width,height);


	loadedTextures[filename]=Texture(id);

	gdt_resource_unload(res);

	return loadedTextures[filename];
}

const Texture Texture::get(std::string filename){
	return loadedTextures[filename];
}

GLuint Texture::createTexture(GLubyte *data,GLuint width,GLuint height){
	GLuint textureID = textureIDs.back();
	textureIDs.pop_back();
	glActiveTexture(GL_TEXTURE0+textureID);
	glBindTexture(GL_TEXTURE_2D, texture[textureID]);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(
		GL_TEXTURE_2D, 0,           /* target, level of detail */
		GL_RGBA,                    /* internal format */
		width,height, 0,           /* width, height, border */
		GL_RGBA, GL_UNSIGNED_BYTE,   /* external format, type */
		(void*)data                      /* pixels */
	);

	return textureID;
}
