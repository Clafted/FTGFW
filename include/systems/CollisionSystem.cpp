#include "CollisionSystem.hpp"
#include <memory>
#include "../component/KinematicComponent.hpp"

#define dpcast std::dynamic_pointer_cast

void CollisionSystem::update(GLFWwindow * window, float deltaTime) 
{
	std::shared_ptr<KinematicComponent> target, other;
	auto components = componentManager->getComponentMap<KinematicComponent>();
	for (auto i = components->begin(); i != components->end(); i++) {
		dpcast<KinematicComponent>(i->second)->collisions.clear();
	}
	for (auto i = components->begin(); i != components->end(); i++) {
		target = dpcast<KinematicComponent>(i->second);
		for (auto j = i; j != components->end() && i != components->end(); j++) {
			if (j == i) continue;
			other = dpcast<KinematicComponent>(j->second);
			if (target->isCollidingWith(other)) {
				target->collisions.push_back(j->first);
				other->collisions.push_back(i->first);
			}
		}
	}
}