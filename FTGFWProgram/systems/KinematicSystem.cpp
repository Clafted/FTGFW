#include "KinematicSystem.hpp"

void KinematicSystem::update(GLFWwindow* window, float deltaTime)
{
	std::shared_ptr<KinematicComponent> component;
	for (auto i =  componentManager.getComponentMap<KinematicComponent>()->begin(); i != componentManager.getComponentMap<KinematicComponent>()->end(); i++) 
	{
		component = std::dynamic_pointer_cast<KinematicComponent>(i->second);
		// Change facing-direction depending on rotation angle
		component->direction.y = sin(component->rotation.x);
		component->direction.x = -sin(component->rotation.y) * cos(component->rotation.x);
		component->direction.z = -cos(component->rotation.y) * cos(component->rotation.x);
		component->direction = glm::normalize(component->direction);
		// Update velocity and position
		component->velocity += component->acceleration * deltaTime;
		component->pos += component->velocity * deltaTime;
	}
}