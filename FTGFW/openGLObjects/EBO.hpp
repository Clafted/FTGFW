#ifndef EBO_H
#define EBO_H

#include "OpenGLObject.hpp"

class EBO : public OpenGLObject {
public:
	
	EBO() {};
	EBO(const void* indices, GLsizeiptr size, GLenum usage) {
		glGenBuffers(1, &ID);
		bindObject();
		setIndices(indices, size, usage);
	}

	inline void bindObject() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	inline void unbindObject() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	inline void setIndices(const void* indices, GLsizeiptr size, GLenum usage) {
		bindObject();
		numIndices = (int)size / sizeof(int);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
		
	}

	inline int getNumIndices() {
		return numIndices;
	}

private:
	int numIndices = 0;
};

#endif