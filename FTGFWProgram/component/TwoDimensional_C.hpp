#ifndef TWODIMENSIONAL_C_H
#define TWODIMENSIONAL_C_H

#include "RenderComponent.hpp"
#include "../data/NativeShapes.hpp"

using namespace NativeShapes::FlatPlane;

struct TwoDimensional_C : public RenderComponent
{
	TwoDimensional_C(std::string diffuse, std::string specular) 
		: RenderComponent(&vertices, &indices, verticesSize, indicesSize, diffuse, specular) {}
};

#endif