#pragma once 
#ifndef COMPONENT_H
#define COMPONENT_H

#include "../openGLObjects/GLIncludes.hpp"

class Component {
public:
	virtual void update(GLFWwindow * window) = 0;
};

#endif