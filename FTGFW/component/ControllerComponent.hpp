#pragma once
#ifndef CONTOLLERCOMPONENT_H
#define CONTOLLERCOMPONENT_H

#include <vector>
#include "Component.hpp"

template <typename T>
class ControllerComponent 
	: public Component{
public:
	bool enabled = true;
	T* target;
	double prevMouseX = 0.0f;
	double prevMouseY = 0.0f;
	double mousePosX = 0.0f;
	double mousePosY = 0.0f;
	void (T::*inputHandler)(GLFWwindow* window, double mouseMoveX, double mouseMoveY) = nullptr;

	ControllerComponent(T* target) {
		this->target = target;
	}

	void update(GLFWwindow* window) {
		prevMouseX = mousePosX;
		prevMouseY = mousePosY;
		glfwGetCursorPos(window, &mousePosX, &mousePosY);
		checkInputs(window);
	}

	virtual void checkInputs(GLFWwindow* window) {
		(target->*inputHandler)(window, mousePosX - prevMouseX, mousePosY - prevMouseY);
	};
};

#endif