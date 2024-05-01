#include "KinematicSystem.hpp"

void KinematicSystem::update(GLFWwindow* window, float deltaTime)
{
	std::shared_ptr<KinematicComponent> component;
	std::shared_ptr<componentMap> map = componentManager->getComponentMap<KinematicComponent>();
	for (auto i = map->begin(); i != map->end(); i++) {
		component = std::dynamic_pointer_cast<KinematicComponent>(i->second);
		// Change facing-direction depending on rotation angle
		component->direction.y = sin(component->rotation.x);
		component->direction.x = -sin(component->rotation.y) * cos(component->rotation.x);
		component->direction.z = -cos(component->rotation.y) * cos(component->rotation.x);
		component->direction = glm::normalize(component->direction);
		// Update velocity and position
		component->velocity += component->acceleration * deltaTime;
		// Component-wise friction simulation
		if (component->speed() > 0.0f) 
			component->acceleration = -component->velocity * component->frictionFactor;
		component->pos += component->velocity * deltaTime;
	}
}