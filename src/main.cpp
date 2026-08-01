#include "../include/WindowManager.hpp" 

int main(void)
{
	WindowManager windowManager;

	windowManager.initShader();
	windowManager.initObjetBlender();
	windowManager.initTexture();
	windowManager.init3D();
	windowManager.initMusicEngine();
	windowManager.initMusicAnayzer();
	windowManager.startAudio();

	while (!glfwWindowShouldClose(windowManager.getWindow()))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		windowManager.updateMusicEngine(currentFrame);
		windowManager.updateMusicAnalyzer();
		windowManager.updateAnimationEngine(currentFrame);
		windowManager.updateRender();
		windowManager.updateVisualizer();
		glfwSwapBuffers(windowManager.getWindow());
		glfwPollEvents();
	}
	windowManager.destroyWindow();
	return 0;
}