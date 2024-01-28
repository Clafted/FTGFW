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
		std::cout << "\nDeleting Scene";
		delete camera;
	}

	void setScreenDimensions(int screenWidth, int screenHeight) {
		camera->setScreenDimensions(screenWidth, screenHeight);
		Scene::screenWidth = screenWidth;
		Scene::screenHeight = screenHeight;
	}

	virtual void setupScene() = 0;
	virtual void exitScene() = 0;

	/**
	 * Makes changes to the scene
	 * 
	 * May be overrided by subclasses of Scene, but you MUST
	 * call Scene::update() for background updates to be done.
	 * Currently, Scene::update() only updates every entity
	 * in the entities vector.
	 * 
	 * @param window - a pointer to the GLFWwindow to pull information from
	 */
	virtual inline void update(GLFWwindow * window) {
		for (Entity* entity : entities) {
			entity->update(window);
		}
	}

	
};

#endif