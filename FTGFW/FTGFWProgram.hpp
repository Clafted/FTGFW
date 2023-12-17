#pragma once
#ifndef FTGFWPROGRAM_H
#define FTGFWPROGRAM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Shader.hpp"

class FTGFWProgram {
public:
	GLFWwindow* window = nullptr;
	Shader* shader = nullptr;
	unsigned int screenWidth = 800, screenHeight = 600;
	unsigned int frameCount = 0;

	FTGFWProgram() {}

	~FTGFWProgram() {
		std::cout << "Average frame rate: " << frameCount / glfwGetTime() << " FPS";
		// Free resouces and terminate program
		delete shader;
		glfwTerminate();
	}

	/**
	 * Initializes GLFW and GLAD 
	 */
	int initProgram() {
		if (glfwSetup() == -1) return -1;
		if (gladSetup() == -1) return -1;
		return 0;
	}

	/**
	 * Begin the render loop with the given starting-scene.
	 *
	 * @param startingScene - a pointer to the Scene object to initialize with
	 */
	int initRenderLoop(Scene* startingScene) {
		glm::mat4 model;
		glm::mat4 projection;
		glm::mat4 view;

		SceneManager::Instance()->setStartScene(startingScene);
		
		// Use Shaders
		shader = new Shader("vertex.vert", "fragment.frag");
		glEnable(GL_DEPTH_TEST);
		glUseProgram(shader->ID);

		// Create perspective transformation matrix
		projection = glm::perspective(glm::pi<float>() / 4.0f, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
		// Start loop
		// ---------------------------------------------------------------------------
		Scene* currentScene;
		while (!glfwWindowShouldClose(window)) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			currentScene = SceneManager::Instance()->getCurrentScene();
			// Update the camera's (view) transformation matrix
			currentScene->camera.pos = glm::vec3(0.0f, 0.0f, 0.5f * glfwGetTime());
			view = currentScene->camera.lookAt();
	
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
			// Render every Entity
			// ------------------------------------------------------------------------------------------
			for (Entity* entity : currentScene->entities) {
				// Create model transformation matrix (NOTE: Order of calculations is SCALE, ROTATE, then TRANSLATE)
				model = glm::translate(glm::mat4(1.0f), entity->pos);
				model = glm::rotate(model, entity->rotationAngle, entity->rotationAxis);
				// Update model transformation matrix
				glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
				// Render
				entity->vao.bindObject();
				entity->texture.bindObject();
				glDrawArrays(GL_TRIANGLES, 0, entity->vbo.getNumVertices());
			}
			
			SceneManager::Instance()->update();
			glfwSwapBuffers(window);
			glfwPollEvents();
			frameCount++;
		}
		return 0;
	}

private:
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	int glfwSetup() {
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

	int gladSetup() {
		// Initialize GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}
		return 0;
	}
};
#endif