#include "FTGFWProgram.hpp"
#include "../third_party/GLIncludes.hpp"
#include "systems/KinematicSystem.hpp"
#include "systems/CameraSystem.hpp"
#include "systems/CollisionSystem.hpp"

FTGFWProgram::~FTGFWProgram() {
	glfwTerminate();
}

int FTGFWProgram::initProgram(int screenWidth, int screenHeight, const char* windowName) {
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	if (glfwSetup(windowName) == -1 || gladSetup() == -1) return -1;
	// Register Render and Controller Systems
	systemManager.registerSystem(renderSystem);
	systemManager.registerSystem(controllerSystem);
	systemManager.registerSystem(std::make_shared<KinematicSystem>(componentManager, sceneManager));
	systemManager.registerSystem(std::make_shared<CameraSystem>(componentManager, sceneManager));
	systemManager.registerSystem(std::make_shared<CollisionSystem>(componentManager, sceneManager));

	return 0;
}

int FTGFWProgram::initRenderLoop(std::string startingScene, std::string vertexShaderPath, std::string fragmentShaderPath) 
{
	sceneManager.setScene(startingScene);
	renderSystem->addShader(vertexShaderPath, fragmentShaderPath);
	// Start loop
	// ---------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window)) 
	{
		// Update time variables
		deltaTime = glfwGetTime() - previousTime;
		previousTime = glfwGetTime();
		if (deltaTime >= 0.15f) deltaTime = 0.15;
		// Take input
		glfwPollEvents();
		// Update all Systems
		systemManager.update(window, deltaTime);
		frameCount++;
	}
	std::cout << "\nTerminating FTGFWProgram...\n"
			  << "Runtime: " << glfwGetTime() << "\n"
			  << "FPS: ~" << frameCount / glfwGetTime() << std::flush;	

	return 0;
}

void FTGFWProgram::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int FTGFWProgram::glfwSetup(const char * windowName) 
{
	// Initial GLFW configuration
	// -----------------------------------------------------
	if (glfwInit() == GLFW_FALSE) 
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create a GLFW window
	// ----------------------------------------------------
	window = glfwCreateWindow(screenWidth, screenHeight, windowName, NULL, NULL);
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Set callbacks
	// -----------------------------------------------------
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glfwSetMouseButtonCallback(window, ControllerSystem::mouseButtonCallback);
	return 0;
}

int FTGFWProgram::gladSetup() {
	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	return 0;
}