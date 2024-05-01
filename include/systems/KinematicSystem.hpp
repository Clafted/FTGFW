#ifndef KINEMATICSYSTEM_H
#define KINEMATICSYSTEM_H

#include "System.hpp"
#include "../component/KinematicComponent.hpp"

class KinematicSystem : public System {
public:

	void update(GLFWwindow* window, float deltaTime);
};

#endif