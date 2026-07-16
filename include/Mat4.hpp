#ifndef MAT4_HPP
#define MAT4_HPP

#include "Vec4.hpp"

struct mat4
{
	float mat[4][4];
    
    mat4(){
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                mat[i][j] = 0;
    };

    mat4(float k){
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                mat[i][j] = (i == j) ? k : 0;
    };

    const float *operator[](int i) const{
        if (i == 0)
            return (mat[0]);
        else if (i == 1)
            return (mat[1]);
        else if (i == 2)
            return (mat[2]);
        else
            return (mat[3]);
    }

    float *operator[](int i) {
        if (i == 0)
            return (mat[0]);
        else if (i == 1)
            return (mat[1]);
        else if (i == 2)
            return (mat[2]);
        else
            return (mat[3]);
    }

    bool operator==(const mat4& obj) const {
        constexpr float eps = 1e-6f;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (std::fabs(mat[i][j] - obj.mat[i][j]) > eps)
    	        	return false;
            }
        }
        return (true);
    }

    mat4 operator+(const mat4& obj) const {
        mat4 tmp ;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                tmp.mat[i][j] = mat[i][j] + obj.mat[i][j];
            }
        }
        return (tmp);
    }
    
    mat4 operator-(const mat4& obj) const {
        mat4 tmp ;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                tmp.mat[i][j] = mat[i][j] - obj.mat[i][j];
            }
        }
        return (tmp);
    }

    mat4& operator*=(float k) {
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                mat[i][j] = mat[i][j] * k;
            }
        }
        return (*this);
    }
    
    mat4 operator*(float k) const {
        mat4 tmp ;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                tmp.mat[i][j] = mat[i][j] * k;
            }
        }
        return (tmp);
    }

    mat4 operator*(const mat4& obj) const {
        mat4 tmp(0);
        for (int a = 0; a < 4; ++a) { // ligne m gauche
            for (int b = 0; b < 4; ++b) { // col m droite
                for (int c = 0; c < 4; ++c) { // s produit
                    tmp.mat[a][b] += mat[a][c] * obj.mat[c][b];
                }
            }
        }
        return (tmp);
    }

    vec4 operator*(const vec4& v) const
    {
        vec4 r(0.0f);

        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                r[i] += mat[i][j] * v[j];
        return r;
    }
};

inline mat4 operator*(float i, const mat4& obj) {
    mat4 tmp(obj);
    tmp *= i;
    return (tmp);
}

#endif