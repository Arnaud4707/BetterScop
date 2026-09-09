#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "../include/WindowManager.hpp"

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

void recVisualizer(GLFWwindow *window, unsigned int *VBO, unsigned int *VAO, int size)
{
	(void)window;
	glGenBuffers(size, VBO);

	glGenVertexArrays(1, VAO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);
	// set the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
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

void	objectAndLight(WindowBox& app, float width, float height, AnimationState& anime)
{
	app.shaderObject.use();
	app.shaderObject.setVec3("light.position", light.position);
	app.shaderObject.setFloat("factor", factor);
	if (onTexture)
	{
		if (factor < 1.00000)
			factor += SPEED_SWITCH_COLOR_TEXTURE;
		else if (factor > 1.00000)
			factor = 1.0;
	}
	else
	{
		if (factor > 0.00000)
			factor -= SPEED_SWITCH_COLOR_TEXTURE;
		else if (factor < 0.00000)
			factor = 0.0;
	}
	// app.shaderObject.setVec3("lightObj.ambient", lightObj.ambient);
	// app.shaderObject.setVec3("lightObj.diffuse", lightObj.diffuse);
	// app.shaderObject.setVec3("lightObj.specular", lightObj.specular);
	// app.shaderObject.setFloat("lightObj.shininess", lightObj.shininess);
	app.shaderObject.setVec3("light.ambient",  light.ambient);
	app.shaderObject.setVec3("light.diffuse",  light.diffuse); // darken diffuse light a bit
	app.shaderObject.setVec3("light.specular", light.specular); 
	// view/projection transformations
	app.render.projection = perspective(radians(cam.Zoom * anime.cameraZoom),width / height, 0.1f, 100.f);
	// *projection = perspective(radians(cam.Zoom), (float)(width * 0.8) / (float)(height * 0.8), 0.1f, 100.0f);
	float s = anime.cameraShake;
	cam.Position.x += random(-1,1) * s * 0.03f;
	cam.Position.y += random(-1,1) * s * 0.03f;
	app.render.view = cam.GetViewMatrix();
	app.shaderObject.setMat4("projection", app.render.projection);
	app.shaderObject.setMat4("view", app.render.view);
	app.shaderObject.setVec3("viewPos", cam.Position);

	// world transformation
    app.render.model = mat4(1.0f);
	app.render.model = translate(app.render.model, app.render.centerObject);
	app.render.model = rotate(app.render.model, app.shaderObject.getRotY(), vec3(0.0f, 1.0f, 0.0f));
	app.render.model = rotate(app.render.model, app.shaderObject.getRotX(), vec3(1.0f, 0.0f, 0.0f));
	app.render.model = translate(app.render.model, -app.render.centerObject);
	app.render.model = translate(app.render.model, vec3(0.0f));
    app.render.model = scale(app.render.model, anime.objectScale);

	app.shaderObject.setMat4("model", app.render.model);

}

void processInputAnimation(GLFWwindow *window, float *delta, Shader* ourShader, Camera *camera)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		system("pkill paplay");
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, *delta);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, *delta);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, *delta);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, *delta);
	static bool yPressedLastFrame = false;
	static bool oPressedLastFrame = false;
	static bool lPressedLastFrame = false;
	static bool tPressedLastFrame = false;
	bool yPressedNow = glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS;
	bool oPressedNow = glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS;
	bool lPressedNow = glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS;
	bool tPressedNow = glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS;
	if (oPressedNow && !oPressedLastFrame)
	{
		if (ourShader->getRot())
		{
    		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			ourShader->setRot(false);
		}
		else
		{
    		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			ourShader->setRot(true);
			ourShader->resetMouse();
		}
	}
	if (lPressedNow && !lPressedLastFrame)
	{
		if (autoRot)
			autoRot = false;
		else
			autoRot = true;
	}
	if (yPressedNow && !yPressedLastFrame)
	{
		if (!wareFrame)
		{
			glDisable(GL_DEPTH_TEST);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			wareFrame = true;
		}
		else
		{
			glEnable(GL_DEPTH_TEST);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			wareFrame = false;
		}
	}
	if (tPressedNow && !tPressedLastFrame)
	{
		if (onTexture)
			onTexture = false;
		else
			onTexture = true;
	}
	yPressedLastFrame = yPressedNow;
	oPressedLastFrame = oPressedNow;
	lPressedLastFrame = lPressedNow;
	tPressedLastFrame = tPressedNow;
	// if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	// 	light.position.y += 0.05f;
	// if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	// 	light.position.y -= 0.05f;
	// if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	// 	light.position.x += 0.05f;
	// if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	// 	light.position.x -= 0.05f;
	// if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	// 	light.position.z += 0.05f;
	// if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	// 	light.position.z -= 0.05f;
};

void	processInputVisualizer(GLFWwindow *window, float *delta, Shader* ourShader, Camera *camera)
{
    (void)delta;
    (void)ourShader;
    (void)camera;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		EGlobal.position.y += 0.05f;
		std::cout << EGlobal.position;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		EGlobal.position.y -= 0.05f;
		std::cout << EGlobal.position;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
		EGlobal.position.x += 0.05f;
		std::cout << EGlobal.position;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		EGlobal.position.x -= 0.05f;
		std::cout << EGlobal.position;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		EGlobal.position.z += 0.05f;
		std::cout << EGlobal.position;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		EGlobal.position.z -= 0.05f;
		std::cout << EGlobal.position;
	}

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

void	framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}
