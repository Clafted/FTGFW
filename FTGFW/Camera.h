#pragma once
#ifndef CLASS_H
#define CLASS_H

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"

class Camera {
public:
	glm::vec3 pos = glm::vec3(0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);

	Camera() {};
	~Camera() {};

	glm::mat4 lookAt() {
		return glm::lookAt(pos, pos + direction, glm::vec3(0.0f, 1.0f, 0.0f));
	}

private:
	
};

#endif
