#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include "define.hpp"
#include "vec/Vec2.hpp"
#include "vec/Vec3.hpp"
#include "vec/Vec4.hpp"
#include "mat/Mat2.hpp"
#include "mat/Mat3.hpp"
#include "mat/Mat4.hpp"

struct face
{
	int x;
	int y;
	int z;
};

struct dface
{
	face	position;
	face	normal;
	face	texture;
	int	idMaterial;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Jauge
{
	vec3 position;
	vec3 color;
};

#endif