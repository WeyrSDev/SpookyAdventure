#include "World.h"
#include "Platform.h"
#include "Collectable.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

World::World()
{
	playerScore = 0;

	//player = new Player({ 40,40 }, *this);
	player = new Player({ 0.2f,0.2f }, *this);
	worldObjects.push_back(player);
	worldObjectCount++;
	player->SetPosition({ 60,450 });

	// SPAWN PLATFORMS
	for (int i = worldObjectCount; i < 5; i++)
	{
		//worldObjects[i] = new Platform({ 200,40 });
		//worldObjects.push_back(new Platform({ 300,40 }));
		worldObjects.push_back(new Platform({ 1,0.2f },*this));
		worldObjectCount++;
		
		if (i == 1)
		{
			worldObjects.at(i)->SetPosition({ 30,WINDOW_HEIGHT - 40 });
		}
		else if (i>1)
		{
			worldObjects.at(i)->SetPosition(worldObjects[i - 1]->GetPosition() + sf::Vector2f({ 500,-100 }));
		}
	}
	
	// SPAWN COLLECTABLES
	for (int i = 0; i < worldObjectCount; i++)
	{
		if (worldObjects[i]->GetObjectTag() == "Platform")
		{
			worldObjectCount++;
			worldObjects.push_back(new Collectable({ 0.3f,0.3f },*this));

			sf::Vector2f position = sf::Vector2f({ worldObjects[i]->GetShape().width /2, -260 });
			position += worldObjects[i]->GetPosition();
			worldObjects.back()->SetPosition(position);
		}
	}
	
	//SPAWN ENEMIES
	for (int i = 1; i < worldObjectCount; i++)
	{
		if (worldObjects[i]->GetObjectTag() == "Platform")
		{
			worldObjectCount++;
			worldObjects.push_back(new Enemy({ 0.2f,0.2f },*this));

			sf::Vector2f position = sf::Vector2f({ worldObjects[i]->GetShape().width / 2, - 44 });
			position += worldObjects[i]->GetPosition();
			worldObjects.back()->SetPosition(position);
		}
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

		if (worldObjects[i] == object)
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

void World::DestroyObjectAt(int i)
{
	worldObjects.erase(worldObjects.begin() + i);
	worldObjectCount--;
}

void World::GiveScore(int score)
{
	playerScore += score;
}

int World::GetScore()
{
	return playerScore;
}
