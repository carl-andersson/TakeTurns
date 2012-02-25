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

#include "GdtResource.h"
#include "ModifiableTexture.h"

const char *Game::TAG = "Game";

Game::Game() {
	gdt_log(LOG_NORMAL, TAG, "Game instance created.");
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

void Game::loadAndPrintGdtResource() {
		string_t file = "/test.txt.jet";

		GdtResource res = GdtResource(file);

		int len = res.getLength();

		gdt_log(LOG_NORMAL, TAG, "Resource length is: %d", len);

		std::string bytes = std::string((string_t) res.getBytes(), len);

		gdt_log(LOG_NORMAL, TAG, "byte per byte:");
		for(int i = 0; i < bytes.size(); i++) {
			gdt_log(LOG_NORMAL, TAG, "%c", bytes.at(i));
		}
		gdt_log(LOG_NORMAL, TAG, "end");

		gdt_log(LOG_NORMAL, TAG, "Read \"%s\" from file \"%s\"", bytes.c_str(), file);
}

void Game::init() {
	gdt_log(LOG_NORMAL, TAG, "Game initialized.");

	loadAndPrintGdtResource();
}

void Game::visible(bool newSurface) {
	gdt_log(LOG_NORMAL, TAG, "Game visible.");

	int width = gdt_surface_width();
	int height = gdt_surface_height();

	gdt_log(LOG_NORMAL, TAG, "%sisible with screen size (%d, %d).",newSurface?"New v":"V", width, height);
	if (newSurface){
		//Texture::init();

		Texture *t1 = Texture::loadPNG("/scene.png");
		Shader s = Shader::load("/vert.jet","/frag.jet");

		//GLuint texture=Texture::get("/pancake.png").textureID;
		Sprite::init(s);
		mSprite = new Sprite(t1);
		mSprite->mScaleY=1;
		mSprite->mScaleX=1;

		ModifiableTexture *mt = new ModifiableTexture(64,128);
		mPlayground = new Sprite(mt);
		mPlayground->mScaleY=2;
		mPlayground->mScaleX=2;
	}

	glClearColor(0.4, 0.8, 0.4, 1);
	mScreen = Screen(width,height);
	glViewport(0, 0, width,height);
}

void Game::handleTouch(touch_type_t what, int screenX, int screenY) {
	int32_t w = gdt_surface_width();
	int32_t h = gdt_surface_height();

	//gdt_log(LOG_NORMAL, TAG, "(w,h) = (%d,%d) and (screenX,screenY) = (%d,%d)", w,h, screenX,screenY);

	float x = 1 - (float) screenX / (float) w;
	float y = 1 - (float) screenY / (float) h;

	if(x < 0)
		x = 0;
	else if(x > 1)
		x = 1;

	if(y < 0)
		y = 0;
	else if(y > 1)
		y = 1;

	ModifiableTexture *mt = (ModifiableTexture *) (mPlayground->getTexture());
	mt->setPixel((int) ((mt->getWidth() - 1)*x), (int) ((mt->getHeight() - 1)*y), 255,255,0);
}

void Game::render(){
	glClear(GL_COLOR_BUFFER_BIT);

	mPlayground->draw();
	mSprite->draw();
}

