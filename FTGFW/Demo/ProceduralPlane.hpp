#ifndef PPLANE_H
#define PPLANE_H

#include "../scene/Entity.hpp"
#include "../component/RenderComponent.hpp"

class ProceduralPlane :public Entity {
public:
	std::vector<float> genVertices;
	RenderComponent* render = nullptr;

	ProceduralPlane() {
		generateVertices();
		render = new RenderComponent(&genVertices[0], sizeof(float) * genVertices.size(), GL_DYNAMIC_DRAW);
		components.push_back(render);
	}

	~ProceduralPlane() {
		delete render;
	}

	void generateVertices() {
		genVertices = { 
						0.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
						10.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
						10.0f, 0.0f, 10.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
						10.0f, 0.0f, 10.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
						0.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
						0.0f,  0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f

		};
	}
};

#endif