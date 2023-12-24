#ifndef LIGHT_H
#define LIGHT_H

#include "Entity.hpp"
#include "../component/KinematicComponent.hpp"
#include "../component/RenderComponent.hpp"

class Light : public Entity {
public:
	KinematicComponent kinematic;
	RenderComponent render;
	glm::vec3 lightColor;
	float intensity;

	Light(const void * vertices, GLsizeiptr size, GLenum usage, glm::vec3 lightColor = glm::vec3(1.0f), float intensity = 1.0f) 
		: render(vertices, size, usage),
		  lightColor(lightColor),
		  intensity(intensity){
		components.push_back(&kinematic);
		components.push_back(&render);
	}
	~Light() {}

	inline void update(GLFWwindow* window) {
		render.modelPos = kinematic.pos;
	}
};

#endif