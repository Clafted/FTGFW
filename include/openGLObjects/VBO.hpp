#pragma once
#ifndef VBO_H
#define VBO_H

#include "OpenGLObject.hpp"
#include "../data/Vertex.hpp"
#include <vector>

/** 
 * The VBO class simpilifies the use of OpenGL Vertex Array Objects.
 * Vertices are in the order (x, y, z, u, v, nX, nY, nZ).
 * 
 * @author Noah Perez
 */
class VBO : public OpenGLObject
{
public:
	VBO() {}
	VBO(const void* vertices, GLsizeiptr size, GLenum usage) {
		glGenBuffers(1, &ID);
		bindObject();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		setVertices(vertices, size, usage);
	}
	
	~VBO() {}

	inline void bindObject() { 
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	inline void unbindObject() {}

	inline int const getNumVertices() {
		return numVertices;
	}
	/**
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
		numVertices = (int)size / (sizeof(float) * 8);
	}

private:
	int numVertices = 0;
};

#endif

