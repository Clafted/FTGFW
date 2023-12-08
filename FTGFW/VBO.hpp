#pragma once
#ifndef VBO_H
#define VBO_H

#include "OpenGLObject.hpp"

class VBO : public OpenGLObject
{
public:
	VBO(const void* vertices, GLsizeiptr size, GLenum usage)
	{
		glGenBuffers(1, &ID);
		bindObject();
		setVertices(vertices, size, usage);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

	~VBO() {}

	inline void bindObject() { 
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	inline void unbindObject() { }

	inline void setVertices(const void* vertices, GLsizeiptr size, GLenum usage)
	{
		bindObject();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
	}
};

#endif

