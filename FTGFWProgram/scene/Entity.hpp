#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "../component/Component.hpp"
#include "../../third_party/GLIncludes.hpp"
#include <vector>

class Entity {
public:
	std::vector<Component*> components;

	Entity() {};
	~Entity() {
		components.clear();
	};

	/* Updates components and other necessary parts of the Entity
	 * 
	 * NOTE: Call Entity::update() when overriding to cover other necessary updates
	 * @param window - a GLFWwindow* to use pull any window-related data from*/
	virtual void update(GLFWwindow* window) {
		deltaTime = glfwGetTime() - previousTime / 1000.0;
		if (deltaTime > 0.15) deltaTime = 0.15;
		previousTime = glfwGetTime();

		for (Component* component : components) {
			component->update(window);
		}
	}

protected:
	double deltaTime = 0.0f, previousTime = 0.0f;
};

#endif