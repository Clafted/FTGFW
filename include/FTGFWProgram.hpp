#pragma once
#ifndef FTGFWPROGRAM_H
#define FTGFWPROGRAM_H

#include <iostream>
#include <string>

#include "managers/SceneManager.hpp"
#include "managers/SystemManager.hpp"
#include "managers/ComponentManager.hpp"
#include "managers/EntityManager.hpp"

#include "systems/ControllerSystem.hpp"
#include "systems/RenderSystem.hpp"

struct GLFWwindow;
/**
 * A Singleton class to manage the life-cycle of the FTGFW program.
 * 
 * This includes setting up GLAD and GLFW, managing the
 * GLFW window, and running the render and update loop. */
class FTGFWProgram {
public:
	GLFWwindow* window = nullptr;
	unsigned int screenWidth = 1280, screenHeight = 720;
	unsigned int frameCount = 0;

	ComponentManager componentManager;
	EntityManager entityManager;
	SceneManager sceneManager = SceneManager(componentManager, window);
	SystemManager systemManager;

	std::shared_ptr<RenderSystem> renderSystem = std::make_shared<RenderSystem>();
	std::shared_ptr<ControllerSystem> controllerSystem = std::make_shared<ControllerSystem>();

	~FTGFWProgram();

	/** 
	 * Initializes GLFW and GLAD
	 * @returns -1 if there are any issues in initializing GLAD or GLFW, 0 otherwise. */
	int initProgram(int screenWidth, int screenHeight, const char* windowName);

	/**
	 * Begin the render loop with the given starting-scene and shaders.
	 * NOTE: Before calling this method, make sure to have called initProgram() successfully.
	 * @seealso initProgram()
	 * @param startingScene - a pointer to the Scene object to initialize with */
	int initRenderLoop(std::string startingScene, std::string vertexShaderPath, std::string fragmentShaderPath);

private:

	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	double previousTime = 0.0, deltaTime = 0.0;
	int glfwSetup(const char * windowName);
	int gladSetup();
};
#endif