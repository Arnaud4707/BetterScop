#ifndef OBJECTBLENDER_HPP
#define OBJECTBLENDER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <bits/stdc++.h>
#include "structure.hpp"
#include "fonction_math.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct vertex
{
	vec3 position;
	vec3 normal;
	vec2 texcoord;
	int idMaterial;
};

struct key{
	std::string index;
	int nbIndex;
};

struct lightning
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

class ObjectBlender
{
private:
	std::string name;
	std::vector<vertex> vertexs;
	std::vector<face> faces;
	std::vector<vec3> v;
	std::vector<vec3> n;
	std::vector<vec2> t;
	std::vector<dface> dfaces;
	std::map<int, lightning> color;
	std::map<std::string, int> keys;
	lightning light;

public:
	ObjectBlender(){};
	ObjectBlender(std::string fileObj, std::string fileMtl);
	ObjectBlender(std::string fileObj, std::string fileMtl, int d);
	ObjectBlender(const ObjectBlender &o) = default;
	ObjectBlender &operator=(const ObjectBlender &o) = default;
	~ObjectBlender() = default;

	const std::vector<vec3> &getV() const;
	const std::vector<face> &getF() const;
	const std::vector<dface> &getdF() const;
	const std::vector<vertex> &getVertexs() const;
	const std::string &getName() const;
	const lightning &getlightning() const;
	const std::map<std::string, int> &getKey() const;
	const std::map<int, lightning> &getMaterials() const;
	void calculeNormal();
	void parseLight(std::string text);
	void	generateTexCoords();
	void	mouse_callback(GLFWwindow *window, double xposIn, double yposIn);

	void	tri();
};

#endif