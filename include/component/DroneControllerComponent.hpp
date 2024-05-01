#ifndef DRONECAMERA_H
#define DRONECAMERA_H

#include "ControllerComponent.hpp"
#include "KinematicComponent.hpp"
#include "CameraComponent.hpp"
#include "../../third_party/GLIncludes.hpp"

struct DroneControllerComponent : public ControllerComponent {
public:
	float sensitivity = 0.2f;
	float accelerationMagnitude = 10.0f;
	double mouseX = 0.0, mouseY = 0.0, prevMouseX = 0.0, prevMouseY = 0.0;

	DroneControllerComponent(std::shared_ptr<Entity> entity) : ControllerComponent(entity) {}

	void handleInput(ComponentManager& componentManager, SceneManager& sceneManager, GLFWwindow * window, std::unordered_map<int, int>& mouseButtons)
	{
		prevMouseX = mouseX;
		prevMouseY = mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		double mouseMoveX = mouseX - prevMouseX;
		double mouseMoveY = prevMouseY - mouseY;
		auto kinematic = componentManager.getComponent<KinematicComponent>(entity);
		auto camera = componentManager.getComponent<CameraComponent>(entity);
		// Mouse inputs
		// ---------------------------------------------------
		kinematic->rotation.y += (float) (mouseMoveX * sensitivity * 3.1415f / 180.0f);
		if (abs(kinematic->rotation.x) > 0.93f * 3.1415f / 2.0f) 
		{
			kinematic->rotation.x = (float) (0.93f * 3.1415f / 2.0f * glm::sign(kinematic->rotation.x));
		} else {
			kinematic->rotation.x += (float) (mouseMoveY * sensitivity * 3.1415f / 180.0f);
		}
		camera->rotation = kinematic->rotation;
		// Keyboard inputs
		// ---------------------------------------------------
		glm::vec3 input = glm::vec3(0.0f);
		glm::vec3 inputDirection = glm::vec3(0.0f);
		glm::vec3 finalAcceleration;
		// Check inputs
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) input.z = 1.0f;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) input.z = -1.0f;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) input.x = -1.0f;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) input.x = 1.0f;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) input.y = 1.0f;
		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) input.y = -1.0f; 
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
		//if (glfwGetScrol)
		// Calculate final acceleration
		if (input == glm::vec3(0.0f)) 
		{
			kinematic->acceleration = glm::vec3(0.0f);
		} else {
			finalAcceleration = input.x * camera->right + input.y * camera->up + input.z * camera->forward;
			kinematic->acceleration = accelerationMagnitude * (finalAcceleration);
		}
		if (kinematic->speed() < 0.05f) kinematic->velocity = glm::vec3(0.0f);
	}
};

#endif