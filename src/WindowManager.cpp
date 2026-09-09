#include "../include/WindowManager.hpp"

void	WindowManager::initShader()
{
	Shader ourShader("shader/shaderObjectSansNetT.vs", "shader/shaderObjectSansNetT.fs");
	app.shaderObject = ourShader;
	
	Shader lightCubeShader("shader/shaderLightCube.vs", "shader/shaderLightCube.fs");
	app.shaderLight = lightCubeShader;

	Shader shaderVisualizer("shader/shaderVisualizer.vs", "shader/shaderVisualizer.fs");
	visualizer.shaderObject = shaderVisualizer;

	app.shaderObject.setDeltaTime(0.005);
	app.shaderObject.setRotationSpeed(2.0);
}

void	WindowManager::initObjetBlender()
{
	ObjectBlender obj("42.obj", "42.mtl");
	app.object = obj;
	app.render.centerObject = centerObj(&app.object);
			app.shaderObject.setVec3("color", vec3(1.0f));
			// vertexdf(window, &obj, VBO, VAO, lightVAO, 2);
			vertexSansNT(window, &app.object, app.render.VBO, app.render.VAO, app.render.lightVAO, 2);
}

void WindowManager::initVisualizer()
{
	EGlobal.position = vec3(-2.4f, 5.0f, 0.0f);
	EGlobal.color = vec3(0.7, 0.7, 0.3);
	recVisualizer(window, visualizer.render.VBO, visualizer.render.VAO, 1);
	visualizer.render.projection = perspective(radians(45.f), visualizer.width / height, 0.1f, 100.f);
	visualizer.render.view = cam.GetViewMatrix();
	visualizer.shaderObject.use();
	visualizer.shaderObject.setMat4("projection", visualizer.render.projection);
    visualizer.shaderObject.setMat4("view", visualizer.render.view);

}

void	WindowManager::init3D()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	// glDisable(GL_CULL_FACE);

	app.render.model = mat4(1.0f);
	cam.ProcessMouseMovement(-74.033f, -104.846f, true);
	initMaterials();

	light.position = vec3(1.2f, 1.0f, 2.0f);
	light.ambient = vec3(1.0f, 1.0f, 1.0f);
	light.diffuse = vec3(1.0f, 1.0f, 1.0f);
	light.specular = vec3(1.0f, 1.0f, 1.0f);
	// light.ambient = vec3 (0.15f, 0.15f, 0.15f);
	// light.diffuse = vec3 (0.8f, 0.8f, 0.8f);
	// light.specular = vec3 (0.35f, 0.35f, 0.35f);
	for (auto &m : app.object.getKey())
	{
		std::string ambient = "material[" + std::to_string(m.second) + "].ambient";
		std::string diffuse = "material[" + std::to_string(m.second) + "].diffuse";
		std::string specular = "material[" + std::to_string(m.second) + "].specular";
		std::string shininess = "material[" + std::to_string(m.second) + "].shininess";
		const std::map<int, lightning> &material = app.object.getMaterials();
		app.shaderObject.use();
		app.shaderObject.setVec3(ambient, material.at(m.second).ambient);
		app.shaderObject.setVec3(diffuse, material.at(m.second).diffuse);
		app.shaderObject.setVec3(specular, material.at(m.second).specular);
		app.shaderObject.setFloat(shininess, material.at(m.second).shininess);
	}
	// app.shaderObject.use();
	// for none mat0
	// ourShader.setVec3("material.ambient", mat.ambient);
	// ourShader.setVec3("material.diffuse", mat.diffuse);
	// ourShader.setVec3("material.specular", mat.specular);
	// ourShader.setFloat("material.shininess", mat.shininess);
}

void WindowManager::startAudio()
{
	int ch = fork();
	if (ch == 0)
	{
		system("paplay audio/meek_Mill_Rico_ftdrake/meek_Mill_Rico_ftdrake.mp3");
		exit(0);
	}
}

void	WindowManager::initMusicEngine()
{
	std::string pathFFT = "csv/meek_Mill_Rico_ftdrake/csv_from_fft/";
	std::string pathMidi = "csv/meek_Mill_Rico_ftdrake/csv_from_midi/";
	MusicEngine engine(pathFFT + "bass_fft.csv", pathFFT + "drums_fft.csv", pathFFT + "guitar_fft.csv", pathFFT + "piano_fft.csv", pathFFT + "other_fft.csv", pathFFT + "vocals_fft.csv"
				, pathMidi + "bass.csv", pathMidi + "drums.csv", pathMidi + "guitar.csv", pathMidi + "piano.csv", pathMidi + "other.csv", pathMidi + "vocals.csv");
	musicEngine = engine;
}

//after initMusicEngine()
void	WindowManager::initMusicAnayzer()
{
	std::array<const AudioStats *, 6> cpAudioStats = {&musicEngine.bass_fft.stats, &musicEngine.drums_fft.stats, &musicEngine.guitar_fft.stats, &musicEngine.piano_fft.stats, &musicEngine.other_fft.stats, &musicEngine.vocals_fft.stats};
	MusicAnalyzer analyser(cpAudioStats);
	analyzer = analyser;
}

GLFWwindow*	WindowManager::initwindow(const GLFWvidmode *mode, std::string name)
{
	GLFWwindow* window = NULL;
	height = mode->height * percentWin;
	width = mode->width * percentWin;
	app.height = height;
	app.width = width / 2;
	// app.width = width;
	visualizer.height = app.height;
	visualizer.width = app.width;
	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}
	return (window);
}
//apter initShader()
void	WindowManager::initTexture()
{
	// unsigned int texture2;
	app.render.texture1 = loadTexture((char const *)("texture/container.jpg"));
	// texture2 = loadTexture((char const *)("texture/basketball.png"));
	app.shaderObject.use();
	app.shaderObject.setInt("t.specular", 0);
}

//after initShader()
void WindowManager::setPointerWindow(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, &app.shaderObject);
	glfwSetCursorPosCallback(window, Shader::mouse_callback_wrapper);	
}

void	WindowManager::updateMusicEngine(float currentFrame)
{
	track = musicEngine.update(currentFrame);
}

void	WindowManager::updateMusicAnalyzer()
{
	analyzer.update(track.bass, BASS);
	analyzer.update(track.drums, DRUMS);
	analyzer.update(track.guitar, GUITAR);
	analyzer.update(track.piano, PIANO);
	analyzer.update(track.other, OTHER);
	analyzer.update(track.vocals, VOCALS);
	analyzer.updateGlobal(track);
	analyzer.updateHistory(track.bass, BASS);
	analyzer.updateHistory(track.drums, DRUMS);
	analyzer.updateHistory(track.guitar, GUITAR);
	analyzer.updateHistory(track.piano, PIANO);
	analyzer.updateHistory(track.other, OTHER);
	analyzer.updateHistory(track.vocals, VOCALS);
}

void WindowManager::updateAnimationEngine(float deltaTime)
{
	state = animationEngine.update(track, deltaTime);
}

void WindowManager::updateRender()
{
	// glViewport(0, 0, app.width, app.height);
	glViewport(0, 0, width / 2, height);
	glScissor(0, 0, width / 2, height);
	processInputAnimation(window, &deltaTime, &app.shaderObject, &cam);
	// processInput(window, &deltaTime, &goldShaderpaplay audio/meek_Mill_Rico_ftdrake.mp3, &cam);

	glClearColor(app.color.x, app.color.y, app.color.z, app.color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, app.render.texture1);
	// glActiveTexture(GL_TEXTURE1);
	// glBindTexture(GL_TEXTURE_2D, texture2);
	objectAndLight(app, app.width, app.height, state);
	// render the cube
		
	app.shaderObject.setVec3("color", state.color);
	app.shaderObject.setFloat("glow", state.glow);
	glBindVertexArray(app.render.VAO[0]);
	// glDrawElements(GL_TRIANGLES, 3 * obj.getdF().size(), GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, app.object.getVertexs().size());

	if (autoRot){
		// ourShader.setRotY(ourShader.getRotY() + (ourShader.getRotationSpeed() * ourShader.getDeltaTime()));
		// ourShader.setRotY(ourShader.getRotY() + (radians(ourShader.getRotationSpeed() * rotation)));
		// ourShader.setRotY(ourShader.getRotY() + deltaTime * animation.piano.pitch * 0.015f);
		app.shaderObject.setRotX(app.shaderObject.getRotX() + deltaTime * track.piano.pitch * 0.0015);
		app.shaderObject.setRotY(app.shaderObject.getRotY() + state.rotationSpeed * 0.15);
	}
    // also draw the lamp object
    app.shaderLight.use();
	app.shaderLight.setVec3("light", light.specular);
    app.shaderLight.setMat4("projection", app.render.projection);
    app.shaderLight.setMat4("view", app.render.view);
    app.render.model = mat4(1.0f);
    app.render.model = translate(app.render.model, light.position);
    app.render.model = scale(app.render.model, vec3(0.2f)); // a smaller cube
    app.shaderLight.setMat4("model", app.render.model);

    glBindVertexArray(app.render.lightVAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

void WindowManager::destroyWindow()
{
	glDeleteVertexArrays(1, app.render.VAO);
	glDeleteBuffers(1, app.render.VBO);
	glDeleteProgram(app.shaderObject.ID);
	// glDeleteProgram(goldShader.ID);
	glfwTerminate();
}

void WindowManager::updateVisualizer(){
	glViewport(width / 2, 0, width / 2, height);
	glScissor(width / 2, 0, width / 2, height);

	processInputVisualizer(window, &deltaTime, &visualizer.shaderObject, &cam);
	glClearColor(visualizer.color.x, visualizer.color.y, visualizer.color.z, visualizer.color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	StatsHistory history;
	history.push(track);
	NormalizePeak np;
	visualizer.shaderObject.use();
	// for (int i = 0; i < 3; i++){
		float *tab = &track.global.energy;
		float x = np.normalizeGlobalEnergie(tab[2]);
    	visualizer.render.model = mat4(1.0f);
		vec3 p = EGlobal.position;
		p.y -= 1 * 0.5f; 
    	visualizer.render.model = translate(visualizer.render.model, p);
    	visualizer.render.model = scale(visualizer.render.model, vec3(x, 0.5f, 0.f)); // a smaller cube
		visualizer.shaderObject.setVec3("color", EGlobal.color * x);
    	visualizer.shaderObject.setMat4("model", visualizer.render.model);
		
		glBindVertexArray(visualizer.render.VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	// }
	// std::cout << "track.global.energy: " << track.global.energy << " track.global.beat: " << track.global.beat << " track.global.brightness: " << track.global.brightness << std::endl;
	// std::cout << "tab[0]: " << tab[0] << " tab[1]: " << tab[1] << " tab[2]: " << tab[2] << std::endl;
}
