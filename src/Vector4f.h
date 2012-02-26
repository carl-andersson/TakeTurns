/*
 * Vector4f.h
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

#ifndef VECTOR4F_H
#define VECTOR4F_H
class Vector4f;
#include "Matrix4f.h"
class Vector4f{
private:
	float vec[4];
	friend class Matrix4f;
	void init(float v){
		for(int i=0;i<4;i++){
			vec[i]=v;
		}
	}
public:

	Vector4f(){
		init(0);
	}
	Vector4f(float v){
		init(v);
	}
	Vector4f(float v1,float v2,float v3,float v4){
		vec[0]=v1;
		vec[1]=v2;
		vec[2]=v3;
		vec[3]=v4;
	}

	float& operator[](int i ){
		return vec[i];
	}
};






#endif //VECTOR4F_H
