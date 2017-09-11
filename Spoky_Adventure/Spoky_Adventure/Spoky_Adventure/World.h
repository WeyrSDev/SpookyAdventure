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

	GameObject* FindClosestObject(GameObject* object);

	Player* GetPlayer();

	int GetWorldObjectCount();
	std::vector<GameObject*> GetWorldObjectList();

	void DestroyObjectAt(int i);
};

