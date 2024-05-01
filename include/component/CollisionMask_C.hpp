#pragma once

#include <vector>
#include <string>
#include <stb_image.h>

#include "Component.hpp"
#include "../scene/Entity.hpp"
#include "glm/vec3.hpp"

/*
* A Component to detect 2D-collisions between 2D-textures.
* 
*/
struct CollisionMask_C : public Component {
	unsigned char* texture;
	int width, height;
	std::vector<bool> mask;
	std::vector<Entity> collisions = {};
	glm::vec3 pos = glm::vec3(0.0f);

	CollisionMask_C(std::string texture) {
		int nrChannels;
		this->texture = stbi_load(texture.c_str(), &width, &height, &nrChannels, 0);
		mask = std::vector<bool>(width * height);

		if (nrChannels != 4) return;

		for (int i = 0; i < width * height; i += 4) {
			mask[i / 4] = ((float)this->texture[i + 3] > 0.0f);
		}
	}

	bool isCollidingWith(CollisionMask_C& other) {
		// AABB collision pass
		if (pos.z != other.pos.z
			||pos.x + width / 2 < other.pos.x - other.width / 2
			|| pos.x - width / 2 > other.pos.x + other.width / 2
			|| pos.y + height / 2 < other.pos.y - other.height / 2
			|| pos.x - height / 2 > other.pos.y + other.height / 2) return false;

		int l, r, t, b, oL, oR, oT, oB;
		if (pos.x < other.pos.x) {
			l = (int)other.pos.x - other.width / 2;
			r = (int)pos.x + width / 2;
		} else {
			l = (int)pos.x - width / 2;
			r = (int)other.pos.x + other.width / 2;
		}

		if (pos.y < other.pos.y) {
			t = (int)pos.y + height / 2;
			b = (int)other.pos.y - other.height / 2;
		} else {
			t = (int)other.pos.y + other.height / 2;
			b = (int)pos.y - height / 2;
		}


	}

	bool pixelAt(int worldX, int worldY) {
		int x = worldX - (pos.x - width / 2); // Left-side right offset
		int y = worldY - (pos.y + height / 2); // Top-side down offset

		if (x < 0 || y < 0 || x > width || y > height) return false;
		return mask[x + y * width];
	}
};