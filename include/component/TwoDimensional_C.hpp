#ifndef TWODIMENSIONAL_C_H
#define TWODIMENSIONAL_C_H

#include "RenderComponent.hpp"
#include "../data/NativeShapes.hpp"

using namespace NativeShapes::FlatPlane;

struct TwoDimensional_C : public RenderComponent
{
	TwoDimensional_C(std::string diffuse, std::string specular, std::shared_ptr<Shader> shader = nullptr) 
		: RenderComponent(&vertices, &indices, verticesSize, indicesSize, shader, diffuse, specular) 
	{
		rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	}
};

#endif