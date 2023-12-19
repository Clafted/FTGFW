#pragma once
#ifndef CLASS_H
#define CLASS_H

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"
#include "Controller.hpp"
#include "KinematicComponent.hpp"

class Camera : public Entity, public KinematicComponent {
public:
	Camera() {};
	~Camera() {};

	glm::mat4 lookAt() {
		return glm::lookAt(pos, pos + direction, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void checkInputs(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			acceleration.z = -1.0f;
		} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			acceleration.z -= 1.0f;
		} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			acceleration.x -= 1.0f;
		} else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			acceleration.x += 1.0f;
		}
	}

private:
	
};

#endif
