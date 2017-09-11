#pragma once
#include "GameObject.h"
#include "Player.h"

class World
{
private:
	std::vector<GameObject*> worldObjects;
	int worldObjectCount = 0;
	Player* player;

public:
	World();
	~World();

	GameObject* FindClosestObject(std::vector<GameObject*>& objectList, GameObject* object);

	Player* GetPlayer();
};

