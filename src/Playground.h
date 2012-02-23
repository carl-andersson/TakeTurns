
#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include "Sprite.h"
#include "Texture.h"
#include <gdt/gdt_gles2.h>

struct pixel{
	GLubyte red,green,blue,alpha;
};

class Playground:public Sprite{
private:
	struct pixel *data;
	int width;
	int height;
	bool dirty;
	int xMin,Ymin,xMax,yMax;
public:
	Playground(std::string name,int w, int h){
		width=w;
		height=h;
		data=(struct pixel*)calloc(width*height,sizeof(struct pixel));
		mTexture=Texture::createTexture(name,(GLubyte*)data,width,height);
		data[1040].red=255;
	}
	~Playground(){
		free(data);
	}
	void setPixel(int x, int y,float r,float g,float b){
		data[width*y+x].red=r;
		data[width*y+x].green=g;
		data[width*y+x].blue=b;
	}
	void updateTexture(){
		glActiveTexture(GL_TEXTURE0+mTexture.getID());
		glTexSubImage2D(GL_TEXTURE_2D,0,0,0,width,height,GL_RGBA,GL_UNSIGNED_BYTE,(GLubyte*)data);
	}

};




#endif //PLAYGROUND_H
