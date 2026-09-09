#ifndef MAT3_HPP
#define MAT3_HPP

#include <cmath>

struct mat3
{
	float mat[3][3];
    
    mat3(){
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                mat[i][j] = 0;
    };

    mat3(float k){
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                mat[i][j] = (i == j) ? k : 0.0f;
    };

    const float *operator[](int i) const{
        if (i == 0)
            return (mat[0]);
        else if (i == 1)
            return (mat[1]);
        else
            return (mat[2]);
    }

    float *operator[](int i) {
        if (i == 0)
            return (mat[0]);
        else if (i == 1)
            return (mat[1]);
        else
            return (mat[2]);
    }

    bool operator==(const mat3& obj) const {
        
        constexpr float eps = 1e-6f;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (std::fabs(mat[i][j] - obj.mat[i][j]) > eps)
    	        	return false;
            }
        }
        return (true);
    }

    mat3 operator+(const mat3& obj) const {
        mat3 tmp ;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                tmp.mat[i][j] = mat[i][j] + obj.mat[i][j];
            }
        }
        return (tmp);
    }
    
    mat3 operator-(const mat3& obj) const {
        mat3 tmp ;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                tmp.mat[i][j] = mat[i][j] - obj.mat[i][j];
            }
        }
        return (tmp);
    }

    mat3& operator*=(float k) {
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                mat[i][j] = mat[i][j] * k;
            }
        }
        return (*this);
    }
    
    mat3 operator*(float k) const {
        mat3 tmp ;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                tmp.mat[i][j] = mat[i][j] * k;
            }
        }
        return (tmp);
    }

    mat3 operator*(const mat3& obj) const {
        mat3 tmp(0);
        for (int a = 0; a < 3; ++a) { // ligne m gauche
            for (int b = 0; b < 3; ++b) { // col m droite
                for (int c = 0; c < 3; ++c) { // s produit
                    tmp.mat[a][b] += mat[a][c] * obj.mat[c][b];
                }
            }
        }
        return (tmp);
    }
};

inline mat3 operator*(float i, const mat3& obj) {
    mat3 tmp(obj);
    tmp *= i;
    return (tmp);
}

#endif