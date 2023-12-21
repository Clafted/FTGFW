#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "../component/Component.hpp"
#include "GLFW/glfw3.h"
#include <vector>

class Entity {
public:
	std::vector<Component*> components;

	void update(GLFWwindow* window) {
		for (Component* component : components) {
			component->update(window);
		}
	}
};

#endif