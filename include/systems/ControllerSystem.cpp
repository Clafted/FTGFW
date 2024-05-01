#include "ControllerSystem.hpp"

std::unordered_map<int, int> ControllerSystem::mouseButtons = {};

void ControllerSystem::update(GLFWwindow* window, float deltaTime) 
{
	std::shared_ptr<componentMap> map = componentManager->getComponentMap<ControllerComponent>();
	std::string currentScene = sceneManager->getCurrentSceneName();
	for (auto i = map->begin(); i != map->end(); i++)
	{
		std::dynamic_pointer_cast<ControllerComponent>(i->second)->handleInput(*componentManager, *sceneManager, window, mouseButtons);
		if (currentScene != sceneManager->getCurrentSceneName()) break;
	}
}

void ControllerSystem::mouseButtonCallback(GLFWwindow * window, int button, int action, int mods) {
	mouseButtons.insert({ button, action });
}
