#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.hpp"

class SceneManager {
public:

	inline ~SceneManager() {
		delete instance;
		delete currentScene;
		delete temp;
	}

	inline static SceneManager* Instance() {
		if (!instance) {
			instance = new SceneManager();
		}
		return instance;
	}

	inline void setStartScene(Scene* scene) {
		instance->currentScene = scene;
	}
	
	inline Scene* getCurrentScene() {
		return currentScene;
	}

	inline void update() {
		temp = currentScene->update();
		if (temp) {
			delete currentScene;
			currentScene = temp;
		}
	}

private:
	static SceneManager* instance;
	Scene* currentScene = nullptr, *temp = nullptr;

	SceneManager() {}
};

#endif