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
    Light* light2 = nullptr;

	DefaultScene() {
        camera = new DroneCamera();
		float vertices [] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
		};

		entity = new Block(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
        entity->rend.setDiffuseMap("textures/container2.png");
        entity->rend.setSpecularMap("textures/container2_specular.png");
		entity->kin.pos = glm::vec3(0.0f, 2.0f, -1.0f);
		entities.push_back(entity);

		entity2 = new Block(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
		entity2->kin.pos = glm::vec3(0.2f, -0.3f, -1.0f);
        entity2->rend.scale = glm::vec3(0.5f, 0.5f, 0.5f);
        entity2->rend.setDiffuseMap("textures/container2.png");
        entity2->rend.setSpecularMap("textures/container2_specular.png");
		entities.push_back(entity2);

        light = new Light(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
        light->kinematic.pos = glm::vec3(0.6f, 0.6f, 0.5f);
        light->render.scale = glm::vec3(0.2f, 0.2f, 0.2f);
        light->intensity = 0.5f;
        entities.push_back(light);
        lights[0] = light;

        light2 = new Light(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
        light2->kinematic.pos = glm::vec3(-0.2f, 0.1f, -1.5f);
        light2->lightColor = glm::vec3(0.9f, -0.2f, 0.0f);
        light2->render.scale = glm::vec3(0.2f, 0.2f, 0.2f);
        light2->intensity = 0.8f;
        entities.push_back(light2);
        lights[1] = light2;

        renderComponents = { &entity->rend, &entity2->rend, &light->render, &light2->render };

		camera->kinematic.pos = glm::vec3(0.0f, 0.0f, 3.0f);
		entities.push_back(camera);
	}

	~DefaultScene() {
		delete entity;
	}

	inline Scene* update() {
		entity->rend.rotationAngle = (float)glfwGetTime() / glm::pi<float>();
 		return nullptr;
	}
};

#endif