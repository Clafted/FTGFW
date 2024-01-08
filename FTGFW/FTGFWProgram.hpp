#pragma once
#ifndef FTGFWPROGRAM_H
#define FTGFWPROGRAM_H

#include <iostream>

#include "./openGLObjects/GLIncludes.hpp"
#include "scene/Scene.hpp"
#include "scene/SceneManager.hpp"
#include "scene/Renderer.hpp"

/**
 * A Singleton class to manage the life-cycle of the FTGFW program.
 * 
 * This includes setting up GLAD and GLFW, managing the
 * GLFW window, and running the render and update loop. 
 */
class FTGFWProgram {
public:
	Renderer* renderer = nullptr;
	SceneManager* sceneManager = nullptr;
	GLFWwindow* window = nullptr;
	unsigned int screenWidth = 1280, screenHeight = 720;
	unsigned int frameCount = 0;

	~FTGFWProgram() {
		std::cout << "Average frame rate: " << frameCount / glfwGetTime() << " FPS";
		// Free resouces and terminate program
		glfwTerminate();
	}

	static FTGFWProgram* Instance() {
		if (!instance) instance = new FTGFWProgram();
		return instance;
	}

	static void terminate() { delete instance; }

	/* Initializes GLFW and GLAD
	* 
	* @returns -1 if there are any issues in initializing GLAD or GLFW, 0 otherwise. */
	int initProgram() {
		return ((glfwSetup() == -1 || gladSetup() == -1) ? -1 : 0);
	}

	/**
	 * Begin the render loop with the given starting-scene.
	 *
	 * @param startingScene - a pointer to the Scene object to initialize with */
	int initRenderLoop(std::string startingScene);

private:

	static FTGFWProgram* instance;

	FTGFWProgram() {}

	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		SceneManager::Instance()->getCurrentScene()->setScreenDimensions(width, height);
	}
	int glfwSetup();
	int gladSetup();
};
#endif