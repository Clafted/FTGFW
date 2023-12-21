#pragma once
#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "../openGLObjects/OpenGLObject.hpp"
#include "../openGLObjects/Texture.hpp"
#include "../openGLObjects/VAO.hpp"
#include "../openGLObjects/VBO.hpp"
#include "Component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

/*
 * The RenderComponent class represents anything that can be rendered.
 * 
 * As a result, each RenderComponent object has at leasts its own VBO
 * and VAO.
 * 
 * @author Noah Perez
 */
class RenderComponent : public Component{
public:
	std::vector<OpenGLObject*> glObjects = {};
	VBO vbo;
	VAO vao;
	Texture texture;

	glm::vec3 modelPos = glm::vec3(0.0f);
	glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	float rotationAngle = 0.0f;

	/*
	 * A Constructor for the RenderComponent class
	 *
	 * @param vertices - a pointer to the array of vertices
	 * @param size - the size of the array of vertices
	 * @param usage - how the vertices will be rendered
	 */
	RenderComponent(const void* vertices, GLsizeiptr size, GLenum usage) {
		vao.bindObject();
		vbo = VBO(vertices, size, usage);

		glObjects.assign(0, &vao);
		glObjects.assign(1, &vbo);
		glObjects.assign(2, &texture);
	}
	~RenderComponent() {
		glObjects.clear();
	}

	unsigned int vaoID() {
		return glObjects[0]->ID;
	}

	/**
	 * Add a texture to use with the RenderComponent.
	 * 
	 * @param path the path to the texture
	 */
	void addTexture(const char* path) {
		texture.createTexture(path);
	}

	void update(GLFWwindow * window) {};
};

#endif
