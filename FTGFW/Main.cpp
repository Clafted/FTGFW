#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Texture.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "Entity.h"
#include "Camera.h"

int glfwSetup(GLFWwindow ** window);
int gladSetup();
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

unsigned int screenWidth = 800, screenHeight = 600;
unsigned int frameCount = 0;

int main() {

	GLFWwindow* window = nullptr;
	if (glfwSetup(&window) == -1) return 0;
	if (gladSetup() == -1) return 0;

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	
	// Use Shaders
	Shader shader("vertex.vert", "fragment.frag");
	
	Entity entity(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
	entity.vao.bindObject();
	entity.addTexture("./Textures/Brick_Texture.png");

	glEnable(GL_DEPTH_TEST);
	glUseProgram(shader.ID);

	glm::mat4 model, view(1.0f), projection;
	projection = glm::perspective(glm::pi<float>() / 4.0f, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	Camera cam;

	// Render Loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam.pos.x = 0.3 * glm::sin(glfwGetTime());

		// Create model matrix (SCALE is FIRST, THEN ROTATION AND TRANSLATION FOLLOW)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.4f * glm::sin((float)glfwGetTime() / glm::pi<float>()), -3.0f));
		model = glm::rotate(model, (float)glfwGetTime() / glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));

		// Update viewspaces transformation matrices
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(cam.lookAt()));
		// Draw vertices
		glDrawArrays(GL_TRIANGLES, 0, entity.vbo.getNumVertices());

		glfwSwapBuffers(window);
		glfwPollEvents();
		frameCount++;
	}
	std::cout << "Average frame rate: " << frameCount / glfwGetTime() << " FPS";
	// Free resouces and terminate program
	glfwTerminate();
	return 0;
}

int glfwSetup(GLFWwindow ** window) {
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
	*window = glfwCreateWindow(screenWidth, screenHeight, "FTGFW", NULL, NULL);
	if (*window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(*window);
	// Set callbacks
	// -----------------------------------------------------
	glfwSetFramebufferSizeCallback(*window, frameBufferSizeCallback);
}

int gladSetup() {
	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, width, height);
}