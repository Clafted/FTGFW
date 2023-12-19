#pragma once
#ifndef KINEMATICCOMPONENT_H
#define KINEMATICCOMPONENT_H

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"

#include "Component.hpp"

class KinematicComponent {
public:
	glm::vec3 pos = glm::vec3(0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);

	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f);

	void update(float deltaTime) {
		velocity += acceleration * deltaTime;
		pos += velocity * deltaTime;

		if (acceleration.x == 0) {
			velocity.x *= 0.5f;
			if (velocity.x <= 0.05f) {
				velocity.x = 0.0f;
			}
		}

		if (acceleration.y == 0) {
			velocity.y *= 0.5f;
			if (velocity.y <= 0.05f) {
				velocity.y = 0.0f;
			}
		}

		if (acceleration.z == 0) {
			velocity.z *= 0.5f;
			if (velocity.z <= 0.05f) {
				velocity.z = 0.0f;
			}
		}
	};
};

#endif