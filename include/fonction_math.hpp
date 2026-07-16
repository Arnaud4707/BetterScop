#ifndef FONCTION_MATH
#define FONCTION_MATH

#include "structure.hpp"
#include <cmath>

static inline vec3 add(vec3 a, vec3 b)
{
    return {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

static inline vec3	sub(vec3 a, vec3 b)
{
	vec3 r;

	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
	return (r);
}

static inline vec3	cross(vec3 a, vec3 b)
{
	vec3 r;

	r.x = a.y * b.z - a.z * b.y;
	r.y = a.z * b.x - a.x * b.z;
	r.z = a.x * b.y - a.y * b.x;
	return (r);
}

static inline vec3	normalize(vec3 v)
{
	float len;
	vec3 r;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0)
		return (v);
	r.x = v.x / len;
	r.y = v.y / len;
	r.z = v.z / len;
	return (r);
}

static inline double	dot(vec3 a, vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

static inline double edge(vec3 a, vec3 b, vec3 c)
{
	return (c.x - a.x)*(b.y - a.y) - (c.y - a.y)*(b.x - a.x);
}

static inline mat4 translate(const mat4& mat, const vec3& vec)
{
	mat4 tmp(1.0f);

    tmp[0][3] = vec.x;
    tmp[1][3] = vec.y;
    tmp[2][3] = vec.z;

    return mat * tmp;
}

static inline mat4 perspective(float fov, float aspect, float near, float far)
{
	mat4 tmp(1.0f);

	tmp.mat[0][0] = 1.0 / (tan(fov / 2) * aspect);
	tmp.mat[1][1] = 1.0 / tan(fov / 2);
	tmp.mat[2][2] = (far + near) / (near - far);
	tmp.mat[2][3] = (2 * far * near) / (near - far);
	tmp.mat[3][2] = -1.0;
	tmp.mat[3][3] = 0;
	return (tmp);
}

static inline mat4 scale(const mat4& mat, const vec3& vec)
{
	mat4 tmp(1.0f);

	tmp[0][0] = vec.x;
	tmp[1][1] = vec.y;
	tmp[2][2] = vec.z;

	return (mat * tmp);
}

static inline mat4 rotate(const mat4& mat, float theta, const vec3& vec)
{
	mat4 tmp(1.0f);
	vec3 axis = normalize(vec);
	
	tmp.mat[0][0] = cosf(theta) + (axis.x * axis.x) * (1 - cosf(theta));
	tmp.mat[0][1] = axis.x * axis.y * (1 - cosf(theta)) - axis.z * sinf(theta);
	tmp.mat[0][2] = axis.x * axis.z * (1 - cosf(theta)) + axis.y * sinf(theta);
	tmp.mat[1][0] = axis.y * axis.x * (1 - cosf(theta)) + axis.z * sinf(theta);
	tmp.mat[1][1] = cosf(theta) + (axis.y * axis.y) * (1 - cosf(theta));
	tmp.mat[1][2] = axis.y * axis.z * (1 - cosf(theta)) - axis.x * sinf(theta);
	tmp.mat[2][0] = axis.z * axis.x * (1 - cosf(theta)) - axis.y * sinf(theta);
	tmp.mat[2][1] = axis.z * axis.y * (1 - cosf(theta)) + axis.x * sinf(theta);
	tmp.mat[2][2] = cosf(theta) + (axis.z * axis.z) * (1 - cosf(theta));

	return (mat * tmp);
}

static inline float radians(float degrees)
{
	return ((M_PI * degrees)/ 180);
}
#endif