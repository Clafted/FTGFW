#pragma once
#ifndef OPENGLOBJECT_H
#define OPENGLOBJECT_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class OpenGLObject
{
public:
	unsigned int ID;

	virtual void bindObject() = 0;
	virtual void unbindObject() = 0;
};

#endif