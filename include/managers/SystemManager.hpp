#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "../systems/System.hpp"
#include "../systems/CameraSystem.hpp"
#include "../../third_party/GLIncludes.hpp"

#include <bitset>
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

/*
* A class to manage System objects.
* 
* Allows for the registration and update of systems
*/
class SystemManager {
public:
	std::unordered_map<std::string, std::shared_ptr<System>> systems = {};
	std::vector<const char*> registeredTypes = {};

	void update(GLFWwindow* window, float deltaTime);

	template <typename T>
	void registerSystem() {
		if (systems.find(typeid(T).name()) == systems.end()) {
			systems.insert({ typeid(T).name(), std::make_shared<T>() });
		}
	}

	template <typename T>
	void registerSystem(std::shared_ptr<T> system) {
		if (systems.find(typeid(T).name()) == systems.end()) {
			systems.insert({ typeid(T).name(), system });
		}
	}
};

#endif