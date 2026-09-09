#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include "globals.hpp"

void	framebuffer_size_callback(GLFWwindow *window, int width, int height);

unsigned int loadTexture(char const *path);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

struct Render
{
	unsigned int VAO[1];
	unsigned int lightVAO[1];
	unsigned int VBO[2];
	unsigned int texture1;
	vec3 centerObject;
	mat4 projection;
	mat4 view;
	mat4 model;
};

struct WindowBox {
	vec4				color;
	Shader				shaderObject;
	Shader				shaderLight;
	ObjectBlender		object;
	Render				render;
	float				width;
	float				height;
};

class WindowManager
{
	private:
		GLFWwindow			*window;
		WindowBox			app;
		WindowBox			visualizer;
		MusicEngine			musicEngine;
		MusicAnalyzer		analyzer;
		MusicState			track;
		AnimationEngine 	animationEngine;
		AnimationState		state;
		float 				percentWin;
		int					width;
		int					height;
		GLFWwindow* initwindow(const GLFWvidmode *mode, std::string name);


	public:
		WindowManager()
		{
			glfwInit();

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			percentWin = 0.8f;
			// percentWin = 1.f;
			int nmonitor;
			GLFWmonitor **monitor = glfwGetMonitors(&nmonitor);
			const GLFWvidmode* mode = glfwGetVideoMode(monitor[0]);
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
			app.color = vec4(0.1f, 0.1f, 0.1f, 1.0f);
			visualizer.color = vec4(0.9f, 0.9f, 0.9f, 1.0f);
			window = initwindow(mode, "Audio Animation");
			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
			glfwSetScrollCallback(window, scroll_callback);
			// tell GLFW to capture our mouse
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		};
		WindowManager(const WindowManager &obj) = default;
		WindowManager &operator=(const WindowManager &obj) = default;
		~WindowManager() = default;

		void initShader();
		void initObjetBlender();
		void initTexture();
		void init3D();
		void initVisualizer();
		void startAudio();
		void initMusicAnayzer();
		void initMusicEngine();
		void setPointerWindow(GLFWwindow* window);
		GLFWwindow* getWindow(){
			return (window);
		};
		void updateMusicEngine(float currentTime);
		void updateMusicAnalyzer();
		void updateAnimationEngine(float deltaTime);
		void updateRender();
		void updateVisualizer();
		void destroyWindow();

};

void	processInputAnimation(GLFWwindow *window, float *delta, Shader* ourShader, Camera *camera);

void	processInputVisualizer(GLFWwindow *window, float *delta, Shader* ourShader, Camera *camera);

void	initMaterials(void);

void vertexSansNT(GLFWwindow *window, ObjectBlender* obj, unsigned int *VBO, unsigned int *VAO, unsigned int *lightVAO, int size);

void recVisualizer(GLFWwindow *window, unsigned int *VBO, unsigned int *VAO, int size);

vec3 centerObj(ObjectBlender* obj);

void	objectAndLight(WindowBox& app, float width, float height, AnimationState& anime);

#endif