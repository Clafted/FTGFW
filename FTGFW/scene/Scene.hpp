#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <array>
#include <string>

#include "../component/RenderComponent.hpp"
#include "Light.hpp"
#include "DroneCamera.hpp"

class Scene {
public:
	std::vector<RenderComponent*> renderComponents;
	std::vector<Entity*> entities;
	std::array<Light*, 4> lights = {};
	float screenWidth, screenHeight;
	Camera* camera = nullptr;

	Scene(float screenWidth, float screenHeight)
		: screenWidth(screenWidth), screenHeight(screenHeight) {}

	~Scene() {
		renderComponents.clear();
		entities.clear();
		for (Light* light : lights) delete light;
		delete camera;
	}

	void setScreenDimensions(float screenWidth, float screenHeight) {
		camera->setScreenDimensions(screenWidth, screenHeight);
	}

	/**
	 * Makes any changes to the Scene.
	 * 
	 * By default, nullptr is returned, and nothing else is changed.
	 */
	virtual inline Scene* update() {
		return nullptr;
	}
};

#endif