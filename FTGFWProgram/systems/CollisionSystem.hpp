#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "../component/KinematicComponent.hpp"
#include "System.hpp"

class CollisionSystem : public System {
public:

	CollisionSystem(ComponentManager& componentManager, SceneManager& sceneManager) : System(componentManager, sceneManager) {};
	void update(GLFWwindow * window, float deltaTime);
};

#endif