#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

#include "Entity.h"
#include "Camera.h"

class Scene {
public:
	std::vector<Entity*> entities;
	Camera camera;

	Scene(){}

	~Scene() {
		entities.clear();
	}

	inline Scene* update() {
		return this;
	}
};

#endif