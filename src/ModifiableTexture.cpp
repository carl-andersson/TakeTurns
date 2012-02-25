/*
 * ModifiableTexture.cpp
 *
 * Copyright (c) 2011 Sebastian Ärleryd
 * CopyRight (c) 2012 Carl Andersson
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

#include "ModifiableTexture.h"

const string_t ModifiableTexture::TAG = "ModifiableTexture";

ModifiableTexture::ModifiableTexture(int width, int height) {
	if(!isPowerOfTwo(width) || !isPowerOfTwo(height))
		gdt_fatal(TAG, "ModifiableTexture sizes has to be a power of 2.");

	mWidth = width;
	mHeight = height;

	//mData = new pixel[width*height];		//(pixel *) calloc(width*height, sizeof(pixel));

	mData = (pixel *) calloc(width*height, sizeof(pixel));

	mTextureID = createTexture((GLubyte *) mData, GL_RGB, width, height);
	if(mTextureID < 0) {
		gdt_fatal(TAG, "Could not create %dx%d texture.", width, height);
	}

	mDirty = false;
}

ModifiableTexture::~ModifiableTexture() {
	free(mData);
}

void ModifiableTexture::clear(GLubyte red, GLubyte green, GLubyte blue) {
	pixel p;
	p.red = red;
	p.green = green;
	p.blue = blue;

	for(int i = 0; i < mWidth * mHeight; i++) {
		memcpy(mData+i, &p, sizeof(pixel));
	}

	mDirty = true;
}

pixel ModifiableTexture::getPixel(int x, int y) {
	pixel p;

	memcpy(&p, mData + y*mWidth + x, sizeof(pixel));

	return p;
}

void ModifiableTexture::setPixel(int x, int y, GLubyte red, GLubyte green, GLubyte blue) {
	if(x < 0 || x >= mWidth || y < 0 || y >= mHeight)
		gdt_fatal(TAG, "Target coordinates (%d,%d) for setPixel is outside of the texture.", x, y);

	pixel p;
	p.red = red;
	p.green = green;
	p.blue = blue;

	mData[mWidth * y + x] = p;

	mDirty = true;
}

void ModifiableTexture::useAs(GLuint textureUnit) {
	Texture::useAs(textureUnit);

	if(mDirty) {
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *) mData);
		mDirty = false;
	}
}
