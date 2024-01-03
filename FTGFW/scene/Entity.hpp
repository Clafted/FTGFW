#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "../component/Component.hpp"
#include "../openGLObjects/GLIncludes.hpp"
#include <vector>

class Entity {
public:
	std::vector<Component*> components;

	/* Updates components and other necessary parts of the Entity
	 *
	 * @param window - a GLFWwindow* to use pull any window-related data from*/
	virtual void update(GLFWwindow* window) {
		for (Component* component : components) {
			component->update(window);
		}
	}
};

#endif