#include "EntityManager.hpp"

EntityManager::EntityManager() {
	for (int i = 0; i < MAX_ENTITIES; i++)
		entityIDs.push(i);
}

std::shared_ptr<Entity> EntityManager::createEntity() 
{
	int id = entityIDs.top();
	entityIDs.pop();
	entities.insert({ id, std::make_shared<Entity>(id) });

	return entities.find(id)->second;
}

std::shared_ptr<Entity> EntityManager::createEntity(std::string name)
{
	std::shared_ptr<Entity> entity = createEntity();
	entity->name = name;
	return entity;
}

void EntityManager::destroyEntity(std::shared_ptr<Entity> entity) 
{
	entityIDs.push(entity->id);
	entities.erase(entity->id);
}

void EntityManager::clearEntities()
{
	while (!entities.empty())
	{
		entityIDs.push(entities.begin()->first);
		entities.erase(entities.begin());
	}
}