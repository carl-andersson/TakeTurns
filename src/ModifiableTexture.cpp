/*
 * ModifiableTexture.cpp
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

#include "ModifiableTexture.h"

#include "GdtResource.h"

const string_t ModifiableTexture::TAG = "ModifiableTexture";

void ModifiableTexture::reloadTexture() {
	uploadAndCreateTexture();
}

ModifiableTexture::ModifiableTexture(std::string filename) {
	GdtResource res = GdtResource(filename);
	if(!res.isValid()) {
		mTextureID = -1;
		return;
	}

	std::vector<unsigned char> decodedData;
	unsigned long width;
	unsigned long height;
	int decodeStatus = decodePNG(decodedData, width, height, (const unsigned char *) res.getBytes(), res.getLength());

	mWidth = width;
	mHeight = height;

	gdt_log(LOG_NORMAL, TAG, "Decoded PNG with status %d and got data of size %d.", decodeStatus, decodedData.size());

	unsigned char *data = &decodedData[0];

	gdt_log(LOG_NORMAL, TAG, "(1)");

	mData = (pixel *) calloc(width*height, sizeof(pixel));

	gdt_log(LOG_NORMAL, TAG, "(2)");

	memcpy(mData, data, width*height*sizeof(pixel));

	gdt_log(LOG_NORMAL, TAG, "(3)");

	uploadAndCreateTexture();

	gdt_log(LOG_NORMAL, TAG, "(4)");

	sTextures.push_back(this);

	gdt_log(LOG_NORMAL, TAG, "(5)");
}

ModifiableTexture::ModifiableTexture(int width, int height) {
	if(!isPowerOfTwo(width) || !isPowerOfTwo(height))
		gdt_fatal(TAG, "ModifiableTexture sizes has to be a power of 2.");

	mWidth = width;
	mHeight = height;

	//mData = new pixel[width*height];		//(pixel *) calloc(width*height, sizeof(pixel));

	mData = (pixel *) calloc(width*height, sizeof(pixel));

	uploadAndCreateTexture();

	sTextures.push_back(this);
}

ModifiableTexture::~ModifiableTexture() {
	free(mData);
}

void ModifiableTexture::uploadAndCreateTexture() {
	mTextureID = createTexture((GLubyte *) mData, GL_RGBA, mWidth, mHeight);
	if(mTextureID < 0) {
		gdt_fatal(TAG, "Could not create %dx%d texture.", mWidth, mHeight);
	}

	mDirty = false;
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

	gdt_log(LOG_NORMAL, TAG, "ModifiableTexture %x setting pixel.", this);

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
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid *) mData);
		mDirty = false;
	}
}
