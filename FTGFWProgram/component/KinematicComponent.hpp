#pragma once
#ifndef KINEMATICCOMPONENT_H
#define KINEMATICCOMPONENT_H

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"

#include "Component.hpp"

class KinematicComponent : public Component{
public:
	friend class CollisionManager;
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
	// Size dimensions
	float width = 1.0f, height = 1.0f;

	KinematicComponent(const char * entityName, const char* entityTag) : Component(entityName, entityTag) {}
	KinematicComponent(const char * entityName, const char* entityTag, glm::vec3 pos, glm::vec3 velocity, float width, float height) 
		: Component(entityName, entityTag), pos(pos), velocity(velocity), width(width), height(height) {}
	~KinematicComponent(){}

	void update(GLFWwindow * window) {
		deltaTime = (float)glfwGetTime() - previousTime;
		// Limit deltaTime
		if (deltaTime >= 0.15f) deltaTime = 0.15f;
		previousTime = (float)glfwGetTime();
		// Change facing-direction depending on rotation angle
		direction.y = sin(rotation.x);
		direction.x = -sin(rotation.y) * cos(rotation.x);
		direction.z = -cos(rotation.y) * cos(rotation.x);
		direction = glm::normalize(direction);
		// Update velocity and position
		velocity += acceleration * deltaTime;
		pos += velocity * deltaTime;
	};

	inline bool isCollidingWith(KinematicComponent& other) {
		return !((pos.x - width / 2 > other.pos.x + other.width / 2)
			|| (pos.x + width / 2 < other.pos.x - other.width / 2)
			|| (pos.y - height / 2 > other.pos.y + other.height / 2)
			|| (pos.y + height / 2 < other.pos.y - other.height / 2));
	}

	inline std::vector<KinematicComponent*>& getCollisions() { return collisions; }

	inline float speed() {
		return (float)(sqrt(pow(velocity.x, 2) + pow(velocity.y, 2) + pow(velocity.z, 2)));
	}

	inline float accelerationMagnitude() {
		return (float)(sqrt(pow(acceleration.x, 2) + pow(acceleration.y, 2) + pow(acceleration.z, 2)));
	}

private:
	float deltaTime = 0.0f;
	float previousTime = 0.0f;	
	std::vector<KinematicComponent*> collisions = {};
};

#endif