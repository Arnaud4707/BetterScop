#ifndef VEC4_HPP
#define VEC4_HPP

#include <cmath>
#include <ostream>
#include <iostream>

struct vec4
{
	float x;
	float y;
	float z;
	float w;

	vec4(){
        x = 0;
        y = 0;
        z = 0;
		w = 0;
    };

    vec4(float a){
        x = a;
        y = a;
        z = a;
		w = a;
    };

    vec4(float a, float b){
        x = a;
        y = b;
        z = 0;
		w = 0;
    };

	vec4(float a, float b, float c){
		x = a;
        y = b;
        z = c;
		w = 0;
	}
	vec4(float a, float b, float c, float d){
		x = a;
        y = b;
        z = c;
		w = d;
	}

	bool operator==(const vec4& obj) const{
		
        constexpr float eps = 1e-6f;
        for (int i = 0; i < 4; i++){
			if (std::fabs((*this)[i] - obj[i]) > eps)
				return false;
        }
        return (true);
	};

	const float &operator[](int i) const{
		if (i == 0)
			return (x);
		else if (i == 1)
			return (y);
		else if (i == 2)
			return (z);
		else
			return (w);
	};

	float &operator[](int i) {
		if (i == 0)
			return (x);
		else if (i == 1)
			return (y);
		else if (i == 2)
			return (z);
		else
			return (w);
	};

	vec4 operator++(int) {
		vec4 obj;
		obj.x = x;
		obj.y = y;
		obj.z = z;
		obj.w = w;
		x += 1;
		y += 1;
		z += 1;
		w += 1;
		return (obj);
	};

	vec4 &operator++() {
		x += 1;
		y += 1;
		z += 1;
		w += 1;
		return (*this);
	};
	
	vec4 operator--(int) {
		vec4 obj;
		obj.x = x;
		obj.y = y;
		obj.z = z;
		obj.w = w;
		x -= 1;
		y -= 1;
		z -= 1;
		w -= 1;
		return (obj);
	};

	vec4 &operator--() {
		x -= 1;
		y -= 1;
		z -= 1;
		w -= 1;
		return (*this);
	};
	
	vec4 &operator+=(const vec4& obj) {
		x += obj.x;
		y += obj.y;
		z += obj.z;
		w += obj.w;
		return (*this);
	};

	vec4 &operator-=(const vec4& obj) {
		x -= obj.x;
		y -= obj.y;
		z -= obj.z;
		w -= obj.w;
		return (*this);
	};

	vec4 &operator*=(const vec4& obj) {
		x *= obj.x;
		y *= obj.y;
		z *= obj.z;
		w *= obj.w;
		return (*this);
	};

	vec4 &operator/=(const vec4& obj) {
		x /= obj.x;
		y /= obj.y;
		z /= obj.z;
		w /= obj.w;
		return (*this);
	};

	vec4 operator+(const vec4& obj) const {
		vec4 tmp;
		tmp.x = x + obj.x;
		tmp.y = y + obj.y;
		tmp.z = z + obj.z;
		tmp.w = w + obj.w;
		return (tmp);
	};

	vec4 operator-(const vec4& obj) const {
		vec4 tmp;
		tmp.x = x - obj.x;
		tmp.y = y - obj.y;
		tmp.z = z - obj.z;
		tmp.w = w - obj.w;
		return (tmp);
	};

	vec4 operator*(const vec4& obj) const {
		vec4 tmp;
		tmp.x = x * obj.x;
		tmp.y = y * obj.y;
		tmp.z = z * obj.z;
		tmp.w = w * obj.w;
		return (tmp);
	};

	vec4 operator/(const vec4& obj) const {
		vec4 tmp;
		tmp.x = x / obj.x;
		tmp.y = y / obj.y;
		tmp.z = z / obj.z;
		tmp.w = w / obj.w;
		return (tmp);
	};

	vec4 operator+(float i) const {
		vec4 tmp;
		tmp.x = x + i;
		tmp.y = y + i;
		tmp.z = z + i;
		tmp.w = w + i;
		return (tmp);
	};

	vec4 operator-(float i) const {
		vec4 tmp;
		tmp.x = x - i;
		tmp.y = y - i;
		tmp.z = z - i;
		tmp.w = w - i;
		return (tmp);
	};

	vec4 operator*(float i) const {
		vec4 tmp;
		tmp.x = x * i;
		tmp.y = y * i;
		tmp.z = z * i;
		tmp.w = w * i;
		return (tmp);
	};

	vec4 operator/(float i) const {
		vec4 tmp;
		tmp.x = x / i;
		tmp.y = y / i;
		tmp.z = z / i;
		tmp.w = w / i;
		return (tmp);
	};

};

static inline vec4 operator-(float k, const vec4& obj)
{
	vec4 tmp;
	for (int i = 0; i < 4; i++)
		tmp[i] = k - obj[i];
	return (tmp);
}

static inline vec4 operator-(const vec4& obj)
{
	vec4 tmp;
	for (int i = 0; i < 4; i++)
		tmp[i] = 0 - obj[i];
	return (tmp);
}

inline std::ostream& operator<<(std::ostream& os, const vec4& obj){
	os << "x: " << obj.x << " y: " << obj.y << " z: " << obj.z << " w: " << obj.w << std::endl;
	return (os);
}

#endif