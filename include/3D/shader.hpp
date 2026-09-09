#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../structure.hpp"
#include "camera.hpp"

extern Camera cam;

class Shader
{
public:
	// the program ID
	unsigned int ID;
	float	rotX;
	float	rotY;
	bool	rot;
	float	rotationSpeed = 2.0f;
	float	deltaTime = 0.005f;
	// constructor reads and builds the shader
	Shader(){};
	Shader(const char *vertexPath, const char *fragmentPath, float rotx = INIT_ROTX_OBJ, float roty = INIT_ROTY_OBJ, bool rot = false);
	Shader(const Shader& obj) = default;
	Shader& operator=(const Shader& obj) = default;
	~Shader() = default;
	// use/activate the shader
	void use();
	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string &name, const vec2 &vec2) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec3(const std::string &name, const vec3 &vec3) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, const vec4 &vec4) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
	void setMat2(const std::string &name, const mat2 &mat2) const;
	void setMat3(const std::string &name, const mat3 &mat3) const;
	void setMat4(const std::string &name, const mat4 &mat4) const;
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void resetMouse();
	void setRotationSpeed(float rts){
		this->rotationSpeed = rts;
	};
	void setDeltaTime(float dt){
		this->deltaTime = dt;
	};
	void setRot(bool rotObj){
		this->rot = rotObj;
	};
	void setRotX(float rotx){
		this->rotX = rotx;
	};
	void setRotY(float roty){
		this->rotY = roty;
	};
	float getRotationSpeed(void){
		return (this->rotationSpeed);
	};
	float getDeltaTime(void){
		return (this->deltaTime);
	};
	float getRotX(void){
		return (this->rotX);
	};
	float getRotY(void){
		return (this->rotY);
	};
	float getRot(void){
		return (this->rot);
	};
    static void mouse_callback_wrapper(GLFWwindow* window,
                                       double xpos,
                                       double ypos)
    {
        Shader* shader =
            static_cast<Shader*>(glfwGetWindowUserPointer(window));

        shader->mouse_callback(window, xpos, ypos);
    }
};

#endif
