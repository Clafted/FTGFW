#pragma once
#ifndef OPENGLOBJECT_H
#define OPENGLOBJECT_H

#include <iostream>
#include "../third_party/GLIncludes.hpp"

/* 
 * The OpenGLObject interface creates an inheritance
 * hierarchy between actual OpenGL Objects.
 * 
 * @author Noah Perez
 */
class OpenGLObject {
public:
	// The ID storing the OpenGL object's address
	unsigned int ID = NULL;

	// Binds an OpenGL object to its appropriate buffer
	virtual void bindObject() = 0;
	// Unbinds an OpenGL object from its appropriate buffer
	virtual void unbindObject() = 0;
};

#endif