#pragma once
#ifndef CONTOLLERCOMPONENT_H
#define CONTOLLERCOMPONENT_H

#include <vector>
#include <unordered_map>
#include "Component.hpp"
#include "../managers/ComponentManager.hpp"
#include "../managers/SceneManager.hpp"
#include "../../third_party/GLIncludes.hpp"
#include "../scene/Entity.hpp"

/**
 * A Component subclass to allow for user-input-controlled events.
 * The template type is to be the type of the object which will be controlled.
 *
 * To use this class, the user must define a method of the template type T,
 * and upon instantiation of the ControllerComponent class provide a pointer
 * to the instance which will be used to call the method of inputs.
 * 
 * @author Noah  */
struct ControllerComponent : public Component {
public:

	std::shared_ptr<Entity> entity;
	bool enabled = true;

	ControllerComponent(std::shared_ptr<Entity> entity) : entity(entity) {};
	virtual void handleInput(ComponentManager& componentManager, SceneManager& sceneManager, GLFWwindow * window, std::unordered_map<int, int>& mouseButtons) = 0;
};

#endif