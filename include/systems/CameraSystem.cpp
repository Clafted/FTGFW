#include "CameraSystem.hpp"

void CameraSystem::update(GLFWwindow* window, float deltaTime) 
{
	auto components = componentManager->getComponentMap<CameraComponent>();
	std::shared_ptr<CameraComponent> camera;
	for (auto i = components->begin(); i != components->end(); i++) 
	{
		camera = std::dynamic_pointer_cast<CameraComponent>(i->second);
		camera->direction = glm::normalize(glm::vec3(
				sin(camera->rotation.y),
				sin(camera->rotation.x),
				-cos(camera->rotation.y) * cos(camera->rotation.x)
			));
		camera->forward = camera->direction;
		camera->up = glm::vec3(0.0f, 1.0f, 0.0f);
		camera->right = glm::cross(camera->forward, camera->up);
	}
}