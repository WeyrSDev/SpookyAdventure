#include "World.h"
#include "Platform.h"
#include "Collectable.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

World::World()
{

	player = new Player({ 40,40 }, *this);
	player->SetPosition({ 60,450 });

	for (int i = worldObjectCount; i < 5; i++)
	{
		//worldObjects[i] = new Platform({ 200,40 });
		worldObjects.push_back(new Platform({ 200,40 }));
		worldObjectCount++;
		if (i == 0)
		{
			worldObjects.at(i)->SetPosition({ 30,WINDOW_HEIGHT - 40 });
		}
		else if (i>0)
		{
			worldObjects.at(i)->SetPosition(worldObjects[i - 1]->GetPosition() + sf::Vector2f({ 300,-100 }));
		}
	}

	// SPAWN COLLECTABLES
	for (int i = worldObjectCount; i < 8; i++)
	{
		worldObjectCount++;
		worldObjects.push_back(new Collectable({ 50,50 }));
		worldObjects.at(i)->SetPosition({ 100,WINDOW_HEIGHT - 300 });
	}
}


World::~World()
{
}

GameObject * World::FindClosestObject(GameObject * object)
{
	double tempDistance = 0;
	double closestDistance = (float)1e10;

	GameObject* closestObject = nullptr;

	int x1, x2, y1, y2;

	for (int i = 0; i < worldObjectCount; i++) // TODO CHANGE TO GET WORLD Objects COUNT
	{
		if (worldObjects[i] == nullptr)
		{
			continue;
		}

		y1 = object->GetYPosition();
		y2 = worldObjects[i]->GetYPosition();
		x1 = object->GetXPosition();
		x2 = worldObjects[i]->GetXPosition();

		int distanceX = (x2 - x1) * (x2 - x1);
		int distanceY = (y2 - y1) * (y2 - y1);

		tempDistance = sqrt(distanceX - distanceY);

		if (tempDistance < closestDistance)
		{
			closestDistance = tempDistance;
			closestObject = worldObjects[i];
		}

	}

	//cout << "closest pos: " << closestObject->GetPosition().x << "player pos: " << object->GetPosition().x << endl;

	return closestObject;
}

Player * World::GetPlayer()
{
	return player;
}

int World::GetWorldObjectCount()
{
	return worldObjectCount;
}

std::vector<GameObject*> World::GetWorldObjectList()
{
	return worldObjects;
}
