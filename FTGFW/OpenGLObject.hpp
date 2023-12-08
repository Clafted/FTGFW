#pragma once
#ifndef OPENGLOBJECT_H
#define OPENGLOBJECT_H

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class OpenGLObject
{
public:
	unsigned int ID = NULL;

	virtual void bindObject() = 0;
	virtual void unbindObject() = 0;
};

#endif