/*
 * Sprite.h
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

#ifndef SPRITE_H
#define SPRITE_H

#include <string.h>

#include <gdt/gdt_gles2.h>
#include <gdt/gdt.h>

#include "Node.h"
#include "Texture.h"

typedef struct {
	float v[2];
	float tc[2];
} Vertex;

class Sprite : public Node {
private:
	static const string_t TAG;

	static GLuint vertexBuf;
	static GLuint indexBuf;
	static const Vertex vertices[];
	//static const GLfloat v[];
	static const GLubyte indices[];

protected:
	Texture *mTexture;
	//Texture mTexture2;

public:
	static void init(Shader);

	Sprite() {}
	//Sprite(Texture texture1, Texture texture2) : mTexture(texture1), mTexture2(texture2) {}
	Sprite(Texture *texture) : mTexture(texture) {};

	Texture * getTexture();

	void selfDraw();
};

#endif //SPRITE_H
