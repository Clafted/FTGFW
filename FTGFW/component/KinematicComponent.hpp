#pragma once
#ifndef KINEMATICCOMPONENT_H
#define KINEMATICCOMPONENT_H

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"

#include "Component.hpp"

class KinematicComponent : public Component{
public:
	KinematicComponent() {};
	~KinematicComponent() {};

	glm::vec3 pos = glm::vec3(0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 rotation = glm::vec3(0.0f);

	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f);

	void update(GLFWwindow * window) {
		deltaTime = (float)glfwGetTime() - previousTime;
		if (deltaTime >= 0.15f) {
			deltaTime = 0.15f;
		}
		previousTime = (float)glfwGetTime();

		velocity += acceleration * deltaTime;
		pos += velocity * deltaTime;

		if (acceleration.x == 0) {
			velocity.x *= 0.9f;
			if (abs(velocity.x) <= 0.05f) {
				velocity.x = 0.0f;
			}
		}

		if (acceleration.y == 0) {
			velocity.y *= 0.9f;
			if (abs(velocity.y) <= 0.05f) {
				velocity.y = 0.0f;
			}
		}

		if (acceleration.z == 0) {
			velocity.z *= 0.9f;
			if (abs(velocity.z) <= 0.05f) {
				velocity.z = 0.0f;
			}
		}

		direction.y = sin(rotation.x * glm::pi<float>() / 180.0f);
		direction.x = sin(rotation.y * glm::pi<float>() / 180.0f);
		direction.z = -cos(rotation.x * glm::pi<float>() / 180.0f);
	};

private:
	float deltaTime = 0.0f;
	float previousTime = 0.0f;
};

#endif