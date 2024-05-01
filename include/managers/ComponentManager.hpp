#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "../component/Component.hpp"
#include "../scene/Entity.hpp"
#include <unordered_map>
#include <memory>

using namespace std;
using componentMap = unordered_map<shared_ptr<Entity>, shared_ptr<Component>>;

class ComponentManager {
public:

	template<typename T>
	inline void addComponent(shared_ptr<T> component, shared_ptr<Entity> entity) {
		if (componentMaps.find(typeid(T).name()) == componentMaps.end())
			componentMaps.insert({ typeid(T).name(), make_shared<componentMap>()});

		componentMaps.find(typeid(T).name())->second->emplace( entity, component );
	};

	template<typename T, typename... Args>
	inline void addComponent(shared_ptr<Entity> entity, Args... args) {
		addComponent(make_shared<T>(args...), entity);
	}

	template <typename T>
	inline void addComponents(unordered_map<shared_ptr<T>, shared_ptr<Entity>> components) {
		for (auto i = components.begin(); i != components.end(); i++)
			addComponent(i->first, i->second);
	}

	template <typename T>
	void removeComponent(shared_ptr<Entity> entity) 
	{
		if (componentMaps.find(typeid(T).name()) != componentMaps.end())
			componentMaps.at(typeid(T).name()).erase(entity);
	};

	template <typename T>
	shared_ptr<T> getComponent(shared_ptr<Entity> entity) {
		if (componentMaps.find(typeid(T).name()) != componentMaps.end())
			return dynamic_pointer_cast<T>(componentMaps.find(typeid(T).name())->second->find(entity)->second);
		return nullptr;
	};

	template <typename T>
	shared_ptr<T> getComponent(std::string name)
	{
		shared_ptr<componentMap> map = componentMaps.find(typeid(T).name())->second;
		if (!map) return nullptr;
		for (auto component = map->begin(); component != map->end(); component++)
			if (component->first->name == name) return dynamic_pointer_cast<T>(map->find(component->first)->second);
	}

	template <typename T>
	bool hasComponentOfType(shared_ptr<Entity> entity)
	{
		return componentMaps.find(typeid(T).name()) != componentMaps.end()
			&& componentMaps.find(typeid(T).name())->second->find(entity) != componentMaps.find(typeid(T).name())->second->end();
	}

	template <typename T>
	shared_ptr<unordered_map<shared_ptr<Entity>, shared_ptr<Component>>> getComponentMap() 
	{
		if (componentMaps.find(typeid(T).name()) != componentMaps.end())
			return componentMaps.find(typeid(T).name())->second;

		return nullptr;
	}

	void clearComponents()
	{
		for (auto map : componentMaps)
			map.second->clear();
	}

private:
	unordered_map<const char*, shared_ptr<componentMap>> componentMaps;
};

#endif