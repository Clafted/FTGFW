#pragma once
#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "../openGLObjects/OpenGLObject.hpp"
#include "../openGLObjects/Texture.hpp"
#include "../openGLObjects/VAO.hpp"
#include "../openGLObjects/VBO.hpp"
#include "../openGLObjects/EBO.hpp"
#include "../shaders/Shader.hpp"
#include "Component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

/*
 * The RenderComponent class represents anything that can be rendered.
 * 
 * As a result, each RenderComponent object has at leasts its own VBO
 * and VAO.
 * 
 * @author Noah Perez
 */
struct RenderComponent : public Component{
public:
	std::vector<OpenGLObject*> glObjects = {};
	std::vector<Texture> textures = {};
	glm::vec3 modelPos = glm::vec3(0.0f);
	glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f);

	VBO vbo;
	VAO vao;
	EBO ebo;

	std::weak_ptr<Shader> shader;

	float rotationAngle = 0.0f;

	RenderComponent(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, std::shared_ptr<Shader> shader = nullptr) 
		: textures(textures), shader(shader)
	{
		vao.bindObject();
		ebo = EBO(&indices[0], indices.size() * sizeof(unsigned int), GL_DYNAMIC_DRAW);
		vbo = VBO(&vertices[0], vertices.size() * sizeof(float), GL_DYNAMIC_DRAW);
	}

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
	 * @param sizeOfVertices - the size of the array of vertices
	 * @param sizeOfIndices - the size of the array of indices
	 * @param usage - how the vertices will be rendered */
	RenderComponent(const void* vertices, const void* indices, GLsizeiptr sizeOfVertices, GLsizeiptr sizeOfIndices, std::shared_ptr<Shader> shader = nullptr, std::string diffusePath = Texture::defaultPath, std::string specularPath = Texture::defaultPath, GLenum usage = GL_DYNAMIC_DRAW)
		: shader(shader)
	{
		vao.bindObject();
		ebo = EBO(indices, sizeOfIndices, usage);
		vbo = VBO(vertices, sizeOfVertices, usage);

		glActiveTexture(GL_TEXTURE0);
		setDiffuseMap(diffusePath.c_str());
		glActiveTexture(GL_TEXTURE1);
		setSpecularMap(specularPath.c_str());
		
		glObjects = { &vao, &vbo, &ebo };
	}

	~RenderComponent() {
		glObjects.clear();
		textures.clear();
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
		textures.push_back(Texture(path.c_str(), Texture::DIFFUSE));
	}

	/* Set the specular map of the RenderComponent.
	 *
	 * @param path - the path to the specular map*/
	void setSpecularMap(std::string path) {
		textures.push_back(Texture(path.c_str(), Texture::SPECULAR));
	}
};

#endif
