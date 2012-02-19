



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
