#include "../include/header.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"


vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;

float vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, float *delta, Shader* ourShader, Camera *camera)
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

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		light.position.y += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		light.position.y -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		light.position.x += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		light.position.x -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		light.position.z += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		light.position.z -= 0.05f;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	(void)xoffset;
	(void)window;
	cam.ProcessMouseScroll(static_cast<float>(yoffset));
}

void transform4(Shader *ourShader)
{
	for (unsigned int i = 0; i < 10; i++)
	{
		mat4 model = mat4(1.0f);
		model = translate(model, vec3(0.0f, 0.0f, 0.0f));
		float angle = 20.0f * i;
		if (i % 3 == 0)
			model = rotate(model, (float)glfwGetTime() * 2.0f, vec3(1.0f, 0.3f, 0.5f));
		else
			model = rotate(model, radians(angle), vec3(1.0f, 0.3f, 0.5f));
		ourShader->setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

unsigned int loadTexture(char const * path)
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

void	print_vertex(ObjectBlender* obj)
{
	std::vector<vertex> vv = obj->getVertexs();
	std::vector<face> ff = obj->getF();
	for (auto &dispay : ff){
		// std::cout << "x : " << dispay.normal.x << " y: " << dispay.normal.y << " z: " << dispay.normal.z << std::endl;
		std::cout << " x: " << vv[dispay.x].normal.x << " y: " << vv[dispay.x].normal.y << " z: " << vv[dispay.x].normal.z << std::endl;
		std::cout << " x: " << vv[dispay.y].normal.x << " y: " << vv[dispay.y].normal.y << " z: " << vv[dispay.y].normal.z << std::endl;
		std::cout << " x: " << vv[dispay.z].normal.x << " y: " << vv[dispay.z].normal.y << " z: " << vv[dispay.z].normal.z << std::endl;
	}
}

void vertexf(GLFWwindow *window, ObjectBlender* obj, unsigned int *VBO, unsigned int *VAO, unsigned int *lightVAO, int size)
{
	std::vector<float> tabVertex;
	for (auto &v : obj->getVertexs())
	{
		tabVertex.push_back(v.position.x);
		tabVertex.push_back(v.position.y);
		tabVertex.push_back(v.position.z);
		tabVertex.push_back(v.normal.x);
		tabVertex.push_back(v.normal.y);
		tabVertex.push_back(v.normal.z);
		tabVertex.push_back(v.texcoord.x);
		tabVertex.push_back(v.texcoord.y);
	}
	// for (auto &v : obj->getV())
	// {
	//     tabVertex.push_back(v.x);
	//     tabVertex.push_back(v.y);
	//     tabVertex.push_back(v.z);
	// }

	(void)window;
	glGenBuffers(size, VBO);

	glGenVertexArrays(1, VAO);

	glBindVertexArray(VAO[0]);
	// 2. copy our first_triangle array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, tabVertex.size() * sizeof(float), tabVertex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenVertexArrays(1, lightVAO);

	glBindVertexArray(lightVAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// set the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
}

void vertexdf(GLFWwindow *window, ObjectBlender* obj, unsigned int *VBO, unsigned int *VAO, unsigned int *lightVAO, int size)
{
	std::vector<float> tabVertex;
	for (auto &v : obj->getVertexs())
	{
		tabVertex.push_back(v.position.x);
		tabVertex.push_back(v.position.y);
		tabVertex.push_back(v.position.z);
		tabVertex.push_back(v.normal.x);
		tabVertex.push_back(v.normal.y);
		tabVertex.push_back(v.normal.z);
		tabVertex.push_back(v.texcoord.x);
		tabVertex.push_back(v.texcoord.y);
		tabVertex.push_back((v.idMaterial));
	}
	(void)window;
	glGenBuffers(size, VBO);

	glGenVertexArrays(1, VAO);

	glBindVertexArray(VAO[0]);
	// 2. copy our first_triangle array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, tabVertex.size() * sizeof(float), tabVertex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glGenVertexArrays(1, lightVAO);

	glBindVertexArray(lightVAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// set the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
}


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

void	materialAndLight(Shader* ourShader, mat4* model, mat4* view, mat4* projection, int width, int height, Material mat, vec3 pos)
{
	ourShader->use();
	ourShader->setVec3("light.position", light.position);
	ourShader->setVec3("material.ambient", mat.ambient);
	ourShader->setVec3("material.diffuse", mat.diffuse);
	ourShader->setVec3("material.specular", mat.specular);
	ourShader->setFloat("material.shininess", mat.shininess);
	ourShader->setVec3("light.ambient",  light.ambient);
	ourShader->setVec3("light.diffuse",  light.diffuse); // darken diffuse light a bit
	ourShader->setVec3("light.specular", light.specular); 
	// view/projection transformations
	*projection = perspective(radians(cam.Zoom), (float)(width * 0.8) / (float)(height * 0.8), 0.1f, 100.0f);
	*view = cam.GetViewMatrix();
	ourShader->setMat4("projection", *projection);
	ourShader->setMat4("view", *view);
	ourShader->setVec3("viewPos", cam.Position);

	// world transformation
    *model = mat4(1.0f);
    *model = translate(*model, pos);
    *model = scale(*model, vec3(INIT_SCALE_OBJ)); 
	*model = rotate(*model, ourShader->getRotY(), vec3(0.0f, 1.0f, 0.0f));
	*model = rotate(*model, ourShader->getRotX(), vec3(1.0f, 0.0f, 0.0f));
	ourShader->setMat4("model", *model);
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

void	objectAndLight(Shader* ourShader, mat4* model, mat4* view, mat4* projection, int width, int height, vec3 pos, MusicState& anime)
{
	ourShader->use();
	ourShader->setVec3("light.position", light.position);
	ourShader->setFloat("factor", factor);
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
	// ourShader->setVec3("lightObj.ambient", lightObj.ambient);
	// ourShader->setVec3("lightObj.diffuse", lightObj.diffuse);
	// ourShader->setVec3("lightObj.specular", lightObj.specular);
	// ourShader->setFloat("lightObj.shininess", lightObj.shininess);
	ourShader->setVec3("light.ambient",  light.ambient);
	ourShader->setVec3("light.diffuse",  light.diffuse); // darken diffuse light a bit
	ourShader->setVec3("light.specular", light.specular); 
	// view/projection transformations
	*projection = perspective(radians(cam.Zoom), (float)(width * 0.8) / (float)(height * 0.8), 0.1f, 100.0f);
	*view = cam.GetViewMatrix();
	ourShader->setMat4("projection", *projection);
	ourShader->setMat4("view", *view);
	ourShader->setVec3("viewPos", cam.Position);

	// world transformation
    *model = mat4(1.0f);
	*model = translate(*model, pos);
	*model = rotate(*model, ourShader->getRotY(), vec3(0.0f, 1.0f, 0.0f));
	*model = rotate(*model, ourShader->getRotX(), vec3(1.0f, 0.0f, 0.0f));
	*model = translate(*model, -pos);
	*model = translate(*model, vec3(0.0f));
    *model = scale(*model, vec3(INIT_SCALE_OBJ) + (anime.bass.rms * 4.0f));

	ourShader->setMat4("model", *model);

}