#include "CollisionManager.hpp"

CollisionManager* CollisionManager::instance = nullptr;

CollisionManager::~CollisionManager() { kinComponents.clear(); }

CollisionManager* CollisionManager::getInstance() {
	if (!instance) instance = new CollisionManager();
	return instance;
}

void CollisionManager::terminate() {
	delete instance;
}

void CollisionManager::checkCollisions() {
	KinematicComponent* target = nullptr, *other = nullptr;
	for (int i = 0; i < kinComponents.size(); i++) {
		target = kinComponents.at(i);
		target->collisions.clear();
		for (int j = i + 1; j < kinComponents.size(); j++) {
			other = kinComponents.at(j);
			if (target->isCollidingWith(*other)) {
				target->collisions.push_back(other);
			}
		}
	}
}