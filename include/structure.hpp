#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include "define.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat2.hpp"
#include "Mat3.hpp"
#include "Mat4.hpp"

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

#endif