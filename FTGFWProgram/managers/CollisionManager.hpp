#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "../component/KinematicComponent.hpp"

class CollisionManager {
public:
	std::vector<KinematicComponent*> kinComponents = {};
	static CollisionManager* instance;

	static CollisionManager* getInstance();
	static void terminate();
	void checkCollisions();
protected:
	CollisionManager() {};
	~CollisionManager();
	
};

#endif