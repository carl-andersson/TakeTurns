



#ifndef SCREEN_H
#define SCREEN_H

#include <gdt/gdt_gles2.h>

class Screen{
private:
	GLuint mWidth;
	GLuint mHeight;
public:
	Screen(GLuint height, GLuint width){
		mWidth=width;
		mHeight=height;
	}

	Screen(){};


};





#endif //SCREEN_H
