#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "../../third_party/GLIncludes.hpp"
#include "../component/Component.hpp"
#include <vector>

class Entity {
public:
	const char* name = "";
	const char* tag = "";

	Entity(const char* name, const char* tag) : name(name), tag(tag) {};
	~Entity() {};

	/* Updates components and other necessary parts of the Entity
	 * 
	 * NOTE: Call Entity::update() when overriding to cover other necessary updates
	 * @param window - a GLFWwindow* to use pull any window-related data from*/
	virtual void update(GLFWwindow* window) {
		deltaTime = glfwGetTime() - previousTime / 1000.0;
		if (deltaTime > 0.15) deltaTime = 0.15;
		previousTime = glfwGetTime();
	}

	virtual void handleCollisionWith(Entity& other) {};
	inline const std::vector<Component*>& getComponents() { return components; }

protected:
	double deltaTime = 0.0f, previousTime = 0.0f;
	std::vector <Component*> components = {};
};

#endif