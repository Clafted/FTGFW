#pragma once
#ifndef VAO_H
#define VAO_H

#include "OpenGLObject.hpp"

/*
 * The VAO class simplifies the use of Open GL Vertex Array  Objects
 * 
 * @authoer Noah Perez
 */
class VAO : public OpenGLObject
{
public:
	VAO() { 
		glGenVertexArrays(1, &ID);
		bindObject();
	}
	~VAO() {}

	inline void bindObject() override { glBindVertexArray(ID); }
	inline void unbindObject() override { glBindVertexArray(0); }
};

#endif

