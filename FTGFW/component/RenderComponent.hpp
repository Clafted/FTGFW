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
	Texture diffuseMap;
	Texture specularMap;

	glm::vec3 modelPos;
	glm::vec3 rotationAxis;
	glm::vec3 scale;
	float rotationAngle;

	RenderComponent()
		: modelPos(0.0f),
		  rotationAxis(0.0f, 1.0f, 0.0f),
		  scale(1.0f),
		  rotationAngle(0.0f) {}

	/**
	 * A Constructor for the RenderComponent class
	 *
	 * NOTE: Since RenderComponent objects include textures,
	 * the vertices provided MUST contain the following three
	 * pieces of vertex information (in the same order):
	 * 1. 3D Model Coordinates
	 * 2. 2D Texture Coordinates
	 * 3. 3D Normal Vector
	 * 
	 * @param vertices - a pointer to the array of vertices
	 * @param size - the size of the array of vertices
	 * @param usage - how the vertices will be rendered */
	RenderComponent(const void* vertices, GLsizeiptr size, GLenum usage, std::string diffusePath = Texture::defaultPath, std::string specularPath = Texture::defaultPath) 
		: modelPos(0.0f),
		  rotationAxis(0.0f, 1.0f, 0.0f),
	      scale(1.0f),
		  rotationAngle(0.0f) {

		vao.bindObject();
		vbo = VBO(vertices, size, usage);
		diffuseMap = Texture(diffusePath.c_str());
		specularMap = Texture(specularPath.c_str());

		glObjects.assign(0, &vao);
		glObjects.assign(1, &vbo);
		glObjects.assign(2, &diffuseMap);
		glObjects.assign(3, &specularMap);
	}

	~RenderComponent() {
		glObjects.clear();
	}
	/* Get the ID of the VAO of the renderable component
	 * 
	 * @return ID of VAO containing the graphics data  */
	unsigned int vaoID() {
		return glObjects[0]->ID;
	}

	/* Add a diffuseMap to use with the RenderComponent.
	 * 
	 * @param path - the path to the diffuseMap */
	void setDiffuseMap(std::string path) {
		diffuseMap.createTexture(path.c_str());
	}

	/* Set the specular map of the RenderComponent.
	 *
	 * @param path - the path to the specular map*/
	void setSpecularMap(std::string path) {
		specularMap.createTexture(path.c_str());
	}

	void update(GLFWwindow * window) {};
};

#endif
