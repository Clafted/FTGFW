#pragma once
#ifndef KINEMATICCOMPONENT_H
#define KINEMATICCOMPONENT_H

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"

#include "Component.hpp"

class KinematicComponent : public Component{
public:
	glm::vec3 pos = glm::vec3(0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f);

	void update(GLFWwindow * window) {
		deltaTime = (float)glfwGetTime() - previousTime;
		// Limit deltaTime
		if (deltaTime >= 0.15f) deltaTime = 0.15f;
		previousTime = (float)glfwGetTime();

		// Component-wise friction simulation
		if (acceleration.x == 0) {
			velocity.x *= 0.9f;
			if (abs(velocity.x) <= 0.05f) velocity.x = 0.0f;
		}
		if (acceleration.y == 0) {
			velocity.y *= 0.9f;
			if (abs(velocity.y) <= 0.05f) velocity.y = 0.0f;
		}
		if (acceleration.z == 0) {
			velocity.z *= 0.9f;
			if (abs(velocity.z) <= 0.05f) velocity.z = 0.0f;
		}
		// Change facing-direction depending on rotation angle
		direction.y = sin(rotation.x);
		direction.x = -sin(rotation.y) * cos(rotation.x);
		direction.z = -cos(rotation.y) * cos(rotation.x);
		direction = glm::normalize(direction);
		velocity += acceleration * deltaTime;
		pos += velocity * deltaTime;
	};

private:
	float deltaTime = 0.0f;
	float previousTime = 0.0f;

	float speed(glm::vec3 & velocity) {
		return sqrt(pow(velocity.x, 2) + pow(velocity.y, 2) + pow(velocity.z, 2));
	}

	float accelerationMagnitude(glm::vec3 & acceleration) {
		return sqrt(pow(acceleration.x, 2) + pow(acceleration.y, 2) + pow(acceleration.z, 2));
	}
};

#endif