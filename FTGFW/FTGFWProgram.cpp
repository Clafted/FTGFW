#include "FTGFWProgram.hpp"
#include "third_party/GLIncludes.hpp"
#include "scene/Scene.hpp"
#include "scene/SceneManager.hpp"
#include "scene/Renderer.hpp"

FTGFWProgram* FTGFWProgram::instance = nullptr;

int FTGFWProgram::initRenderLoop(std::string startingScene) {

	renderer = renderer->Instance();
	sceneManager = SceneManager::Instance();
	sceneManager->setScene(startingScene);

	// Start loop
	// ---------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window)) {

		// Take input and update 
		glfwPollEvents();
		sceneManager->getCurrentScene()->update(window);
		renderer->updateMatrices(sceneManager->getCurrentScene()->camera->lookAt(), sceneManager->getCurrentScene()->camera->projectionMatrix, sceneManager->getCurrentScene()->camera->kinematic.pos);
		renderer->renderFrame(window);

		frameCount++;
	}
	return 0;
}

void FTGFWProgram::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	SceneManager::Instance()->getCurrentScene()->setScreenDimensions(width, height);
}

int FTGFWProgram::glfwSetup() {
	// Initial GLFW configuration
	// -----------------------------------------------------
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create a GLFW window
	// ----------------------------------------------------
	window = glfwCreateWindow(screenWidth, screenHeight, "FTGFW", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Set callbacks
	// -----------------------------------------------------
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	return 0;
}

int FTGFWProgram::gladSetup() {
	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	return 0;
}