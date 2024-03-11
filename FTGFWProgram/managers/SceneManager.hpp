#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "../scene/Scene.hpp"
#include <memory>
#include <string>
#include <map>

/* A Singleton class to manager the queueing and transitions of Scene Objects. */
class SceneManager {
public:

	inline SceneManager(ComponentManager& componentManager) : componentManager(componentManager) {};
	inline ~SceneManager() { currentScene->exitScene(componentManager); }
	inline std::shared_ptr<Scene> getCurrentScene() { return currentScene; }
	inline void addScene(std::string name, std::shared_ptr<Scene> scene) { scenes.insert({ name, scene }); }

	void setScene(std::string name);

private:

	std::map<std::string, std::shared_ptr<Scene>> scenes;
	std::shared_ptr<Scene> currentScene = nullptr;
	ComponentManager& componentManager;
};

#endif