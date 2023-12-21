#pragma once
#ifndef CLASS_H
#define CLASS_H

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"
#include "../component/ControllerComponent.hpp"
#include "Entity.hpp"
#include "../component/KinematicComponent.hpp"
#include <iostream>

class Camera : public Entity{
public:
	KinematicComponent kin;
	ControllerComponent<Camera> con = ControllerComponent<Camera>(this);
	float sensitivity = 0.5f;
	float accelerationMagnitude = 5.0f;

	Camera() {
		con.inputHandler = &Camera::checkInputs;
		components.push_back(&kin);
		components.push_back(&con);
	};
	~Camera() {};

	glm::mat4 lookAt() {
		return glm::lookAt(kin.pos, kin.pos + kin.direction, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void checkInputs(GLFWwindow* window, double mouseMoveX, double mouseMoveY) {
		// Mouse inputs
		// ---------------------------------------------------
		if (abs(kin.rotation.x) >= 85.0f) {
			kin.rotation.x = 85.0f * (kin.rotation.x / abs(kin.rotation.x));
		}
		kin.rotation.x -= mouseMoveY * sensitivity * 3.1415f / 180.0f;
		kin.rotation.y += mouseMoveX * sensitivity * 3.1415f / 180.0f;
		// Keyboard inputs
		// ---------------------------------------------------
		glm::vec3 input = glm::vec3(0.0f);
		glm::vec3 inputRotation = glm::vec3(0.0f);
		glm::vec3 finalAcceleration;
		// Check inputs
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) input.z = -1.0f;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) input.z = 1.0f;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) input.x = -1.0f;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) input.x = 1.0f;
		// Calculate final acceleration
		if (input == glm::vec3(0.0f)) {
			kin.acceleration = glm::vec3(0.0f);
		} else {
			input = glm::normalize(input);
			inputRotation.y = asin(in;
			finalAcceleration.x = cos(kin.rotation.x) * -sin(kin.rotation.y);
			finalAcceleration.y = sin(kin.rotation.x);
			finalAcceleration.z = cos(kin.rotation.x) * -cos(kin.rotation.y);
			kin.acceleration = glm::normalize(finalAcceleration) * input *  accelerationMagnitude;
		}
	}

private:
	
};

#endif
