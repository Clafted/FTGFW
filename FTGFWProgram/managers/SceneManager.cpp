#include "SceneManager.hpp"

void SceneManager::setScene(std::string name) 
{
	// Switch only if the new scene is different
	if (scenes.find(name) != scenes.end() 
		&& currentScene != scenes.find(name)->second) 
	{
		if (currentScene) currentScene->exitScene(componentManager);
		std::cout << "\nFound scene. Switching to scene: " << name << std::endl;
		currentScene = scenes.find(name)->second;
		currentScene->setupScene(componentManager);
	} else {
		std::cout << "\nNo scene found";
	}
}