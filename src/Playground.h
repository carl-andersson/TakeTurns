/*
 * Playground.h
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

#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <gdt/gdt_gles2.h>

#include "Sprite.h"
#include "Texture.h"

typedef struct {
	GLubyte red, green, blue, alpha;
} pixel2;

class Playground : public Sprite {
private:
	pixel *data;
	int width;
	int height;
	bool dirty;
	int xMin, Ymin, xMax, yMax;

public:
	Playground(std::string name,int w, int h){
		width = w;
		height = h;
		data = (pixel *) calloc(width*height, sizeof(pixel));
		mTexture = Texture::createTexture(name, (GLubyte *) data, width, height);
		data[1040].red = 255;
	}

	~Playground(){
		free(data);
	}

	void setPixel(int x, int y,float r,float g,float b){
		data[width*y+x].red = r;
		data[width*y+x].green = g;
		data[width*y+x].blue = b;
	}

	void updateTexture(){
		mTexture.useAs(GL_TEXTURE0);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid *) data);
	}
};

#endif //PLAYGROUND_H
