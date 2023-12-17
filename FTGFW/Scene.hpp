#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

#include "Entity.hpp"
#include "Camera.hpp"

class Scene {
public:
	std::vector<Entity*> entities;
	Camera camera;

	Scene(){}

	~Scene() {
		entities.clear();
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