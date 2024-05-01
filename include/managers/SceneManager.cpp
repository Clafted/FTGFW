#include "SceneManager.hpp"

void SceneManager::setScene(std::string name) 
{
	if (scenes.find(name) == scenes.end() || currentScene == scenes.find(name)->second) return;
	if (currentScene) currentScene->exitScene();
	std::cout << "\n" << name << std::endl;
	currentScene = scenes.find(name)->second;
	currentSceneName = name;
	currentScene->setupScene();
}