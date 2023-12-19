#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "Component.hpp"
#include <array>

class Entity {
public:
	std::vector<Component> components;
};

#endif