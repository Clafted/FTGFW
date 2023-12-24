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
	KinematicComponent kinematic;
	
	float sensitivity = 0.5f;
	float accelerationMagnitude = 10.0f;

	Camera() {
		components.push_back(&kinematic);
	};
	~Camera() {};

	glm::mat4 lookAt() {
		return glm::lookAt(kinematic.pos, kinematic.pos + kinematic.direction, glm::vec3(0.0f, 1.0f, 0.0f));
	}

private:
	
};

#endif
