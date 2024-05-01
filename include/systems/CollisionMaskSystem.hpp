#pragma once

#include "System.hpp"
#include "../component/CollisionMask_C.hpp"

class CollisionMaskSystem : public System {
public:

	void update(GLFWwindow* window, float deltaTime) {
		std::shared_ptr<componentMap> map = componentManager->getComponentMap<CollisionMask_C>();
		if (!map) return;
		std::shared_ptr<CollisionMask_C> _C, other_C;
		for (auto i = map->begin(); i != map->end(); i++) {
			_C = std::dynamic_pointer_cast<CollisionMask_C>(i->second);
			for (auto j = i; j != map->end(); j++) {
				if (j == i) continue;
				other_C = std::dynamic_pointer_cast<CollisionMask_C>(j->second);
				//if ()
			}
		}
	}
};