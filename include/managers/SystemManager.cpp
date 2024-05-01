#include "SystemManager.hpp"
#include <typeinfo>

void SystemManager::update(GLFWwindow* window, float deltaTime) 
{
	for (auto i = systems.begin(); i != systems.end(); i++)
		i->second->update(window, deltaTime);
}