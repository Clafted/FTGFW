#ifndef LANDGENERATIONSCENE_H
#define LANDGENERATIONSCENE_H

#include "../scene/Scene.hpp"
#include "../scene/DroneCamera.hpp"
#include "ProceduralPlane.hpp"
#include "Block.hpp"

class LandGenerationScene : public Scene{
public:
	ProceduralPlane* plane;
	Light* light;

	LandGenerationScene(float screenWidth, float screenHeight) 
		: Scene(screenWidth, screenHeight) {

		camera = new DroneCamera(screenWidth, screenHeight, 60.0f);
		plane = new ProceduralPlane();
		plane->render->scale = glm::vec3(2.0f);

		light = new Light();
		light->kinematic.pos = glm::vec3(0.6f, 5.0f, 0.5f);
		light->intensity = 1.0f;
		lights[0] = light;

		renderComponents = { plane->render, &light->render };
		entities = { camera, plane, light };
	}

	~LandGenerationScene() {
		delete plane;
	}
};

#endif