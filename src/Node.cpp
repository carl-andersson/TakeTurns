/*
 * Node.cpp
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

#include "Node.h"

const string_t Node::TAG = "Node";

Shader* Node::sShader;

void Node::removeChild(Node *child) {
	std::vector<Node *>::iterator it;
	for(it = mChildren.begin(); it != mChildren.end(); it++) {
		if( *it == child) {
			mChildren.erase(it);
			break;
		}
	}
}

Node::Node() {
	mChildren = std::vector<Node*>();

	//for (int i=0;i<4;i++)
	//	gdt_log(LOG_NORMAL, TAG, "Mat: %f %f %f %f",mModelMatrix[0][i],mModelMatrix[1][i],mModelMatrix[2][i],mModelMatrix[3][i]);

	mChildrenSortDirty = false;

	mX = 0;
	mY = 0;
	mRotation=0;
	mScaleX = 1;
	mScaleY = 1;
	mColorGreen = 1;
	mColorBlue = 1;
	mColorRed = 1;
	mColorAlpha = 1;

}

Node::~Node() {
	setParent(NULL);

	for(int i = 0; i < mChildren.size(); i++) {
		mChildren[i]->setParent(NULL);
	}
}

void Node::selfDraw() {
	//gdt_log(LOG_NORMAL, TAG, "selfDraw");
}

void Node::move(float x,float y){
	mModelMatrix[3]=glm::vec4(x,y,0,1);
}


void Node::addChild(Node* n){
	mChildren.push_back(n);
}

void Node::draw() {

	pushMatrix();


	scale(mScaleX,mScaleY);
	translate(mX,mY);
	rotate(mRotation);


	sShader->use();
	//for (int i=0;i<4;i++)
	//	gdt_log(LOG_NORMAL, TAG, "Mat: %f %f %f %f",getCurrentMatrix()[0][i],getCurrentMatrix()[1][i],getCurrentMatrix()[2][i],getCurrentMatrix()[3][i]);

	if (!sShader->setUniformMat4f("modelViewMatrix",getCurrentMatrix())){
		gdt_log(LOG_NORMAL, TAG, "ERROR");
	}

	sShader->setAttribute4f("vert_color",mColorRed,mColorGreen,mColorBlue,mColorAlpha);


	if(mChildrenSortDirty) {
		sort(mChildren.begin(), mChildren.end(), NodeSorter());
	}

	// Draw the children in order according to their mLayer variable. Children with mLayer < 0 are drawn before this node.
	int i;
	for(i = 0; i < mChildren.size() && mChildren[i]->mLayer < 0; i++) {
		mChildren[i]->draw();
	}

	selfDraw();

	// Draw the rest of the children, those with mLayer >= 0 and that will appear above the this node.
	for (; i < mChildren.size(); i++){
		mChildren[i]->draw();
	}

	popMatrix();
}

void Node::setLayer(int layer) {
	if(layer != mLayer) {
		mLayer = layer;
		mParent->mChildrenSortDirty = true;
	}
}


void Node::setParent(Node *parent) {
	if(parent != mParent) {
		mParent->removeChild(this);
	}

	mParent = parent;
	if(parent != NULL)
		//TODO: Add child?
		mParent->mChildrenSortDirty = true;
}

