/*
 * Shader.h
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

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>

#include <gdt/gdt_gles2.h>

class Shader{
private:
	static const string_t TAG;

	GLint programID;
	static std::map<std::string, Shader> loadedShaders;
	static GLuint compileShader(string_t shaderCode, GLenum type);

public:
	static const Shader load(std::string vertFile, std::string fragFile);
	static const Shader get(std::string vertFile, std::string fragFile);

	Shader();
	Shader(GLint id);

	void use();

	bool setUniform1i(string_t unifo,int i);

	GLint getAttriLoc(string_t);

	bool setAttribute4f(string_t attri,float f1,float f2,float f3,float f4);
	bool setAttribute3f(string_t attri,float f1,float f2,float f3);
	bool setAttribute2f(string_t attri,float f1,float f2);
	bool setAttribute1f(string_t attri,float f1);

	bool setAttribute4f(string_t attri,float* f);
	bool setAttribute3f(string_t attri,float* f);
	bool setAttribute2f(string_t attri,float* f);
	bool setAttribute1f(string_t attri,float* f);


	bool setUniform4f(string_t unifo,float f1,float f2,float f3,float f4);
	bool setUniform3f(string_t unifo,float f1,float f2,float f3);
	bool setUniform2f(string_t unifo,float f1,float f2);
	bool setUniform1f(string_t unifo,float f1);

	bool setUniform4f(string_t unifo,float *f);
	bool setUniform3f(string_t unifo,float *f);
	bool setUniform2f(string_t unifo,float *f);
	bool setUniform1f(string_t unifo,float *f);
};

#endif //SHADER_H
