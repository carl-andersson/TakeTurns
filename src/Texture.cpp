/*
 * Texture.cpp
 *
 * CopyRight (c) 2012 Carl Andersson
 * CopyRight (c) 2012 Sebastian Ärleryd
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

const string_t Texture::TAG = "Texture";

std::map<std::string, Texture *> Texture::sLoadedTextures;

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

	GLuint newTextureID;
	glGenTextures(1, &newTextureID);

	gdt_log(LOG_NORMAL, TAG, "Got a new texture from OpenGL: %d", newTextureID);

	// Bind the newly created texture so we set some parameters and
	// upload bitmap data
	glBindTexture(GL_TEXTURE_2D, newTextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(
			GL_TEXTURE_2D, 0,						// target, level of detail
			format,										// internal format
			width, height, 0,							// width, height, border
			format, GL_UNSIGNED_BYTE,		// external format, type
			(void *) data									// pixel data
	);

	GLenum error = glGetError();
	if(error == GL_NO_ERROR)
		gdt_log(LOG_NORMAL, TAG, "No errors from OpenGL when creating texture.");
	else {
		string_t error_string = gdt_gl_error_string(error);
		gdt_fatal(TAG, "Got error from OpenGL when creating texture: %s.", error_string);
		//glDeleteTextures(1, &newTextureID);
		//return -1;
	}

	return newTextureID;
}

Texture * Texture::loadPNG(std::string filename){

	if(sLoadedTextures.count(filename) > 0){
		//gdt_fatal(TAG, "Texture already loaded: %s", filename.c_str());
		gdt_log(LOG_NORMAL, TAG, "Texture already loaded \"%s\". Returning copy.", filename.c_str());
		return sLoadedTextures[filename];
	}

	GdtResource res = GdtResource(filename);
	if(!res.isValid())
		return NULL;

	std::vector<unsigned char> decodedData;
	unsigned long width;
	unsigned long height;
	int decodeStatus = decodePNG(decodedData, width, height, (const unsigned char *) res.getBytes(), res.getLength());

	gdt_log(LOG_NORMAL, TAG, "Decoded PNG with status %d and got data of size %d.", decodeStatus, decodedData.size());

	GLuint newTextureID = createTexture(&decodedData[0], GL_RGBA, width, height);		// Using &data[0] is a bit unclean

	Texture *tex = new Texture(newTextureID);
	tex->mWidth = width;
	tex->mHeight = height;
	sLoadedTextures[filename] = tex;

	return tex;
}

Texture * Texture::get(std::string filename){
	return sLoadedTextures[filename];
}

/*
const Texture Texture::createTexture(std::string text, GLubyte *data, GLuint width, GLuint height){
	if(sLoadedTextures[text].mTextureID!=-1){
		gdt_fatal(TAG, "Texture already loaded!: %s", &text[0]);
	}
	GLuint id = createTexture(data, width, height);
	sLoadedTextures[text]=id;
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
