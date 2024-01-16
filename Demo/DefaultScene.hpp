#pragma once
#ifndef DEFAULTSCENE_H
#define DEFAULTSCENE_H


#include "Block.hpp"
#include "scene/SceneManager.hpp"
#include "scene/DroneCamera.hpp"
#include "scene/Scene.hpp"
#include "scene/Light.hpp"

class DefaultScene : public Scene {
public:
	Block* entity = nullptr;
	Block* entity2 = nullptr;
    Light* light = nullptr;
    Light* light2 = nullptr;
    Light* light3 = nullptr;
    float time = 0.0f;
    float previousTime = 0.0f;

	DefaultScene() {
        
        camera = new DroneCamera(screenWidth, screenHeight);

		entity = new Block(glm::vec3(0.0f, 2.0f, -1.0f));
        entity->rend.setDiffuseMap("textures/container2.png");
        entity->rend.setSpecularMap("textures/container2_specular.png");

		entity2 = new Block();
        entity2->rend.setDiffuseMap("textures/container2.png");
        entity2->rend.setSpecularMap("textures/container2_specular.png");

        light = new Light(glm::vec3(0.6f, 0.6f, 0.5f), glm::vec3(0.3f, 1.0f, 0.8f), 0.5f);
        light2 = new Light(glm::vec3(-0.2f, 0.1f, -1.5f), glm::vec3(0.9f, 0.2f, 0.0f), 0.8f);
        light3 = new Light(glm::vec3(-0.0f, 0.0f, -0.0f), glm::vec3(0.9f, -0.2f, 0.0f), 0.8f);

		camera->kinematic.pos = glm::vec3(0.0f, 0.0f, 3.0f);
		
        entities = { entity, entity2, light, light2, light3, camera };
	}

	~DefaultScene() {
	}

    void setupScene() {
        Renderer::Instance()->renderComponents.push_back(&light3->render);
        Renderer::Instance()->renderComponents.push_back(&entity->rend);
        Renderer::Instance()->renderComponents.push_back(&entity2->rend);
        Renderer::Instance()->renderComponents.push_back(&light->render);
        Renderer::Instance()->renderComponents.push_back(&light2->render);

        Renderer::Instance()->lights[0] = &light->light;
        Renderer::Instance()->lights[1] = &light2->light;
        Renderer::Instance()->lights[2] = &light3->light;
        previousTime = (float)glfwGetTime();
    }

    void exitScene() {
        Renderer::Instance()->renderComponents.clear();
        for (int i = 0; i < Renderer::Instance()->lights.size(); i++) {
            Renderer::Instance()->lights[i] = nullptr;
        }
        time = 0.0f;
    }

	inline void update(GLFWwindow * window) {
        Scene::update(window);
		entity->rend.rotationAngle = (float)glfwGetTime() / glm::pi<float>();
        time += glfwGetTime() - previousTime;
        previousTime = (float)glfwGetTime();
	}
};

#endif