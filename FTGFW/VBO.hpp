#pragma once
#ifndef VBO_H
#define VBO_H

#include "OpenGLObject.hpp"

/* 
 * The VBO class simpilifies the use of OpenGL Vertex Array Objects
 * 
 * @author Noah Perez
 */
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

	/*
	 * Chage the vertices stored in the Vertex Buffer Objects.
	 * 
	 * This involves binding the object to GL_ARRAY_BUFFER.
	 * 
	 * @param vertices a pointer to the array of new vertices
	 * @param size the size of the array
	 * @param usage how the vertices will be used
	 */
	inline void setVertices(const void* vertices, GLsizeiptr size, GLenum usage) {
		bindObject();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
	}
};

#endif

