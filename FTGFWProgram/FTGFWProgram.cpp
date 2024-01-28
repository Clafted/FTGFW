#include "FTGFWProgram.hpp"
#include "../third_party/GLIncludes.hpp"
#include "scene/Scene.hpp"
#include "scene/SceneManager.hpp"
#include "scene/Renderer.hpp"
#include "component/InputManager.hpp"

FTGFWProgram* FTGFWProgram::instance = nullptr;
InputManager* InputManager::instance = nullptr;

FTGFWProgram::~FTGFWProgram() {
	
}

int FTGFWProgram::initProgram(int screenWidth, int screenHeight, const char* windowName) {
	Renderer::Instance();
	SceneManager::Instance();
	InputManager::Instance();
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	return ((glfwSetup(windowName) == -1 || gladSetup() == -1) ? -1 : 0);
}

void FTGFWProgram::terminate() {
	SceneManager::terminate();
	Renderer::terminate();
	InputManager::terminate();
	
	delete instance;
}

int FTGFWProgram::initRenderLoop(const char* startingScene, const char* vertexShaderPath, const char* fragmentShaderPath) {

	renderer = Renderer::Instance();
	renderer->addShader(vertexShaderPath, fragmentShaderPath);
	if (renderer->shader == nullptr) return -1;
	sceneManager = SceneManager::Instance();
	sceneManager->setScene(startingScene);
	sceneManager->getCurrentScene()->setScreenDimensions(screenWidth, screenHeight);
	glEnable(GL_BLEND);
	// Start loop
	// ---------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window)) {

		// Take input and update 
		glfwPollEvents();
		InputManager::Instance()->update();
		sceneManager->getCurrentScene()->update(window);
		renderer->updateMatrices(sceneManager->getCurrentScene()->camera->lookAt(), sceneManager->getCurrentScene()->camera->projectionMatrix, sceneManager->getCurrentScene()->camera->kinematic.pos);
		renderer->renderFrame(window);

		frameCount++;
	}
	
	std::cout << "Terminating FTGFWProgram...\nRuntime: " << glfwGetTime() << "\nFPS: ~" << instance->frameCount / glfwGetTime();
	glfwTerminate();
	return 0;
}

void FTGFWProgram::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	SceneManager::Instance()->getCurrentScene()->setScreenDimensions(width, height);
}

int FTGFWProgram::glfwSetup(const char * windowName) {
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
	window = glfwCreateWindow(screenWidth, screenHeight, windowName, NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Set callbacks
	// -----------------------------------------------------
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glfwSetMouseButtonCallback(window, InputManager::mouseButtonCallback);
	glfwSetCursorPosCallback(window, InputManager::cursorPosCallback);
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