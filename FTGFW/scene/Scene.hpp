#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <array>
#include <string>

#include "Entity.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

class Scene {
public:
	std::vector<Entity*> entities;
	std::array<Light*, 4> lights = {};
	static int screenWidth, screenHeight;
	Camera* camera = nullptr;

	Scene() {}

	~Scene() {
		delete camera;
	}

	void setScreenDimensions(int screenWidth, int screenHeight) {
		camera->setScreenDimensions(screenWidth, screenHeight);
		Scene::screenWidth = screenWidth;
		Scene::screenHeight = screenHeight;
	}

	virtual void setupScene() = 0;

	/**
	 * Makes any changes to the Scene. */
	virtual inline void update(GLFWwindow * window) {
		for (Entity* entity : entities) {
			entity->update(window);
		}
	}

	virtual void exitScene() = 0;
};

#endif