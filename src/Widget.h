

#ifndef WIDGET_H
#define WIDGET_H

#include <vector>

class Widget{

private:
	std::vector<Widget*> children;

	float mX;
	float mY;

	float green;
	float red;
	float blue;
	float alpha;


public:

	Widget(){
		children=std::vector<Widget*>();
		mX=0;
		mY=0;
		green=1;
		blue=1;
		red=1;
		alpha=1;
	}

	void draw();
	void drawSelf(){};



};




#endif WIDGET_H
