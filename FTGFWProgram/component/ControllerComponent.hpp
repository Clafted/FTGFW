#pragma once
#ifndef CONTOLLERCOMPONENT_H
#define CONTOLLERCOMPONENT_H

#include <vector>
#include "Component.hpp"
#include "InputManager.hpp"

/**
 * A Component subclass to allow for user-input-controlled events.
 * The template type is to be the type of the object which will be controlled.
 *
 * To use this class, the user must define a method of the template type T,
 * and upon instantiation of the ControllerComponent class provide a pointer
 * to the instance which will be used to call the method of inputs.
 * 
 * @author Noah  */
template <typename T>
class ControllerComponent : public Component {
public:
	bool enabled = true;
	T* target;
	double prevMouseX = 0.0f;
	double prevMouseY = 0.0f;
	double mousePosX = 0.0f;
	double mousePosY = 0.0f;

	using inputHandleFunction = void (T::*)(GLFWwindow* window, double mouseMoveX, double mouseMoveY);
	inputHandleFunction inputHandler = nullptr;

	/**
	 * Constructor for ControllerComponent
	 * 
	 * @param target - the object on which the inputHandler() method will be called
	 * @param inputHandler - the class method of type T to be called when checking for inputs
	 */
	ControllerComponent(T* target, inputHandleFunction inputHandler) {
		this->target = target;
		this->inputHandler = inputHandler;
	}

	void update(GLFWwindow* window) {
		prevMouseX = mousePosX;
		prevMouseY = mousePosY;
		glfwGetCursorPos(window, &mousePosX, &mousePosY);
		// Call the method of the target
		(target->inputHandler)(window, -(mousePosX - prevMouseX), -(mousePosY - prevMouseY));
	}
};

#endif