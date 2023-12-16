#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"

class SceneManager {
public:
	static Scene* startingScene;

	inline ~SceneManager() {
		delete instance;
		delete currentScene;
		delete temp;
		delete startingScene;
	}

	inline static SceneManager* Instance() {
		if (!instance) {
			instance = new SceneManager();
		}
		return instance;
	}

	inline Scene& getCurrentScene() {
		temp = currentScene->update();
		if (temp) {
			delete currentScene;
			currentScene = temp;
		}
		return *currentScene;
	}

private:
	static SceneManager* instance;
	Scene* currentScene = nullptr, *temp = nullptr;

	SceneManager() {
		currentScene = startingScene;
	}
};

#endif