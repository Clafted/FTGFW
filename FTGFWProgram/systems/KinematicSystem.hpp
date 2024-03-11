#ifndef KINEMATICSYSTEM_H
#define KINEMATICSYSTEM_H

#include "System.hpp"
#include "../component/KinematicComponent.hpp"

class KinematicSystem : public System {
public:

	KinematicSystem(ComponentManager& componentManager, SceneManager& sceneManager) : System(componentManager, sceneManager) {};
	void update(GLFWwindow* window, float deltaTime);
};

#endif