#ifndef MAT2_HPP
#define MAT2_HPP

#include <cmath>

struct mat2
{
	float mat[2][2];
    
    mat2(){
        for (int i= 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                mat[i][j] = 0;
    };

    mat2(float k){
        for (int i= 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                mat[i][j] = (i == j) ? k : 0;
    };

    const float *operator[](int i) const{
        if (i == 0)
            return (mat[0]);
        else
            return (mat[1]);
    }

    float *operator[](int i) {
        if (i == 0)
            return (mat[0]);
        else
            return (mat[1]);
    }

    bool operator==(const mat2& obj) const {
        constexpr float eps = 1e-6f;
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 2; j++){
                if (std::fabs(mat[i][j] - obj.mat[i][j]) > eps)
    	        	return false;
            }
        }
        return (true);
    }

    mat2 operator+(const mat2& obj) const {
        mat2 tmp ;
        tmp.mat[0][0] = mat[0][0] + obj.mat[0][0];
        tmp.mat[0][1] = mat[0][1] + obj.mat[0][1];
        tmp.mat[1][0] = mat[1][0] + obj.mat[1][0];
        tmp.mat[1][1] = mat[1][1] + obj.mat[1][1];
        return (tmp);
    }
    
    mat2 operator-(const mat2& obj) const {
        mat2 tmp ;
        tmp.mat[0][0] = mat[0][0] - obj.mat[0][0];
        tmp.mat[0][1] = mat[0][1] - obj.mat[0][1];
        tmp.mat[1][0] = mat[1][0] - obj.mat[1][0];
        tmp.mat[1][1] = mat[1][1] - obj.mat[1][1];
        return (tmp);
    }

    mat2& operator*=(float i) {
        mat[0][0] = mat[0][0] * i;
        mat[0][1] = mat[0][1] * i;
        mat[1][0] = mat[1][0] * i;
        mat[1][1] = mat[1][1] * i;
        return (*this);
    }

    mat2& operator/=(float i){
        mat[0][0] = mat[0][0] / i;
        mat[0][1] = mat[0][1] / i;
        mat[1][0] = mat[1][0] / i;
        mat[1][1] = mat[1][1] / i;
        return (*this);
    }
    
    mat2 operator*(float i) const {
        mat2 tmp ;
        tmp.mat[0][0] = mat[0][0] * i;
        tmp.mat[0][1] = mat[0][1] * i;
        tmp.mat[1][0] = mat[1][0] * i;
        tmp.mat[1][1] = mat[1][1] * i;
        return (tmp);
    }
    
    mat2 operator/(float i) const {
        mat2 tmp ;
        tmp.mat[0][0] = mat[0][0] / i;
        tmp.mat[0][1] = mat[0][1] / i;
        tmp.mat[1][0] = mat[1][0] / i;
        tmp.mat[1][1] = mat[1][1] / i;
        return (tmp);
    }

    mat2 operator*(const mat2& obj) const {
        mat2 tmp;
        tmp.mat[0][0] = mat[0][0] * obj.mat[0][0] + mat[0][1] * obj.mat[1][0];
        tmp.mat[0][1] = mat[0][0] * obj.mat[0][1] + mat[0][1] * obj.mat[1][1];
        tmp.mat[1][0] = mat[1][0] * obj.mat[0][0] + mat[1][1] * obj.mat[1][0];
        tmp.mat[1][1] = mat[1][0] * obj.mat[0][1] + mat[1][1] * obj.mat[1][1];
        return (tmp);
    }
};

inline mat2 operator*(float i, const mat2& obj) {
    mat2 tmp(obj);
    tmp *= i;
    return (tmp);
}

inline mat2 operator/(float i, const mat2& obj) {
    mat2 tmp(obj);
    tmp /= i;
    return (tmp);
}

#endif