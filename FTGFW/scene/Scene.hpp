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
	Camera* camera;

	Scene(){}

	~Scene() {
		renderComponents.clear();
		entities.clear();
		for (Light* light : lights) delete light;
		delete camera;
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