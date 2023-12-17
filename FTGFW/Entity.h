#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "OpenGLObject.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "Texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

/*
 * The Entity class represents anything that can be rendered.
 * 
 * As a result, each Entity object has at leasts its own VBO
 * and VAO.
 * 
 * @author Noah Perez
 */
class Entity {
public:
	std::vector<OpenGLObject*> glObjects = {};
	VBO vbo;
	VAO vao;
	Texture texture;

	glm::vec3 pos =  glm::vec3(0.0f, 0.0f, -1.0f);

	/*
	 * A Constructor for the Entity class
	 *
	 * @param vertices - a pointer to the array of vertices
	 * @param size - the size of the array of vertices
	 * @param usage - how the vertices will be rendered
	 */
	Entity(const void* vertices, GLsizeiptr size, GLenum usage) {
		vao.bindObject();
		vbo = VBO(vertices, size, usage);

		glObjects.assign(0, &vao);
		glObjects.assign(1, &vbo);
		glObjects.assign(2, &texture);
	}
	~Entity() {
		glObjects.clear();
	}

	unsigned int vaoID() {
		return glObjects[0]->ID;
	}

	/**
	 * Add a texture to use with the entity.
	 * 
	 * Handles glObject binding so users do not
	 * need to call bindObject() on the Entity's
	 * OpenGLObjects.
	 * 
	 * @param path the path to the texture
	 */
	void addTexture(const char* path) {
		glObjects[0]->bindObject();
		glObjects[1]->bindObject();
		texture.createTexture(path);
	}
};

#endif
