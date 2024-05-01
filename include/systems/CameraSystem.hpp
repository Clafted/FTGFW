#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include "System.hpp"
#include "../component/CameraComponent.hpp"

class CameraSystem : public System {
public:

	void update(GLFWwindow* window, float deltaTime);
};

#endif