#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include "../../third_party/GLIncludes.hpp"
#include "../component/ControllerComponent.hpp"
#include "System.hpp"

class ControllerSystem : public System {
public:

	void update(GLFWwindow* window, float deltaTime);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

private:
	static std::unordered_map<int, int> mouseButtons;
};

#endif