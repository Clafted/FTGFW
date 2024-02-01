#pragma once 
#ifndef COMPONENT_H
#define COMPONENT_H

#include "../../third_party/GLIncludes.hpp"
#include <vector>

class Component {	
public:
	Component(const char* entityName, const char* entityTag) : entityName(entityName), entityTag(entityTag) {};
	virtual void update(GLFWwindow * window) = 0;
	inline const char* getEntityName() const { return entityName; }
	inline const char* getEntityTag() const { return entityTag; }
protected:
	const char* entityName;
	const char* entityTag;
};

#endif