/*
 * Game.cpp
 *
 * Copyright (c) 2011 Sebastian Ärleryd
 * CopyRight (c) 2012 Carl Andersson
 *
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

#include "Game.h"
#include "gdt_gles2.h"
#include "Screen.h"
#include "sshader.h"
#include "Sprite.h"
#include <stdlib.h>
#include <vector>



char *Game::TAG = "Game";

Game::Game() {

	gdt_log(LOG_NORMAL, TAG, "Game instance created.");
}

void Game::init() {
	gdt_log(LOG_NORMAL, TAG, "Game initialized.");
	mTM.loadImagePNG("/pancake.png");
	mSM.loadShaderProgram("/vert.jet","/frag.jet");

}

void Game::visible(bool newSurface, int width, int height) {
	gdt_log(LOG_NORMAL, TAG, "Visible with screen size (%d, %d).", width, height);
	if (newSurface){
		GLuint texture=mTM.linkTexture("/pancake.png");
		sprites=new Sprite(texture);
		sprites->mScaleY=2;
		sprites->mScaleX=2;
		sshaderInit();
		Sprite::init(getShaderId());
		glClearColor(0.4, 0.8, 0.4, 1);
	}
	mScreen = Screen(width,height);
	glViewport(0, 0, width,height);
}

void Game::render(){
	glClear(GL_COLOR_BUFFER_BIT);

	sprites->draw();

}


