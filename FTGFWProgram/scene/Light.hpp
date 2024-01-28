#ifndef LIGHT_H
#define LIGHT_H

#include "LightCasters.hpp"
#include "Entity.hpp"
#include "../component/KinematicComponent.hpp"
#include "../component/RenderComponent.hpp"
#include "../data/NativeShapes.hpp"

class Light : public Entity {
public:
	KinematicComponent kinematic;
	RenderComponent render;

    PointLight light;

	Light(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 lightColor = glm::vec3(1.0f), float intensity = 1.0f)
	    : light(pos, lightColor, intensity) {

        render = RenderComponent(NativeShapes::Cube::vertices,
								NativeShapes::Cube::indices,
								sizeof(NativeShapes::Cube::vertices),
								sizeof(NativeShapes::Cube::indices),
								GL_DYNAMIC_DRAW,
								"C:/Users/User/source/repos/FTGFW/Bubble/textures/flat_specular.png",
								"C:/Users/User/source/repos/FTGFW/Bubble/textures/flat_specular.png");
        kinematic.pos = pos;
        components = { &kinematic, &render };
	}
	~Light() {}

	inline void update(GLFWwindow* window) {
		render.modelPos = kinematic.pos;
	}
};

#endif