#ifndef DRONECAMERA_H
#define DRONECAMERA_H

#include "./Camera.hpp"
#include "../scene/SceneManager.hpp"

class DefaultScene;
class LandGenerationScene;
class DroneCamera : public Camera {
public:
	float sensitivity = 0.5f;
	float accelerationMagnitude = 10.0f;

	ControllerComponent<DroneCamera> controller = ControllerComponent<DroneCamera>(this, &DroneCamera::inputHandler);

	DroneCamera(float screenWidth, float screenHeigth, float fov = 45.0f, float near = 0.1f, float far = 100.0f) 
		: Camera(screenWidth, screenHeigth, fov, near, far) 
	{
		components = { &controller };
	}

	void inputHandler(GLFWwindow* window, double mouseMoveX, double mouseMoveY) {
		// Mouse inputs
		// ---------------------------------------------------
		kinematic.rotation.y += (float) (mouseMoveX * sensitivity * 3.1415f / 180.0f);
		if (abs(kinematic.rotation.x) > 0.9f * glm::pi<float>() / 2.0f) {
			kinematic.rotation.x = (float) (0.9f * glm::pi<float>() / 2.0f * glm::sign(kinematic.rotation.x));
		}
		else {
			kinematic.rotation.x += (float) (mouseMoveY * sensitivity * 3.1415f / 180.0f);
		}
		// Keyboard inputs
		// ---------------------------------------------------
		glm::vec3 input = glm::vec3(0.0f);
		glm::vec3 inputDirection = glm::vec3(0.0f);
		glm::vec3 finalAcceleration;
		// Check inputs
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) input.z = -1.0f;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) input.z = 1.0f;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) input.x = -1.0f;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) input.x = 1.0f;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) input.y = 1.0f;
		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) input.y = -1.0f; 
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
		//if (glfwGetScrol)
		// Calculate final acceleration
		if (input == glm::vec3(0.0f)) {
			kinematic.acceleration = glm::vec3(0.0f);
		}
		else {
			// Convert input into a normalized vector
			input = glm::normalize(input);
			inputDirection.y = asin(-input.x);
			if (input.z > 0.0f) inputDirection.y = 3.1415f - inputDirection.y;
			// Calculate acceleration direction with added input direction
			finalAcceleration.x = cos(kinematic.rotation.x) * -sin(kinematic.rotation.y + inputDirection.y);
			finalAcceleration.y = sin(kinematic.rotation.x * -glm::sign(input.z)) + input.y;
			finalAcceleration.z = cos(kinematic.rotation.x) * -cos(kinematic.rotation.y + inputDirection.y);
			// Apply acceleration
			kinematic.acceleration = glm::normalize(finalAcceleration) * accelerationMagnitude;
		}
	}
};

#endif