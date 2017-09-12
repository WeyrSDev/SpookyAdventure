#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

class World
{
private:
	std::vector<GameObject*> worldObjects;
	int worldObjectCount = 0;
	Player* player;
	int playerScore;

public:
	World();
	~World();

	GameObject* FindClosestObject(GameObject* object);

	Player* GetPlayer();

	int GetWorldObjectCount();
	std::vector<GameObject*> GetWorldObjectList();

	void DestroyObjectAt(int i);

	void GiveScore(int score);
	int GetScore();
};

