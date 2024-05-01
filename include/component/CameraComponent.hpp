#pragma once
#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"
#include "KinematicComponent.hpp"
#include "Component.hpp"

#include <iostream>

/**
 * A class representing a camera to allow for viewing of the world
 * 
 * @authoer Noah Perez
 */
struct CameraComponent : public Component {
public:
	glm::mat4 projectionMatrix;
	float fov;
	float near, far;
	glm::vec3 direction;
	glm::vec3 rotation;
	glm::vec3 pos;
	glm::vec3 forward, right, up;

	CameraComponent(int screenWidth, int screenHeight, float fov = 45.0f, float near = 0.1f, float far = 100.0f)
		: projectionMatrix(glm::perspective(fov, screenWidth / (float)screenHeight, near, far)),
		fov(fov),
		near(near),
		far(far) 
	{
		rotation = glm::vec3(0.0f);
		pos = glm::vec3(0.0f);
		direction = glm::vec3(0.0f, 0.0f, -1.0f);
		forward = direction;
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		right = glm::cross(forward, up);
	};
	~CameraComponent() {};

	/**
	 * Get the view transformation matrix based on the camera's position and direction.
	 * @returns the view transformation matrix
	 */
	glm::mat4 lookAt() const {
		return glm::lookAt(pos, pos + direction, glm::cross(direction, glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction))));
	}

	void setScreenDimensions(int screenWidth, int screenHeight) {
		projectionMatrix = glm::perspective(fov, screenWidth / (float) screenHeight, near, far);
	}
};

#endif
