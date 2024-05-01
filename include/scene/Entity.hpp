#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <string>

struct Entity {
	const unsigned int id;
	std::string name = "";
	Entity(unsigned int id) : id(id) {};
	Entity(unsigned int id, std::string name) : id(id), name(name) {};
	virtual ~Entity() {};
};

#endif