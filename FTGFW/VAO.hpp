#pragma once
#ifndef VAO_H
#define VAO_H

#include "OpenGLObject.hpp"

class VAO : public OpenGLObject
{
public:
	VAO() { glGenVertexArrays(1, &ID); }
	~VAO() {}

	inline void bindObject() { glBindVertexArray(ID); }
	inline void unbindObject() { glBindVertexArray(0); }
};

#endif

