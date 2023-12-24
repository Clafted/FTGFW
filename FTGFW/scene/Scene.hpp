#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

#include "../component/RenderComponent.hpp"
#include "./Light.hpp"
#include "DroneCamera.hpp"

class Scene {
public:
	std::vector<RenderComponent*> renderComponents;
	std::vector<Entity*> entities;
	std::vector<Light*> lights;
	DroneCamera camera;

	Scene(){}

	~Scene() {
		renderComponents.clear();
		entities.clear();
		lights.clear();
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