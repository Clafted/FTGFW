#pragma once
#ifndef DEFAULTSCENE_H
#define DEFAULTSCENE_H

#include "../scene/Scene.hpp"
#include "../scene/Light.hpp"
#include "Block.hpp"

class DefaultScene : public Scene {
public:
	Block* entity = nullptr;
	Block* entity2 = nullptr;
    Light* light = nullptr;

	DefaultScene() {
		float vertices [] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};
		entity = new Block(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
		entity->rend.addTexture("textures/Brick_Texture.png");
		entity->kin.pos = glm::vec3(0.0f, 2.0f, -1.0f);
		renderComponents.push_back(&entity->rend);
		entities.push_back(entity);

		entity2 = new Block(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
		entity2->kin.pos = glm::vec3(0.2f, -0.3f, -1.0f);
        entity2->rend.scale = glm::vec3(0.5f, 0.5f, 0.5f);
		renderComponents.push_back(&entity2->rend);
		entities.push_back(entity2);

        light = new Light(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
        light->kinematic.pos = glm::vec3(1.0f, 1.0f, 0.5f);
        light->render.scale = glm::vec3(0.2f, 0.2f, 0.2f);
        renderComponents.push_back(&light->render);
        entities.push_back(light);
        lights.push_back(light);

		camera.kinematic.pos = glm::vec3(0.0f, 0.0f, 3.0f);
		entities.push_back(&camera);
	}

	~DefaultScene() {
		delete entity;
	}

	inline Scene* update() {
		entity->rend.rotationAngle = (float)glfwGetTime() / glm::pi<float>();
        light->lightColor.r = 0.5f * sin(3.1415f * glfwGetTime()) + 0.5f;
        light->lightColor.g = 0.5f * sin(3.1415f * (glfwGetTime() - 1.57f)) + 0.5f;
        light->lightColor.b = 0.5f * sin(3.1415f * (glfwGetTime() - 3.14f)) + 0.5f;
 		return nullptr;
	}
};

#endif