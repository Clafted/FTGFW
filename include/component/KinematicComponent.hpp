#pragma once
#ifndef KINEMATICCOMPONENT_H
#define KINEMATICCOMPONENT_H

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"
#include <vector>
#include <memory>

#include "Component.hpp"
#include "../scene/Entity.hpp"

struct KinematicComponent : public Component{
	friend class CollisionSystem;
	// The position
	glm::vec3 pos = glm::vec3(0.0f);
	// A normalized vector of the component's facing direction
	glm::vec3 direction = glm::vec3(0.0f);
	// The rotation on the corresponding axis in radians. Follows the right-handed coordinate system
	glm::vec3 rotation = glm::vec3(0.0f);
	// The velocity. Used to calculate the new position upon calling update()
	glm::vec3 velocity = glm::vec3(0.0f);
	// The acceleration. Used to calculate the new velocity upon calling update()
	glm::vec3 acceleration = glm::vec3(0.0f);
	float frictionFactor = 0.5f;
	// Size dimensions
	float width = 1.0f, height = 1.0f;

	KinematicComponent(float width = 1.0f, float height = 1.0f, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 velocity = glm::vec3(0.0f))
		: pos(pos), velocity(velocity), width(width), height(height) {}

	inline std::vector<std::shared_ptr<Entity>>* getCollisions() { return &collisions; }

	inline bool isCollidingWith(std::shared_ptr<KinematicComponent> other) const {
		return !((pos.x - width / 2 > other->pos.x + other->width / 2)
			|| (pos.x + width / 2 < other->pos.x - other->width / 2)
			|| (pos.y - height / 2 > other->pos.y + other->height / 2)
			|| (pos.y + height / 2 < other->pos.y - other->height / 2));
	}

	inline float speed() {
		return (float)(sqrt(pow(velocity.x, 2) + pow(velocity.y, 2) + pow(velocity.z, 2)));
	}

	inline float accelerationMagnitude() {
		return (float)(sqrt(pow(acceleration.x, 2) + pow(acceleration.y, 2) + pow(acceleration.z, 2)));
	}

	float deltaTime = 0.0f;
	float previousTime = 0.0f;	
	std::vector<std::shared_ptr<Entity>> collisions;
};

#endif