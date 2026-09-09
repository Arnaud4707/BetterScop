#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>
#include <ostream>
#include <iostream>

struct vec2
{
	float x;
	float y;

    vec2(){
        x = 0;
        y = 0;
    };

    vec2(float a){
        x = a;
        y = a;
    };

    vec2(float a, float b){
        x = a;
        y = b;
    };

	bool operator==(const vec2& obj) const{
		
        constexpr float eps = 1e-6f;
        for (int i = 0; i < 2; i++){
			if (std::fabs((*this)[i] - obj[i]) > eps)
				return false;
        }
        return (true);
	};

	const float &operator[](int i) const{
		if (i == 0)
			return (x);
		else
			return (y);
	};

	float &operator[](int i) {
		if (i == 0)
			return (x);
		else
			return (y);
	};

	vec2 operator++(int) {
		vec2 obj;
		obj.x = x;
		obj.y = y;
		x += 1;
		y += 1;
		return (obj);
	};

	vec2 &operator++() {
		x += 1;
		y += 1;
		return (*this);
	};
	
	vec2 operator--(int) {
		vec2 obj;
		obj.x = x;
		obj.y = y;
		x -= 1;
		y -= 1;
		return (obj);
	};

	vec2 &operator--() {
		x -= 1;
		y -= 1;
		return (*this);
	};
	
	vec2 &operator+=(const vec2& obj) {
		x += obj.x;
		y += obj.y;
		return (*this);
	};

	vec2 &operator-=(const vec2& obj) {
		x -= obj.x;
		y -= obj.y;
		return (*this);
	};

	vec2 &operator*=(const vec2& obj) {
		x *= obj.x;
		y *= obj.y;
		return (*this);
	};

	vec2 &operator/=(const vec2& obj) {
		x /= obj.x;
		y /= obj.y;
		return (*this);
	};

	vec2 operator+(const vec2& obj) const {
		vec2 tmp;
		tmp.x = x + obj.x;
		tmp.y = y + obj.y;
		return (tmp);
	};

	vec2 operator-(const vec2& obj) const {
		vec2 tmp;
		tmp.x = x - obj.x;
		tmp.y = y - obj.y;
		return (tmp);
	};

	vec2 operator*(const vec2& obj) const {
		vec2 tmp;
		tmp.x = x * obj.x;
		tmp.y = y * obj.y;
		return (tmp);
	};

	vec2 operator/(const vec2& obj) const {
		vec2 tmp;
		tmp.x = x / obj.x;
		tmp.y = y / obj.y;
		return (tmp);
	};

	vec2 operator+(float i) const {
		vec2 tmp;
		tmp.x = x + i;
		tmp.y = y + i;
		return (tmp);
	};

	vec2 operator-(float i) const {
		vec2 tmp;
		tmp.x = x - i;
		tmp.y = y - i;
		return (tmp);
	};

	vec2 operator*(float i) const {
		vec2 tmp;
		tmp.x = x * i;
		tmp.y = y * i;
		return (tmp);
	};

	vec2 operator/(float i) const {
		vec2 tmp;
		tmp.x = x / i;
		tmp.y = y / i;
		return (tmp);
	};

};

static inline vec2 operator-(float i, const vec2& obj)
{
	vec2 tmp;
	tmp.x = i - obj.x;
	tmp.y = i - obj.y;
	return (tmp);
}

static inline vec2 operator-(const vec2& obj)
{
	vec2 tmp;
	tmp.x = 0 - obj.x;
	tmp.y = 0 - obj.y;
	return (tmp);
}

inline std::ostream& operator<<(std::ostream& os, const vec2& obj){
	os << "x: " << obj.x << " y: " << std::endl;
	return (os);
}

#endif