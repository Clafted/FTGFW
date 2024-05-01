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

	inline SceneManager(ComponentManager& componentManager, GLFWwindow * window) : componentManager(componentManager), window(window) {};
	inline ~SceneManager() { currentScene->exitScene(); }
	inline std::shared_ptr<Scene> getCurrentScene() { return currentScene; }
	inline std::string getCurrentSceneName() const { return currentSceneName; }
	inline void addScene(std::string name, std::shared_ptr<Scene> scene) { scenes.insert({ name, scene }); }

	void setScene(std::string name);

private:

	std::map<std::string, std::shared_ptr<Scene>> scenes;
	std::shared_ptr<Scene> currentScene = nullptr;
	std::string currentSceneName = "";
	ComponentManager& componentManager;
	GLFWwindow * window;
};

#endif