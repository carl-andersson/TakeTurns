/*
 * Sprite.cpp
 *
 * CopyRight (c) 2012 Carl Andersson
 * Copyright (c) 2011 Rickard Edström
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

#include "Sprite.h"

#include "GLUtils.h"

const Vertex Sprite::vertices[] = {
		{-0.5,0.5,0,0},
		{-0.5, -0.5,0,1},
		{0.5, 0.5,1,0},
		{0.5, -0.5,1,1}
};

const GLubyte Sprite::indices[] = { 0, 1, 2, 3 };

const string_t Sprite::TAG = "Sprite";

GLuint Sprite::vertexBuf;
GLuint Sprite::indexBuf;

void Sprite::init(Shader *shader) {
	Node::sShader = shader;
	GLuint positionAttrib = shader->getAttriLoc("position");
	GLuint textcoordsAttrib = shader->getAttriLoc("vert_textureCoords");

	GLErrorAssert(TAG, "Got error %s from OpenGL when getting attribute positions from shader.");

	glGenBuffers(1, &Sprite::vertexBuf);

	GLErrorAssert(TAG, "Got error %s from OpenGL when generating buffers for sprite vertices.");

	//gdt_log(LOG_NORMAL, TAG, "vertexBuf:%d",vertexBuf);
	glBindBuffer(GL_ARRAY_BUFFER, Sprite::vertexBuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLErrorAssert(TAG, "Got error %s from OpenGL when binding vertex buffer and uploading buffer data.");

	glGenBuffers(1, &Sprite::indexBuf);
	//gdt_log(LOG_NORMAL, TAG, "indexBuf:%d",indexBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Sprite::indexBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(positionAttrib);
	glEnableVertexAttribArray(textcoordsAttrib);
	glVertexAttribPointer(positionAttrib, 2, GL_FLOAT, GL_FALSE,sizeof(Vertex), 0);
	glVertexAttribPointer(textcoordsAttrib, 2, GL_FLOAT, GL_FALSE,sizeof(Vertex), (void*)(2*sizeof(GL_FLOAT)));
}

Texture * Sprite::getTexture() {
	return mTexture;
}

void Sprite::selfDraw() {
	mTexture->useAs(GL_TEXTURE0);
	//mTexture2.useAs(GL_TEXTURE1);
	sShader->use();

	glBindBuffer(GL_ARRAY_BUFFER, Sprite::vertexBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Sprite::indexBuf);

	sShader->setUniform1i("texture1", GL_TEXTURE0);
	//sShader.setUniform1i("texture2", GL_TEXTURE1-GL_TEXTURE0);

	/*
	if(sShader.setUniform1i("texture1", GL_TEXTURE0))
		gdt_log(LOG_NORMAL, TAG, "setting texture1 worked.");
	else
		gdt_log(LOG_NORMAL, TAG, "setting texture1 FAILED.");
	if(sShader.setUniform1i("texture2", GL_TEXTURE1-GL_TEXTURE0))
		gdt_log(LOG_NORMAL, TAG, "setting texture2 worked.");
	else
		gdt_log(LOG_NORMAL, TAG, "setting texture2 FAILED.");
	*/

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, NULL);
}

