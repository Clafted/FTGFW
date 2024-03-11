#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include "System.hpp"
#include "../component/CameraComponent.hpp"

class CameraSystem : public System {
public:

	CameraSystem(ComponentManager& componentManager, SceneManager& sceneManager) : System(componentManager, sceneManager) {};
	void update(GLFWwindow* window, float deltaTime);
};

#endif