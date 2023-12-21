#ifndef BLOCK_H
#define BLOCK_H

#include "../scene/Entity.hpp"
#include "../component/KinematicComponent.hpp"
#include "../component/RenderComponent.hpp"

class Block : public Entity {
public:
	KinematicComponent kin;
	RenderComponent rend;
	Block(const void* vertices, GLsizeiptr size, GLenum usage) : rend(vertices, size, usage) {
		components.push_back(&kin);
		components.push_back(&rend);
	};
	~Block() {};
};

#endif