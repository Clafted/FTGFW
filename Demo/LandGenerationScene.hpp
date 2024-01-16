#ifndef LANDGENERATIONSCENE_H
#define LANDGENERATIONSCENE_H

#include "scene/Scene.hpp"
#include "scene/DroneCamera.hpp"
#include "component/ControllerComponent.hpp"
#include "ProceduralPlane.hpp"
#include "Block.hpp"


class LandGenerationScene : public Scene {
public:
	ProceduralPlane* plane;
	Light* light;
	Block* block;
	float time = 0.0f;
	float previousTime = 0.0f;

	LandGenerationScene() {
		plane = new ProceduralPlane();
		block = new Block();
		light = new Light(glm::vec3(plane->width / 4.0f, 50.0f, plane->height / 4.0f), glm::vec3(1.0f), 50.0f);
		camera = new DroneCamera(screenWidth, screenHeight, 60.0f * glm::pi<float>() / 180.0f, 0.1f, 2000.0f);
		
		camera->kinematic.pos = glm::vec3(plane->genVertices[0], plane->genVertices[1] + 1.0f, plane->genVertices[2]);
		entities = { camera, plane, light, block };
	}

	~LandGenerationScene() {
		delete plane;
		delete block;
		delete light;
	}

	void setupScene() {
		Renderer::Instance()->renderComponents.push_back(plane->render);
		Renderer::Instance()->renderComponents.push_back(&light->render);
		Renderer::Instance()->renderComponents.push_back(&block->rend);
		Renderer::Instance()->lights[0] = &light->light;
		previousTime = (float)glfwGetTime();
	}

	void exitScene() {
		Renderer::Instance()->renderComponents.clear();
		Renderer::Instance()->lights[0] = nullptr;
		time = 0.0f;
	}

	void update(GLFWwindow* window) {
		Scene::update(window);
		time += glfwGetTime() - previousTime;
		previousTime = (float)glfwGetTime();
	}
};

#endif