#include "CollisionSystem.hpp"
#include <memory>
#include "../component/KinematicComponent.hpp"

void CollisionSystem::update(GLFWwindow * window, float deltaTime) {
	std::shared_ptr<KinematicComponent> target, other;
	auto components = componentManager.getComponentMap<KinematicComponent>();
	for (auto i = components->begin(); i != components->end(); i++) {
		target = std::dynamic_pointer_cast<KinematicComponent>(i->second);
		target->collisions.clear();
		for (auto j = ++i; j != components->end(); j++) {
			other = std::dynamic_pointer_cast<KinematicComponent>(j->second);
			if (target->isCollidingWith(other))
				target->collisions.push_back(other);
		}
	}
}