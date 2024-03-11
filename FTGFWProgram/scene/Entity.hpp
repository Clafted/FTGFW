#pragma once
#ifndef ENTITY_H
#define ENTITY_H

struct Entity {
	const unsigned int id;
	Entity(unsigned int id) : id(id) {};
	virtual ~Entity() {};
};

#endif