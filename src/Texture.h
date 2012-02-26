/*
 * Texture.h
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

#ifndef TEXTURE_H
#define TEXTURE_H

#include <gdt/gdt_gles2.h>
#include <string>
#include <vector>
#include <map>
#include "picopng.h"

typedef struct {
	GLuint textureID;
	int32_t width;
	int32_t height;
} image;

class Texture{
private:
	static const string_t TAG;

	static std::map<std::string, Texture *> sNameTextureMap;
	//static std::vector<GLuint> textureIDs;
	//static GLuint texture[];

	Texture(GLint id) : mTextureID(id) {
		sTextures.push_back(this);
	}

	static image loadFilePNG(std::string filename);

protected:
	static std::vector<Texture *> sTextures;

	GLint mTextureID;
	GLuint mWidth;
	GLuint mHeight;

	static bool isPowerOfTwo(int number);

	static GLuint createTexture(GLubyte *data, GLint format, GLuint width, GLuint height);

	virtual void reloadTexture();

public:
	//static void init();
	//static const Texture createTexture(std::string text, GLubyte *data, GLuint width, GLuint height);
	static Texture * loadPNG(std::string filename);
	static Texture * get(std::string filename);
	static void reload();

	Texture();
	//Texture(GLubyte *data, GLuint width, GLuint height);

	GLuint getWidth();
	GLuint getHeight();

	bool isValid();
	virtual void useAs(GLuint textureUnit);
};

#endif //TEXTURE_H
