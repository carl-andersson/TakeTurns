


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
