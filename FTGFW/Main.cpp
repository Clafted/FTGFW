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

int glfwSetup(GLFWwindow ** window);
int gladSetup();
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

int main() {

	GLFWwindow* window = nullptr;
	if (glfwSetup(&window) == -1) return 0;
	if (gladSetup() == -1) return 0;

	float vertices[] = {
		//	  Position			TexCoords
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f
	};
	
	// Use Shaders
	Shader shader("vertex.vert", "fragment.frag");
	
	VAO triangleVAO;
	triangleVAO.bindObject();
	VBO triangleVBO(vertices, sizeof(vertices), GL_STATIC_DRAW);
	Texture texture("./Textures/Brick_Texture.png");

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(2.0f, 0.5f, 1.0f));

	glUseProgram(shader.ID);
	// Render Loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Create transformation matrix (SCALE is FIRST, THEN ROTATION AND TRANSLATION FOLLOW)
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.0f, (float) 0.2f * glm::sin(glfwGetTime() * 3.14f), 0.0f));
		transform = glm::rotate(transform, (float) glfwGetTime() * 0.628f, glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 1.0f));
		// Update transoformation matrix
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_transformMat4"), 1, GL_FALSE, glm::value_ptr(transform));
		// Draw vertices
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Free resouces and terminate program
	glfwTerminate();
	return 0;
}

int glfwSetup(GLFWwindow ** window) {
	// Initial GLFW configuration
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFW window
	*window = glfwCreateWindow(800, 600, "FTGFW", NULL, NULL);
	if (*window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(*window);

	// Set callbacks
	glfwSetFramebufferSizeCallback(*window, frameBufferSizeCallback);
}

int gladSetup() {
	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}