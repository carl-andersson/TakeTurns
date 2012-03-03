/*
 * GLUtils.cpp
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

#include "GLUtils.h"
#include <math.h>

namespace NS{
	namespace{
		std::stack<glm::mat4> sMat=std::stack<glm::mat4>();
		glm::mat4 sCurrent=glm::mat4(1.0f);

		const double PI = 3.14159265358979;
		const double PI_OVER_180 =  PI/180;
	}
}

void pushMatrix(){
	NS::sMat.push(NS::sCurrent);
}

void popMatrix(){
	NS::sCurrent=NS::sMat.top();
	NS::sMat.pop();
}

void translate(float x,float y){
	glm::mat4 trans=glm::mat4(1.0);
	trans[3]=glm::vec4(x,y,0,1);
	NS::sCurrent=NS::sCurrent*trans;

}

void rotate(float angle){
	glm::mat4 rot=glm::mat4(1.0);
	float cosA=cos(angle*NS::PI_OVER_180);
	float sinA=sin(angle*NS::PI_OVER_180);
	rot[0]=glm::vec4(cosA,-sinA,0,0);
	rot[1]=glm::vec4(sinA,cosA,0,0);
	NS::sCurrent=NS::sCurrent*rot;
}

void scale(float sX,float sY){
	glm::mat4 scale=glm::mat4(1.0);
	scale[0]=glm::vec4(sX,0,0,0);
	scale[1]=glm::vec4(0,sY,0,0);
	NS::sCurrent=NS::sCurrent*scale;
}

void reset(){
	NS::sMat=std::stack<glm::mat4>();
	NS::sCurrent=glm::mat4(1.0f);
}

glm::mat4 getCurrentMatrix(){
	return NS::sCurrent;
}




string_t GLErrorString(GLenum error) {
	switch(error) {
		case GL_NO_ERROR:
			return "GL_NO_ERROR";
		case GL_INVALID_ENUM:
			return "GL_INVALID_ENUM";
		case GL_INVALID_VALUE:
			return "GL_INVALID_VALUE";
		case GL_INVALID_OPERATION:
			return "GL_INVALID_OPERATION";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return "GL_INVALID_FRAMEBUFFER_OPERATION";
		case GL_OUT_OF_MEMORY:
			return "GL_OUT_OF_MEMORY";
		default:
			return "<Unknown error code>";
	}
}

void GLErrorAssert(string_t TAG, string_t format, ...) {
	va_list args;
	va_start(args, format);

	GLenum error = glGetError();
	if(error != GL_NO_ERROR) {
		string_t error_string = GLErrorString(error);
		gdt_fatal(TAG, format, error_string, args);
	}

	va_end(args);
}
