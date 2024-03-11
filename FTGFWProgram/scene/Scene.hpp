#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <array>
#include <string>
#include <memory>
#include <iostream>

#include "Entity.hpp"
#include "../managers/ComponentManager.hpp"

class Scene {
public:
	static int screenWidth, screenHeight;

	Scene() {};
	~Scene() { std::cout << "\nDeleting Scene"; }

	void setScreenDimensions(int screenWidth, int screenHeight) {
		Scene::screenWidth = screenWidth;
		Scene::screenHeight = screenHeight;
	}

	virtual void setupScene(ComponentManager& componentManager) = 0;
	virtual void exitScene(ComponentManager& componentManager) = 0;
};

#endif