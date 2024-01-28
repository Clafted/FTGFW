#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.hpp"
#include <string>
#include <map>

/* A Singleton class to manager the queueing and transitions of Scene Objects. */
class SceneManager {
public:

	inline ~SceneManager() {
		currentScene->exitScene();
		currentScene = nullptr;
		for (std::map<std::string, Scene*>::iterator i = scenes.begin(); i != scenes.end(); i++) {
			delete i->second;
		}
	}

	inline static SceneManager* Instance() {
		if (!instance) instance = new SceneManager();
		return instance;
	}

	static void terminate() { delete instance; }
	
	inline Scene* getCurrentScene() {
		return currentScene;
	}

	inline void addScene(std::string name, Scene* scene) {
		scenes.insert(std::pair<std::string, Scene*>(name, scene));
	}

	inline void setScene(std::string name) {
		// Switch only if the new scene is different
		if (scenes.find(name) != scenes.end() && currentScene != scenes.find(name)->second) {
			if (currentScene) currentScene->exitScene();
			std::cout << "\nFound scene. Switching to scene: " << name << std::endl;
			currentScene = scenes.find(name)->second;
			currentScene->setupScene();
		}
	}

private:
	static SceneManager* instance;
	std::map<std::string, Scene*> scenes;
	Scene *currentScene = nullptr;

	SceneManager() {}
};

#endif