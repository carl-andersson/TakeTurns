/*
 * Game.h
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

#ifndef Game_h
#define Game_h

#include <gdt/gdt.h>
#include "Screen.h"
#include "Sprite.h"
#include "Texture.h"
#include "Shader.h"
#include <string.h>
#include <gdt/gdt_gles2.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>


class Game {
private:
	static const char *TAG;

	bool mGameStartedOnce;

	Screen mScreen;

	Sprite *mSprite;
	Sprite *mPlayground;

	void loadAndPrintResource();
	void loadAndPrintGdtResource();

public:
	Game();

	//gdt events
	void init();
	void visible(bool newSurface);
	void handleTouch(touch_type_t what, int screenX, int screenY);

	void render();
};

#endif //Game_h
