/*
 * Texture.cpp
 *
 * Copyright (c) 2012 Carl Andersson
 * Copyright (c) 2012 Sebastian Ärleryd
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

#include "Texture.h"

#include "GdtResource.h"
#include "GLUtils.h"

const string_t Texture::TAG = "Texture";

std::vector<Texture *> Texture::sTextures;
std::map<std::string, Texture *> Texture::sNameTextureMap;

image Texture::loadFilePNG(std::string filename) {
		GdtResource res = GdtResource(filename);
		if(!res.isValid()) {
			image img;
			img.textureID = -1;
			return img;
		}

		std::vector<unsigned char> decodedData;
		unsigned long width;
		unsigned long height;
		int decodeStatus = decodePNG(decodedData, width, height, (const unsigned char *) res.getBytes(), res.getLength());

		gdt_log(LOG_NORMAL, TAG, "Decoded PNG with status %d and got data of size %d.", decodeStatus, decodedData.size());

		image img;
		img.textureID = createTexture(&decodedData[0], GL_RGBA, width, height);		// Using &data[0] is a bit unclean
		img.width = width;
		img.height = height;

		return img;
}

bool Texture::isPowerOfTwo(int number) {
	if(number < 2)
		return false;

	int q = number;
	int m;

	while(true) {
		q = q / 2;
		m = q % 2;

		if(m != 0)
			return false;

		if(q <= 2)
			return true;
	}
}

GLuint Texture::createTexture(GLubyte *data, GLint format, GLuint width, GLuint height){
	if(!isPowerOfTwo(width) || !isPowerOfTwo(height))
		gdt_fatal(TAG, "Texture sizes has to be a power of 2.");

	//TODO: Also check against GL_MAX_TEXTURE_SIZE here.

	GLErrorAssert(TAG, "Got error %s from OpenGL before doing anything before loading texture of future size %dx%d.", width, height);

	GLuint newTextureID;
	glGenTextures(1, &newTextureID);

	GLErrorAssert(TAG, "Got error %s from OpenGL when generating texture pointer for future texture of size %dx%d.", width, height);

	gdt_log(LOG_NORMAL, TAG, "Got a new texture from OpenGL: %d", newTextureID);

	// Bind the newly created texture so we set some parameters and
	// upload bitmap data
	glBindTexture(GL_TEXTURE_2D, newTextureID);

	GLErrorAssert(TAG, "Got error %s from OpenGL when binding texture of future size %dx%d.", width, height);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GLErrorAssert(TAG, "Got error %s from OpenGL when setting texture parameters for texture future of size %dx%d.", width, height);

	glTexImage2D(
			GL_TEXTURE_2D, 0,						// target, level of detail
			format,										// internal format
			width, height, 0,							// width, height, border
			format, GL_UNSIGNED_BYTE,		// external format, type
			(void *) data									// pixel data
	);

	GLErrorAssert(TAG, "Got error %s from OpenGL when creating texture of size %dx%d.", width, height);

	return newTextureID;
}

void Texture::reloadTexture() {
	// Try and find this object in sNameTextureMap, if so then load that filename.
	std::map<std::string, Texture *>::iterator it;
	for(it = sNameTextureMap.begin(); it != sNameTextureMap.end(); it++) {
		if(it->second == this) {
			image img = loadFilePNG(it->first);
			mTextureID = img.textureID;
			mWidth = img.width;
			mHeight = img.height;
			break;
		}
	}
}

Texture * Texture::loadPNG(std::string filename){

	if(sNameTextureMap.count(filename) > 0){
		//gdt_fatal(TAG, "Texture already loaded: %s", filename.c_str());
		gdt_log(LOG_NORMAL, TAG, "Texture already loaded \"%s\". Returning copy.", filename.c_str());
		return sNameTextureMap[filename];
	}

	image img = loadFilePNG(filename);

	Texture *tex = new Texture(img.textureID);
	tex->mWidth = img.width;
	tex->mHeight = img.height;
	sNameTextureMap[filename] = tex;

	return tex;
}

Texture * Texture::get(std::string filename){
	return sNameTextureMap[filename];
}

void Texture::reload() {
	for(int i = 0; i < sTextures.size(); i++) {
		sTextures[i]->reloadTexture();
	}
}

/*
const Texture Texture::createTexture(std::string text, GLubyte *data, GLuint width, GLuint height){
	if(sNameTextureMap[text].mTextureID!=-1){
		gdt_fatal(TAG, "Texture already loaded!: %s", &text[0]);
	}
	GLuint id = createTexture(data, width, height);
	sNameTextureMap[text]=id;
	return Texture(id);
}
 */

Texture::Texture() : mTextureID(-1) {}

/*
Texture::Texture(GLubyte *data, GLuint width, GLuint height) {
	mTextureID = createTexture(data, width, height);
}
 */

GLuint Texture::getWidth() {
	return mWidth;
}

GLuint Texture::getHeight() {
	return mHeight;
}

bool Texture::isValid(){
	return mTextureID != -1;
}

void Texture::useAs(GLuint textureUnit) {
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

/*
const Texture Texture::createTexture(std::string text,GLubyte *data,GLuint width,GLuint height){
	if(loadedTextures[text].textureID!=-1){
		gdt_fatal(TAG, "Texture already loaded!: %s", &text[0]);
	}
	GLuint id=createTexture(data,width,height);
	loadedTextures[text]=id;
	return Texture(id);
}
 */
