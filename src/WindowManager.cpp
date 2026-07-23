#include "../include/WindowManager.hpp"

void	WindowManager::initShader()
{
	Shader ourShader("shader/shaderObjectSansNetT.vs", "shader/shaderObjectSansNetT.fs");
	shaderObject = ourShader;
	Shader lightCubeShader("shader/shaderLightCube.vs", "shader/shaderLightCube.fs");
	shaderLight = lightCubeShader;

	shaderObject.setDeltaTime(0.005);
	shaderObject.setRotationSpeed(2.0);
}

void	WindowManager::initObjetBlender()
{
	ObjectBlender obj("42.obj", "42.mtl");
	object = obj;
	vec3 c = centerObj(&object);
			shaderObject.setVec3("color", vec3(1.0f));
			// vertexdf(window, &obj, VBO, VAO, lightVAO, 2);
			vertexSansNT(window3D, &obj, render.VBO, render.VAO, render.lightVAO, 2);
}

void	WindowManager::init3D()
{
	glEnable(GL_DEPTH_TEST);
	// glDisable(GL_CULL_FACE);

	render.model = mat4(1.0f);
	cam.ProcessMouseMovement(-74.033f, -104.846f, true);
	initMaterials();

	light.position = vec3(1.2f, 1.0f, 2.0f);
	light.ambient = vec3(1.0f, 1.0f, 1.0f);
	light.diffuse = vec3(1.0f, 1.0f, 1.0f);
	light.specular = vec3(1.0f, 1.0f, 1.0f);
	// light.ambient = vec3 (0.15f, 0.15f, 0.15f);
	// light.diffuse = vec3 (0.8f, 0.8f, 0.8f);
	// light.specular = vec3 (0.35f, 0.35f, 0.35f);
	for (auto &m : object.getKey())
	{
		std::string ambient = "material[" + std::to_string(m.second) + "].ambient";
		std::string diffuse = "material[" + std::to_string(m.second) + "].diffuse";
		std::string specular = "material[" + std::to_string(m.second) + "].specular";
		std::string shininess = "material[" + std::to_string(m.second) + "].shininess";
		const std::map<int, lightning> &material = object.getMaterials();
		shaderObject.use();
		shaderObject.setVec3(ambient, material.at(m.second).ambient);
		shaderObject.setVec3(diffuse, material.at(m.second).diffuse);
		shaderObject.setVec3(specular, material.at(m.second).specular);
		shaderObject.setFloat(shininess, material.at(m.second).shininess);
	}
	shaderObject.use();
	// for none mat0
	// ourShader.setVec3("material.ambient", mat.ambient);
	// ourShader.setVec3("material.diffuse", mat.diffuse);
	// ourShader.setVec3("material.specular", mat.specular);
	// ourShader.setFloat("material.shininess", mat.shininess);
}

void WindowManager::initAudio()
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

void	WindowManager::initMusicAnayzer()
{
	std::array<const AudioStats *, 6> cpAudioStats = {&musicEngine.bass_fft.stats, &musicEngine.drums_fft.stats, &musicEngine.guitar_fft.stats, &musicEngine.piano_fft.stats, &musicEngine.other_fft.stats, &musicEngine.vocals_fft.stats};
	MusicAnalyzer analyser(cpAudioStats);
	analyzer = analyser;
}

void	WindowManager::initwindow(GLFWwindow* window, const GLFWvidmode *mode)
{
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	window = glfwCreateWindow(mode->width * 0.8, mode->height * 0.8, "Audio Animation", NULL, NULL);
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
	glViewport(0, 0, mode->width * 0.8f, mode->height * 0.8f);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void	WindowManager::initTexture()
{
	// unsigned int texture2;
	render.texture1 = loadTexture((char const *)("texture/container.jpg"));
	// texture2 = loadTexture((char const *)("texture/basketball.png"));
	shaderObject.use();
	shaderObject.setInt("t.specular", 0);
}

//after initShader()
void WindowManager::mouseEvent()
{
	glfwSetWindowUserPointer(window3D, &shaderObject);
	glfwSetCursorPosCallback(window3D, Shader::mouse_callback_wrapper);	
}

void	WindowManager::updateMusicEngine()
{

}