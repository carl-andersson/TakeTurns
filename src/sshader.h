/*
 * sshader.h
 *
 * CopyRight (c) 2012 Carl Andersson
 * Copyright (c) 2011 Sebastian Ärleryd
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

#ifndef SSHADER_H
#define SSHADER_H

#include <gdt/gdt_gles2.h>

void sshaderInit();

GLuint linkProgram();
GLuint compileShader(string_t shaderCode, GLenum type);

GLuint getShaderId();
GLuint getTextcoordsLocation();
GLuint getTextureLocation();

void translate2f(float, float);
void setColor3f(float,float,float);
void setColor4f(float,float,float,float);

void setScale2f(float,float);

<<<<<<< HEAD
=======


>>>>>>> origin/master
#endif //SSHADER_H
