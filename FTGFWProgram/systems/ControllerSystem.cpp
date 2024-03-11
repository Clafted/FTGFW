#include "ControllerSystem.hpp"

std::unordered_map<int, int> ControllerSystem::mouseButtons = {};

void ControllerSystem::update(GLFWwindow* window, float deltaTime) {
	for (auto i = componentManager.getComponentMap<ControllerComponent>()->begin(); i != componentManager.getComponentMap<ControllerComponent>()->end(); i++) {
		std::dynamic_pointer_cast<ControllerComponent>(i->second)->handleInput(componentManager, window, mouseButtons);
	}
}

void ControllerSystem::mouseButtonCallback(GLFWwindow * window, int button, int action, int mods) {
	mouseButtons.insert({ button, action });
}
