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
#include "../managers/EntityManager.hpp"
#include "../../third_party/GLIncludes.hpp"

class Scene {
public:
	static int screenWidth, screenHeight;
	static ComponentManager * componentManager;
	static EntityManager* entityManager;
	static GLFWwindow * window;

	void setScreenDimensions(int screenWidth, int screenHeight) 
	{
		Scene::screenWidth = screenWidth;
		Scene::screenHeight = screenHeight;
	}

	virtual void setupScene() = 0;
	virtual void exitScene() = 0;
};

#endif