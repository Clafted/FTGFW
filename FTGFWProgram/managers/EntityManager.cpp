#include "EntityManager.hpp"

EntityManager::EntityManager() {
	for (int i = 0; i < MAX_ENTITIES; i++)
		entityIDs.push(i);
}

std::shared_ptr<Entity> EntityManager::createEntity() {
	int id = entityIDs.top();
	entities.insert({ id, std::make_shared<Entity>(id) });
	return entities.find(id)->second;
}

void EntityManager::destroyEntity(std::shared_ptr<Entity> entity) {
	entityIDs.push(entity->id);
	entities.erase(entity->id);
}