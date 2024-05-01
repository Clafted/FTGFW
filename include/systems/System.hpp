#ifndef SYSTEM_H
#define SYSTEM_H

#include "../../third_party/GLIncludes.hpp"
#include "../managers/ComponentManager.hpp"
#include "../managers/SceneManager.hpp"
#include <string>
#include <unordered_map>
#include <memory>

template <typename T>
using wPtr = std::weak_ptr<T>;
template <typename T>
using sPtr = std::shared_ptr<T>;

class System {
public:
	static ComponentManager * componentManager;
	static SceneManager * sceneManager;

	System() {};
	virtual void update(GLFWwindow* window, float deltaTime) = 0;
};

#endif