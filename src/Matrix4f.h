/*
 * Matrix4f.h
 *
 * Copyright (c) 2011 Sebastian Ärleryd
 * CopyRight (c) 2012 Carl Andersson
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

#ifndef MATRIX4F_H
#define MATRIX4F_H

class Matrix4f;
#include "Vector4f.h"

class Matrix4f{
private:
	float mat[4][4];

	void init(){
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				mat[i][j]=0;
			}
		}
	}

public:


	Matrix4f(){
		init();
	}

	Matrix4f(float v){
		init();
		for(int i=0;i<4;i++){
			mat[i][i]=v;
		}
	}

	Matrix4f operator*(const Matrix4f& other) const{
		Matrix4f res;
		for (int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				for(int k=0;k<4;k++){
					res.mat[i][j]=res.mat[i][j]+mat[i][k]*other.mat[k][j];
				}
			}
		}
		return res;
	}


	Vector4f operator*(const Vector4f& vec) const{
		Vector4f res;
		for (int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				res[i]=res[i]+vec.vec[j]*mat[i][j];
			}
		}
		return res;
	}


};


#endif //MATRIX4F_H
