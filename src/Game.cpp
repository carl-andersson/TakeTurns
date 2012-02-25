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

const char *Game::TAG = "Game";

Game::Game() {
	gdt_log(LOG_NORMAL, TAG, "Game instance created.");
	x=50;
	y=50;
	angle=0;
}

void Game::loadAndPrintResource() {
		string_t file = "/test.txt.jet";
		resource_t res = gdt_resource_load(file);

		gdt_log(LOG_NORMAL, TAG, "Resource is: %d", res);

		int len = gdt_resource_length(res);

		gdt_log(LOG_NORMAL, TAG, "Resource length is: %d", len);

		void *bytes = gdt_resource_bytes(res);
		char *text = (char *) malloc(len+1);
		memset(text, 0, len+1);
		memcpy(text, bytes, len);

		gdt_log(LOG_NORMAL, TAG, "byte per byte:");
		for(int i = 0; i < len; i++) {
			gdt_log(LOG_NORMAL, TAG, "%c", text[i]);
		}
		gdt_log(LOG_NORMAL, TAG, "end");

		gdt_log(LOG_NORMAL, TAG, "Read \"%s\" from file \"%s\"", text, file);

		gdt_resource_unload(res);

		len = gdt_resource_length(res);
		gdt_log(LOG_NORMAL, TAG, "Resource length is: %d", len);
}

void Game::init() {
	gdt_log(LOG_NORMAL, TAG, "Game initialized.");
}

void Game::visible(bool newSurface) {
	gdt_log(LOG_NORMAL, TAG, "Game visible.");



	int width = gdt_surface_width();
	int height = gdt_surface_height();

	gdt_log(LOG_NORMAL, TAG, "%sisible with screen size (%d, %d).",newSurface?"New v":"V", width, height);
	if (newSurface){
		loadAndPrintResource();

		Texture::init();

		Texture t=Texture::loadPNG("/pancake.png");
		Shader s=Shader::load("/vert.jet","/frag.jet");

		//GLuint texture=Texture::get("/pancake.png").textureID;
		Sprite::init(s);
		sprites=new Sprite(t);
		playG=new Playground("game",100,100);
		playG->mScaleY=2;
		playG->mScaleX=2;
		sprites->mScaleY=1;
		sprites->mScaleX=1;
		//sshaderInit();


		glClearColor(0.4, 0.8, 0.4, 1);
	}
	glClearColor(0.4, 0.8, 0.4, 1);
	mScreen = Screen(width,height);
	glViewport(0, 0, width,height);
}

void Game::handleTouch(touch_type_t what, int screenX, int screenY){
	gdt_log(LOG_NORMAL, TAG, "Touch!");
	//playG->setPixel(99-(int)(screenX/(float)mScreen.mWidth*100),99-(int)(screenY/(float)mScreen.mHeight*100),255,255,0);
	if (screenX<100){
		angle-=0.05;
	}
	if (screenX>mScreen.mWidth-100){
		angle+=0.05;
	}
}

void Game::render(){
	gdt_log(LOG_NORMAL, TAG, "DRAW!");
    x=x+sin(angle)*0.2;
	y=y+cos(angle)*0.2;
	playG->setPixel(x,y,0,255,0);
	//playG->drawLine(x,y,x2,y2);
	glClear(GL_COLOR_BUFFER_BIT);
	playG->updateTexture();

	playG->draw();
	//sprites->draw();


}

