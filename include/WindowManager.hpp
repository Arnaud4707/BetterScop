#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include "globals.hpp"

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

class WindowManager
{
	private:
		GLFWwindow *window3D;
		GLFWwindow *windowDebbug;
		Shader shaderObject;
		Shader shaderLight;
		ObjectBlender object;
		MusicEngine musicEngine;
		MusicAnalyzer analyzer;
		AnimationEngine animationEngine;
		Render render;

	public:
		WindowManager()
		{
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			int nmonitor;
			GLFWmonitor **monitor = glfwGetMonitors(&nmonitor);
			const GLFWvidmode *mode = glfwGetVideoMode(monitor[0]);

			initwindow(window3D, mode);
		};
		WindowManager(const WindowManager &obj) = default;
		WindowManager &operator=(const WindowManager &obj) = default;
		~WindowManager() = default;

		void initwindow(GLFWwindow* window, const GLFWvidmode *mode);
		void initShader();
		void initObjetBlender();
		void initTexture();
		void init3D();
		void initAudio();
		void initMusicAnayzer();
		void initMusicEngine();
		void initMusicAnayzer();
		void mouseEvent();
		void updateMusicEngine();
		void updateMusicAnalyzer();
		void updateAnimationEngine();
		void updateRender();
		void updateDebbug();
};

void	initMaterials(void);

void vertexSansNT(GLFWwindow *window, ObjectBlender* obj, unsigned int *VBO, unsigned int *VAO, unsigned int *lightVAO, int size)
{
	std::vector<float> tabVertex;
	for (auto &v : obj->getVertexs())
	{
		tabVertex.push_back(v.position.x);
		tabVertex.push_back(v.position.y);
		tabVertex.push_back(v.position.z);
	}
	(void)window;
	glGenBuffers(size, VBO);

	glGenVertexArrays(1, VAO);

	glBindVertexArray(VAO[0]);
	// 2. copy our first_triangle array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, tabVertex.size() * sizeof(float), tabVertex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glGenVertexArrays(1, lightVAO);

	glBindVertexArray(lightVAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// set the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
}

vec3 centerObj(ObjectBlender* obj)
{
	vec3 center(0.0f);

	for (auto &v : obj->getVertexs())
	    center += vec3 (v.position.x, v.position.y, v.position.z);

	center /= obj->getVertexs().size();

	vec3 c = {center.x, center.y, center.z};
	return (c);
}

void	framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

unsigned int loadTexture(char const *path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	(void)xoffset;
	(void)window;
	cam.ProcessMouseScroll(static_cast<float>(yoffset));
}

#endif