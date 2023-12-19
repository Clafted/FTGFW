#pragma once
#ifndef CONTOLLER_H
#define CONTOLLER_H

#include <vector>
#include "Component.hpp"

class Controller : public Component{
public:
	bool enabled = true;

	void update(GLFWwindow* window) {
		checkInputs(window);
	}

	virtual void checkInputs(GLFWwindow* window) = 0;
};

#endif