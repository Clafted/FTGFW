#pragma once
#ifndef CLASS_H
#define CLASS_H

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"
#include "Entity.hpp"
#include "../component/ControllerComponent.hpp"
#include "../component/KinematicComponent.hpp"

#include <iostream>

/**
 * A class representing a camera to allow for viewing of the world
 * 
 * @authoer Noah Perez
 */
class Camera : public Entity{
public:
	KinematicComponent kinematic;
	glm::mat4 projectionMatrix;
	float fov;
	float near, far;

	Camera(float screenWidth, float screenHeight, float fov = 45.0f, float near = 0.1f, float far = 100.0f)
		: projectionMatrix(glm::perspective(fov, screenWidth / screenHeight, near, far)) {

		this->fov = fov;
		this->near = near;
		this->far = far;

		components.push_back(&kinematic);
	};
	~Camera() {};

	/**
	 * Get the view transformation matrix based on the camera's position and direction.
	 * @returns the view transformation matrix
	 */
	glm::mat4 lookAt() {
		return glm::lookAt(kinematic.pos, kinematic.pos + kinematic.direction, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void setScreenDimensions(float screenWidth, float screenHeight) {
		projectionMatrix = glm::perspective(fov, screenWidth / screenHeight, near, far);
	}

private:
	
};

#endif
