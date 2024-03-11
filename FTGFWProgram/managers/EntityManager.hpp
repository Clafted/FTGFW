#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "../scene/Entity.hpp"
#include <memory>
#include <unordered_map>
#include <stack>

#define MAX_ENTITIES 5000

class EntityManager {
public:
	std::stack<unsigned int> entityIDs;
	std::unordered_map<unsigned int, std::shared_ptr<Entity>> entities;

	EntityManager();
	std::shared_ptr<Entity> createEntity();
	void destroyEntity(std::shared_ptr<Entity> entity);
};

#endif