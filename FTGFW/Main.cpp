#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
	// Initial GLFW configuration
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Create a GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 600, "FTGFW", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, 800, 600);

	// Initialize GLAD
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == NULL)
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	glfwTerminate();
	return 0;
}