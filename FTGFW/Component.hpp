#pragma once 
#ifndef COMPONENT_H
#define COMPONENT_H

#include "GLFW/glfw3.h"

class Component {
public:
	virtual void update(GLFWwindow * window) = 0;
};

#endif