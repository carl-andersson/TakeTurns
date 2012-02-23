/*
 * Node.cpp
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

#include "Node.h"

const string_t Node::TAG = "Node";

Shader Node::sShader;

Node::Node() {
	//mShader=sShader;
	mChildren = std::vector<Node*>();
	mX = 0;
	mY = 0;
	mScaleX = 1;
	mScaleY = 1;
	mColorGreen = 1;
	mColorBlue = 1;
	mColorRed = 1;
	mColorAlpha = 1;
}

void Node::draw() {
	sShader.setAttribute4f("translation",mX,mY,0,0);
	sShader.setAttribute4f("vert_color",mColorRed,mColorGreen,mColorBlue,mColorAlpha);
	sShader.setAttribute2f("scale",mScaleX,mScaleY);

	selfDraw();

	for (int i = 0; i < mChildren.size(); i++){
		mChildren[i]->draw();
	}

	sShader.setAttribute4f("translation",-mX,-mY,0,0);
}
