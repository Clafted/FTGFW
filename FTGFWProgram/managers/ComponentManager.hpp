#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "../component/Component.hpp"
#include "../scene/Entity.hpp"
#include <unordered_map>
#include <memory>

using componentMap = std::unordered_map<std::shared_ptr<Entity>, std::shared_ptr<Component>>;

class ComponentManager {
public:

	template<typename T>
	inline void addComponent(std::shared_ptr<T> component, std::shared_ptr<Entity> entity) 
	{
		if (componentMaps.find(typeid(T).name()) == componentMaps.end())
			componentMaps.insert({ typeid(T).name(), std::make_shared<componentMap>()});

		componentMaps.find(typeid(T).name())->second->insert({ entity, component });
	};

	template <typename T>
	inline void addComponents(std::unordered_map<std::shared_ptr<T>, std::shared_ptr<Entity>> components)
	{
		for (auto i = components.begin(); i != components.end(); i++)
			addComponent(i->first, i->second);
	}

	template <typename T>
	void removeComponent(std::shared_ptr<Entity> entity) 
	{
		if (componentMaps.find(typeid(T).name()) != componentMaps.end())
			componentMaps.at(typeid(T).name()).erase(entity);
	};

	template <typename T>
	std::shared_ptr<T> getComponent(std::shared_ptr<Entity> entity) 
	{
		if (componentMaps.find(typeid(T).name()) != componentMaps.end())
			// Return the Component associated with the Entity ID, located in the componentMap of the appropriate type
			return std::dynamic_pointer_cast<T>(componentMaps.find(typeid(T).name())->second->find(entity)->second);
		return nullptr;
	};

	template <typename T>
	std::shared_ptr<componentMap> getComponentMap() {
		if (componentMaps.find(typeid(T).name()) != componentMaps.end())
			return componentMaps.find(typeid(T).name())->second;

		return nullptr;
	}

private:
	std::unordered_map<const char*, std::shared_ptr<componentMap>> componentMaps;
};

#endif