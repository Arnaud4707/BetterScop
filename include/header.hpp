#ifndef HEADER_HPP
#define HEADER_HPP

#define WIDTH 800
#define HEIGHT 600

#include "shader.hpp"
#include "ObjectBlender.hpp"
#include "MusicEngine.hpp"
#include "MusicAnalyzer.hpp"
#include "AnimationEngine.hpp"
#include <random>

extern float vertices[];
extern unsigned int indices[];
extern bool autoRot;
extern bool wareFrame;
extern	float factor;
extern	bool onTexture;

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

extern Material emerald;
extern Material jade;
extern Material obsidian;
extern Material pearl;
extern Material ruby;
extern Material turquoise;
extern Material brass;
extern Material bronze;
extern Material chrome;
extern Material copper;
extern Material gold;
extern Material silver;
extern Material black_plastic;
extern Material cyan_plastic;
extern Material green_plastic;
extern Material red_plastic;
extern Material white_plastic;
extern Material yellow_plastic;
extern Material black_rubber;
extern Material cyan_rubber;
extern Material green_rubber;
extern Material red_rubber;
extern Material white_rubber;
extern Material yellow_rubber;
extern Light light;

void 			framebuffer_size_callback(GLFWwindow *window, int width, int height);
void 			processInput(GLFWwindow *window, float *delta, Shader *ourShader, Camera *camera);
void 			vertexf(GLFWwindow *window, ObjectBlender *obj, unsigned int *VBO, unsigned int *VAO, unsigned int *lightVAO, int size);
void 			vertexdf(GLFWwindow *window, ObjectBlender *obj, unsigned int *VBO, unsigned int *VAO, unsigned int *lightVAO, int size);
void 			transform4(Shader *ourShader);
void 			scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void 			objectAndLight(Shader *ourShader, mat4 *model, mat4 *view, mat4 *projection, int width, int height, vec3 pos, AnimationState& anime);
void 			materialAndLight(Shader *ourShader, mat4 *model, mat4 *view, mat4 *projection, int width, int height, Material mat, vec3 pos);
void 			initMaterials(void);
unsigned int 	loadTexture(char const *path);
void 			vertexSansNT(GLFWwindow *window, ObjectBlender *obj, unsigned int *VBO, unsigned int *VAO, unsigned int *lightVAO, int size);
void 			print_vertex(ObjectBlender *obj);
vec3 			centerObj(ObjectBlender *obj);

inline float random(float min, float max)
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
};
#endif