#ifndef PPLANE_H
#define PPLANE_H

#include "scene/Entity.hpp"
#include "component/RenderComponent.hpp"
#include <stb_image.h>

class ProceduralPlane :public Entity {
public:
	std::vector<float> genVertices;
	std::vector<int> genIndices;
	unsigned int width, height;
	RenderComponent* render = nullptr;

	ProceduralPlane() {
		generateVertices();
		render = new RenderComponent(&genVertices.data()[0], &genIndices.data()[0], genVertices.size() * sizeof(float), genIndices.size() * sizeof(int), GL_DYNAMIC_DRAW, "C:/Users/User/source/repos/FTGFW/FTGFW/textures/PlainGrass.png");
		components.push_back(render);
	}

	~ProceduralPlane() {
		delete render;
	}

	void generateVertices() {
		int width, height, nrChannels;
		unsigned char* loadedNoise = stbi_load("textures/Perlin_noise_example.png", &width, &height, &nrChannels, 1);
		this->width = width;
		this->height = height;
		if (!loadedNoise) {
			std::cout << "FAILED TO LOAD NOISE TEXTURE" << std::flush;
			std::cout << stbi_failure_reason();
			return;
		}
		
		for (int i = 0; i < width * height; i++) {
			genVertices.push_back((i % width) * 5.0f);
			genVertices.push_back(loadedNoise[i] - 2.0f);
			genVertices.push_back((i / width) * 5.0f);

			genVertices.push_back((i % width) / (float)width);
			genVertices.push_back(i / (float) width / (float) height);

			genVertices.push_back(0.0f);
			genVertices.push_back(1.0f);
			genVertices.push_back(0.0f);
		}

		for (int i = 0; i < width * (height - 1) - 2; i++) {
			// Skip the end of the row
			if ((i + 1) % width == 0) continue;
			// Generate indices for two triangles sharing an edge
			// ----------------------------------------------------
			// Triangle 1
			genIndices.push_back(i);
			genIndices.push_back(i + 1);
			genIndices.push_back(i + width);
			// Triangle 2
			genIndices.push_back(i + 1);
			genIndices.push_back(i + width);
			genIndices.push_back(i + width + 1);
		}

		glm::vec3 vertex1, vertex2, vertex3, vertex4, normal;

		// Calculate the normals of the vertices
		// -------------------------------------------------------------------------------------------------------------
		for (int i = 0; i < width * (height - 1) - 1; i++) {
			if ((i + 1) % width == 0) continue;

			vertex1 = glm::vec3(genVertices[i * 8], genVertices[i * 8 + 1], genVertices[i * 8 + 2]);
			vertex2 = glm::vec3(genVertices[(i + 1) * 8], genVertices[(i + 1) * 8 + 1], genVertices[(i + 1) * 8 + 2]);
			vertex3 = glm::vec3(genVertices[(i + width) * 8], genVertices[(i + width) * 8 + 1], genVertices[(i + width) * 8 + 2]);

			normal = glm::cross(vertex2 - vertex1, vertex3 - vertex1);
			normal = glm::normalize(normal);
			genVertices[(i * 8) + 5] = normal.x;
			genVertices[(i * 8) + 6] = normal.y;
			genVertices[(i * 8) + 7] = normal.z;
		}

		stbi_image_free(loadedNoise);
	}

private:
};

#endif