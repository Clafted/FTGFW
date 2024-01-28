#pragma once
#ifndef FTGFWPROGRAM_H
#define FTGFWPROGRAM_H

#include <iostream>

class Renderer;
class SceneManager;
struct GLFWwindow;
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

	~FTGFWProgram();

	static FTGFWProgram* Instance() {
		if (!instance) instance = new FTGFWProgram();
		return instance;
	}

	static void terminate();

	/* Initializes GLFW and GLAD
	 * 
	 * @returns -1 if there are any issues in initializing GLAD or GLFW, 0 otherwise. 
	 */
	int initProgram(int screenWidth, int screenHeight, const char* windowName);

	/**
	 * Begin the render loop with the given starting-scene.
	 *
	 * @param startingScene - a pointer to the Scene object to initialize with 
	 */
	int initRenderLoop(const char* startingScene, const char* vertexShaderPath, const char* fragmentShaderPath);

private:

	static FTGFWProgram* instance;

	FTGFWProgram() {}

	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	int glfwSetup(const char * windowName);
	int gladSetup();
};
#endif