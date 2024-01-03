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
    Light* light3 = nullptr;

	DefaultScene(float screenWidth, float screenHeigth)
        : Scene(screenWidth, screenHeigth) {

        camera = new DroneCamera(screenWidth, screenHeigth);

		entity = new Block(glm::vec3(0.0f, 2.0f, -1.0f));
        entity->rend.setDiffuseMap("textures/container2.png");
        entity->rend.setSpecularMap("textures/container2_specular.png");


		entity2 = new Block();
        entity2->rend.setDiffuseMap("textures/container2.png");
        entity2->rend.setSpecularMap("textures/container2_specular.png");

        light = new Light();
        light->kinematic.pos = glm::vec3(0.6f, 0.6f, 0.5f);
        light->render.scale = glm::vec3(0.2f, 0.2f, 0.2f);
        light->intensity = 0.5f;
        lights[0] = light;

        light2 = new Light();
        light2->kinematic.pos = glm::vec3(-0.2f, 0.1f, -1.5f);
        light2->lightColor = glm::vec3(0.9f, -0.2f, 0.0f);
        light2->render.scale = glm::vec3(0.2f, 0.2f, 0.2f);
        light2->intensity = 0.8f;
        lights[1] = light2;

        light3 = new Light();
        light3->kinematic.pos = glm::vec3(-0.0f, 0.0f, -0.0f);
        light3->lightColor = glm::vec3(0.9f, -0.2f, 0.0f);
        light3->render.scale = glm::vec3(0.2f, 0.2f, 0.2f);
        light3->intensity = 0.8f;
        lights[2] = light3;

		camera->kinematic.pos = glm::vec3(0.0f, 0.0f, 3.0f);
		
        renderComponents = { &light3->render, &entity->rend, &entity2->rend, &light->render, &light2->render,  };
        entities = { entity, entity2, light, light2, light3, camera };
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