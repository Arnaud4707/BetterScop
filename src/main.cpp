#include "../include/header.hpp" 

Camera		cam(vec3(0.7f, 1.5f, 8.7f));
float		deltaTime = 0.0f;	// Time between current frame and last frame
float		lastFrame = 0.0f;
bool autoRot = true;
bool wareFrame = false;
float factor = 1.0;
bool onTexture = false;

Material	emerald;
Material	jade;
Material	obsidian;
Material	pearl;
Material	ruby;
Material	turquoise;
Material	brass;
Material	bronze;
Material	chrome;
Material	copper;
Material	gold;
Material	silver;
Material	black_plastic;
Material	cyan_plastic;
Material	green_plastic;
Material	red_plastic;
Material	white_plastic;
Material	yellow_plastic;
Material	black_rubber;
Material	cyan_rubber;
Material	green_rubber;
Material	red_rubber;
Material	white_rubber;
Material	yellow_rubber;
Light		light;

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	int nmonitor;
	GLFWmonitor** monitor = glfwGetMonitors(&nmonitor);
	const GLFWvidmode* mode = glfwGetVideoMode(monitor[0]);
 
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	GLFWwindow *window = glfwCreateWindow(mode->width * 0.8, mode->height * 0.8, "Audio Animation", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, mode->width * 0.8f, mode->height * 0.8f);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	Shader ourShader("shader/shaderObjectSansNetT.vs", "shader/shaderObjectSansNetT.fs");
	glfwSetWindowUserPointer(window, &ourShader);
	glfwSetCursorPosCallback(window, Shader::mouse_callback_wrapper);
	Shader lightCubeShader("shader/shaderLightCube.vs", "shader/shaderLightCube.fs");
	unsigned int VAO[1];
	unsigned int lightVAO[1];
	unsigned int VBO[2];
	unsigned int texture1;
	// unsigned int texture2;
	ourShader.setDeltaTime(0.005);
	ourShader.setRotationSpeed(2.0);
	ObjectBlender obj("42.obj", "42.mtl");
	std::string pathFFT = "csv/meek_Mill_Rico_ftdrake/csv_from_fft/";
	std::string pathMidi = "csv/meek_Mill_Rico_ftdrake/csv_from_midi/";
	MusicEngine engine(pathFFT + "bass_fft.csv", pathFFT + "drums_fft.csv", pathFFT + "guitar_fft.csv", pathFFT + "piano_fft.csv", pathFFT + "other_fft.csv", pathFFT + "vocals_fft.csv"
				, pathMidi + "bass.csv", pathMidi + "drums.csv", pathMidi + "guitar.csv", pathMidi + "piano.csv", pathMidi + "other.csv", pathMidi + "vocals.csv");
	texture1 = loadTexture((char const *)("texture/container.jpg"));
	// texture2 = loadTexture((char const *)("texture/basketball.png"));
	ourShader.use();
	ourShader.setInt("t.specular", 0);
	vec3 c = centerObj(&obj);
	ourShader.setVec3("color", vec3(1.0f));
	// vertexdf(window, &obj, VBO, VAO, lightVAO, 2);
	vertexSansNT(window, &obj, VBO, VAO, lightVAO, 2);
	glEnable(GL_DEPTH_TEST);
	// glDisable(GL_CULL_FACE);
	
	mat4 projection;
	mat4 view;
	mat4 model;
	model = mat4(1.0f);
	cam.ProcessMouseMovement(-74.033f, -104.846f, true);
	initMaterials();
	light.position = vec3 (1.2f, 1.0f, 2.0f);
	light.ambient = vec3 (1.0f, 1.0f, 1.0f);
	light.diffuse = vec3 (1.0f, 1.0f, 1.0f);
	light.specular = vec3 (1.0f, 1.0f, 1.0f);
	// light.ambient = vec3 (0.15f, 0.15f, 0.15f);
	// light.diffuse = vec3 (0.8f, 0.8f, 0.8f);
	// light.specular = vec3 (0.35f, 0.35f, 0.35f);
	for (auto &m : obj.getKey()){
		std::string ambient = "material[" + std::to_string(m.second) + "].ambient";
		std::string diffuse = "material[" + std::to_string(m.second) + "].diffuse";
		std::string specular = "material[" + std::to_string(m.second) + "].specular";
		std::string shininess = "material[" + std::to_string(m.second) + "].shininess";
		const std::map<int, lightning>& material = obj.getMaterials();
		ourShader.use();
		ourShader.setVec3(ambient, material.at(m.second).ambient);
		ourShader.setVec3(diffuse, material.at(m.second).diffuse);
		ourShader.setVec3(specular, material.at(m.second).specular);
		ourShader.setFloat(shininess, material.at(m.second).shininess);

	}
	ourShader.use();
	// for none mat0
	// ourShader.setVec3("material.ambient", mat.ambient);
	// ourShader.setVec3("material.diffuse", mat.diffuse);
	// ourShader.setVec3("material.specular", mat.specular);
	// ourShader.setFloat("material.shininess", mat.shininess);
	int ch = fork();
	if (ch == 0){
		system("paplay audio/meek_Mill_Rico_ftdrake/meek_Mill_Rico_ftdrake.mp3");
		exit(0);
	}
	std::cout << "ici" << std::endl;
	std::array<const AudioStats*, 6> cpAudioStats = {&engine.bass_fft.stats, &engine.drums_fft.stats, &engine.guitar_fft.stats
		, &engine.piano_fft.stats, &engine.other_fft.stats, &engine.vocals_fft.stats};
	MusicAnalyzer anayser(cpAudioStats);
	AnimationEngine engineAnime;
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
    	processInput(window, &deltaTime, &ourShader, &cam);
    	// processInput(window, &deltaTime, &goldShaderpaplay audio/meek_Mill_Rico_ftdrake.mp3, &cam);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// float rotation = 0.0f;

		MusicState track = engine.update(currentFrame);
		anayser.update(track.bass, BASS);
		anayser.update(track.drums, DRUMS);
		anayser.update(track.guitar, GUITAR);
		anayser.update(track.piano, PIANO);
		anayser.update(track.other, OTHER);
		anayser.update(track.vocals, VOCALS);
		anayser.updateGlobal(track);
		AnimationState state = engineAnime.update(track, deltaTime);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		// glActiveTexture(GL_TEXTURE1);
		// glBindTexture(GL_TEXTURE_2D, texture2);
		objectAndLight(&ourShader, &model, &view, &projection, mode->width, mode->height, vec3(c.x, c.y, c.z), state);
		// render the cube
		
		ourShader.setVec3("color", state.color);
		ourShader.setFloat("glow", state.glow);
		glBindVertexArray(VAO[0]);
		// glDrawElements(GL_TRIANGLES, 3 * obj.getdF().size(), GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, obj.getVertexs().size());

		if (autoRot){
			// ourShader.setRotY(ourShader.getRotY() + (ourShader.getRotationSpeed() * ourShader.getDeltaTime()));
			// ourShader.setRotY(ourShader.getRotY() + (radians(ourShader.getRotationSpeed() * rotation)));
			// ourShader.setRotY(ourShader.getRotY() + deltaTime * animation.piano.pitch * 0.015f);
			ourShader.setRotX(ourShader.getRotX() + deltaTime * track.piano.pitch * 0.0015);
			ourShader.setRotY(ourShader.getRotY() + state.rotationSpeed * 0.15);
		}
        // also draw the lamp object
        lightCubeShader.use();
		lightCubeShader.setVec3("light", light.specular);
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = mat4(1.0f);
        model = translate(model, light.position);
        model = scale(model, vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightVAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    glDeleteProgram(ourShader.ID);
    // glDeleteProgram(goldShader.ID);
	glfwTerminate();
	return 0;
}