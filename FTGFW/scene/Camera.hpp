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
		// Keyboard inputs
		// ---------------------------------------------------
		kin.acceleration = glm::vec3(0.0f);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			kin.acceleration.z = -5.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			kin.acceleration.z = 5.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			kin.acceleration.x = -5.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			kin.acceleration.x = 5.0f;
		}
		// Mouse inputs
		// ---------------------------------------------------
		std::cout << "\n\nX: " << mouseMoveX << "\nY: " << mouseMoveY;
		if (abs(kin.rotation.x) >= 180.0f) {
			kin.rotation.x = 180 * (kin.rotation.x / abs(kin.rotation.x));
		}
		kin.rotation.x -= mouseMoveY;
		kin.rotation.y -= mouseMoveX;
	}

private:
	
};

#endif
