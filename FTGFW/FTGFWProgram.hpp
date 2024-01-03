#pragma once
#ifndef FTGFWPROGRAM_H
#define FTGFWPROGRAM_H

#include "./openGLObjects/GLIncludes.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "scene/Scene.hpp"
#include "scene/SceneManager.hpp"
#include "shaders/Shader.hpp"

class FTGFWProgram {
public:
	GLFWwindow* window = nullptr;
	unsigned int screenWidth = 800, screenHeight = 600;
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

	static void terminate() { 
		SceneManager::terminate();
		delete instance; 
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
	 * @param startingScene - a pointer to the Scene object to initialize with */
	int initRenderLoop(Scene* startingScene) {
		glm::mat4 model;
		glm::mat4 projection;
		glm::mat4 view;

		SceneManager* sceneManager = SceneManager::Instance();
		sceneManager->setStartScene(startingScene);
		
		// Use Shaders
		Shader shader = Shader("./shaders/vertex.vert", "./shaders/fragment.frag");
		glEnable(GL_DEPTH_TEST);
		glUseProgram(shader.ID);

		shader.setInt("material.u_currentTexture", 0);
		shader.setInt("material.u_specularMap", 1);

		// Create perspective transformation matrix
		projection = glm::perspective(glm::pi<float>() / 4.0f, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		shader.setMat4("projection", projection);
		
		// Start loop
		// ---------------------------------------------------------------------------
		Scene* currentScene;
		while (!glfwWindowShouldClose(window)) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			currentScene = sceneManager->getCurrentScene();

			// Update the camera's (view) uniform variables
			view = currentScene->camera->lookAt();
			shader.setMat4("view", view);
			shader.setVector3("cameraPos", currentScene->camera->kinematic.pos);

			std::string iterator;
			// Update light variables
			// ------------------------------------------------------------------------------------------
			for (int i = 0; i < 4; i++) {

				if (!currentScene->lights[i]) continue;
				iterator = "pointLights[" + std::to_string(i) + "]";

				shader.setVector3(iterator + ".pos", currentScene->lights[i]->kinematic.pos);
				shader.setVector3(iterator + ".lightColor", currentScene->lights[i]->lightColor);
				shader.setFloat(iterator + ".intensity", currentScene->lights[i]->intensity);
				shader.setFloat(iterator + ".ambientStrength", 0.5f);
				shader.setFloat(iterator + ".diffuseStrength", 0.5f);
				shader.setFloat(iterator + ".specularStrength", 0.5f);
			}

			// Render every Entity
			// ------------------------------------------------------------------------------------------
			for (RenderComponent* renderComponent : currentScene->renderComponents) {
				// Create model transformation matrix (NOTE: Order of calculations is SCALE, ROTATE, then TRANSLATE)
				model = glm::translate(glm::mat4(1.0f), renderComponent->modelPos);
				model = glm::rotate(model, renderComponent->rotationAngle, renderComponent->rotationAxis);
				model = glm::scale(model, renderComponent->scale);
				
				// Update model transformation matrix
				shader.setMat4("model", model);
				
				// Render
				renderComponent->vao.bindObject();
				glActiveTexture(GL_TEXTURE0);
				renderComponent->diffuseMap.bindObject();
				glActiveTexture(GL_TEXTURE1);
				renderComponent->specularMap.bindObject();
				glDrawArrays(GL_TRIANGLES, 0, renderComponent->vbo.getNumVertices());
			}
			glfwSwapBuffers(window);
			glfwPollEvents();

			// Update every Entity
			for (Entity* entity : currentScene->entities) {
				entity->update(window);
			}
			frameCount++;
		}
		return 0;
	}

private:

	static FTGFWProgram* instance;

	FTGFWProgram() {}

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