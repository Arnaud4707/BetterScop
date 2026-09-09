#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <ostream>
#include <iostream>

struct vec3
{
	float x;
	float y;
	float z;

	vec3(){
        x = 0;
        y = 0;
        z = 0;
    };

    vec3(float a){
        x = a;
        y = a;
        z = a;
    };

    vec3(float a, float b){
        x = a;
        y = b;
        z = 0;
    };

	vec3(float a, float b, float c){
		x = a;
        y = b;
        z = c;
	}

	bool operator==(const vec3& obj) const{
		
        constexpr float eps = 1e-6f;
        for (int i = 0; i < 3; i++){
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
		else
			return (z);
	};

	float &operator[](int i) {
		if (i == 0)
			return (x);
		else if (i == 1)
			return (y);
		else
			return (z);
	};

	vec3 operator++(int) {
		vec3 obj;
		obj.x = x;
		obj.y = y;
		obj.z = z;
		x += 1;
		y += 1;
		z += 1;
		return (obj);
	};

	vec3 &operator++() {
		x += 1;
		y += 1;
		z += 1;
		return (*this);
	};
	
	vec3 operator--(int) {
		vec3 obj;
		obj.x = x;
		obj.y = y;
		obj.z = z;
		x -= 1;
		y -= 1;
		z -= 1;
		return (obj);
	};

	vec3 &operator--() {
		x -= 1;
		y -= 1;
		z -= 1;
		return (*this);
	};
	
	vec3 &operator+=(const vec3& obj) {
		x += obj.x;
		y += obj.y;
		z += obj.z;
		return (*this);
	};

	vec3 &operator-=(const vec3& obj) {
		x -= obj.x;
		y -= obj.y;
		z -= obj.z;
		return (*this);
	};

	vec3 &operator*=(const vec3& obj) {
		x *= obj.x;
		y *= obj.y;
		z *= obj.z;
		return (*this);
	};

	vec3 &operator/=(const vec3& obj) {
		x /= obj.x;
		y /= obj.y;
		z /= obj.z;
		return (*this);
	};

	vec3 operator+(const vec3& obj) const {
		vec3 tmp;
		tmp.x = x + obj.x;
		tmp.y = y + obj.y;
		tmp.z = z + obj.z;
		return (tmp);
	};

	vec3 operator-(const vec3& obj) const {
		vec3 tmp;
		tmp.x = x - obj.x;
		tmp.y = y - obj.y;
		tmp.z = z - obj.z;
		return (tmp);
	};

	vec3 operator*(const vec3& obj) const {
		vec3 tmp;
		tmp.x = x * obj.x;
		tmp.y = y * obj.y;
		tmp.z = z * obj.z;
		return (tmp);
	};

	vec3 operator/(const vec3& obj) const {
		vec3 tmp;
		tmp.x = x / obj.x;
		tmp.y = y / obj.y;
		tmp.z = z / obj.z;
		return (tmp);
	};

	vec3 operator+(float i) const {
		vec3 tmp;
		tmp.x = x + i;
		tmp.y = y + i;
		tmp.z = z + i;
		return (tmp);
	};

	vec3 operator-(float i) const {
		vec3 tmp;
		tmp.x = x - i;
		tmp.y = y - i;
		tmp.z = z - i;
		return (tmp);
	};

	vec3 operator*(float i) const {
		vec3 tmp;
		tmp.x = x * i;
		tmp.y = y * i;
		tmp.z = z * i;
		return (tmp);
	};

	vec3 operator/(float i) const {
		vec3 tmp;
		tmp.x = x / i;
		tmp.y = y / i;
		tmp.z = z / i;
		return (tmp);
	};

};

static inline vec3 operator-(float k, const vec3& obj)
{
	vec3 tmp;
	for (int i = 0; i < 3; i++)
		tmp[i] = k - obj[i];
	return (tmp);
}

static inline vec3 operator-(const vec3& obj)
{
	vec3 tmp;
	for (int i = 0; i < 3; i++)
		tmp[i] = 0 - obj[i];
	return (tmp);
}

inline std::ostream& operator<<(std::ostream& os, const vec3& obj){
	os << "x: " << obj.x << " y: " << obj.y << " z: " << obj.z << std::endl;
	return (os);
}

#endif