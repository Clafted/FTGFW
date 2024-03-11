#ifndef SYSTEM_H
#define SYSTEM_H

#include "../../third_party/GLIncludes.hpp"
#include "../managers/ComponentManager.hpp"
#include "../managers/SceneManager.hpp"
#include <string>
#include <unordered_map>
#include <memory>

class System {
public:

	System(ComponentManager& componentManager, SceneManager& sceneManager) 
		: componentManager(componentManager), sceneManager(sceneManager) {};
	virtual void update(GLFWwindow* window, float deltaTime) = 0;

protected:
	ComponentManager& componentManager;
	SceneManager& sceneManager;
};

#endif