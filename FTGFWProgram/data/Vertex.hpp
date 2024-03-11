#ifndef VERTEX_H
#define VERTEX_HPP

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

struct Vertex {
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

#endif