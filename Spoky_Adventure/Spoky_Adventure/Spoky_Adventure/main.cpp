#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Collectable.h"

using namespace std;

int main()
{
	#define WINDOW_WIDTH 1280
	#define WINDOW_HEIGHT 800

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Spooky Adventure");
	
	sf::Clock deltaClock;

    window.setFramerateLimit(120);

	std::vector<GameObject*> worldObjects(10);
	
	GameObject* FindClosestObject(std::vector<GameObject*>& objectList, GameObject* object);

	bool isGrounded = false;

	const int groundHeight = 500;
	const float gravitySpeed = 5;
	float jumpSpeed = 550;
	float moveSpeed = 200.0f;

	int worldObjectCount = 0;

	Player* player = new Player({ 40,40 });
	player->SetPosition({ 60,450 });
	//player->SetPosition({ 450,450 });

	//Platform platform01({ 400,40 });
	//platform01.SetPosition({ 30,groundHeight+40 });
	//platform01.SetPosition({ 30, 300 });

	for (int i = worldObjectCount; i < 3; i++)
	{
		worldObjects[i] = new Platform({ 200,40 });
		worldObjectCount++;
		if (i == 0)
		{

			worldObjects[i]->SetPosition({ 30,WINDOW_HEIGHT - 40 });
		}
		else if(i>0)
		{
			worldObjects[i]->SetPosition(worldObjects[i - 1]->GetPosition() + sf::Vector2f({ 300,-100 }));
		}
	}

	// SPAWN COLLECTABLES
	for (int i = worldObjectCount; i < 5; i++)
	{
		worldObjectCount++;
		worldObjects[i] = new Collectable({ 50,50 });
		worldObjects[i]->SetPosition({ 100,WINDOW_HEIGHT - 300 });
	}

	sf::Vector2f velocity(sf::Vector2f(0, 0));

	while (window.isOpen())
	{
		sf::Event event;


		sf::Time time = deltaClock.getElapsedTime();
		float delta = time.asSeconds();

		//GRAVITY
		if (isGrounded == false)
			velocity.y += (gravitySpeed * delta);
		if (velocity.y > 8)
		{
			velocity.y = 8;
		}
			//cout << "Velocity Y is: " << velocity.y << endl;


		//INPUTS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if(isGrounded)
			velocity.y = (-jumpSpeed) * delta;
				//cout << "jump pressed " << endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
				velocity.x = -moveSpeed * delta;
			//cout << "jump pressed " << endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
				velocity.x = moveSpeed * delta;
			//cout << "jump pressed " << endl;
		}


		player->Move(velocity);

		GameObject* closestObject = FindClosestObject(worldObjects, player);


		if (closestObject != nullptr)
		{
			closestObject->ChangeColour(sf::Color::Magenta);

			if (player->CheckCollisionWith(*closestObject) == 1)
			{
				//cout << "Colliding at top " << endl;
				if (closestObject->GetObjectTag() == "Platform")
				{
					velocity.y += jumpSpeed;
				}



			}

			if (player->CheckCollisionWith(*closestObject) == 2)
			{
				//cout << "Colliding at bottom " << endl;
				if (closestObject->GetObjectTag() == "Platform")
				{
					isGrounded = true;
					velocity.y = 0.0f;
				}



			}
			else
			{
				isGrounded = false;
			}

			if (player->CheckCollisionWith(*closestObject) > 0) // if colliding simple collision
			{
				if (closestObject->GetObjectTag() == "Collectable")
				{
					// PICK UP COLLECTABLE
					cout << "pick up" << endl;
					// erase the 6th element

					for (int i = 0; i < worldObjectCount; i++)
					{
						if (worldObjects[i] == closestObject)
						{
							worldObjects.erase(worldObjects.begin() + i);
							worldObjectCount--;
						}
					}
					

				}
			}
		}



		deltaClock.restart().asSeconds();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased)
			{
				velocity.x = 0;
			}
		}

;
		//player.CheckCollisionWith(platform01.GetShape());
	

		//cout << player.CheckCollisions();
		window.clear();
		//platform01.DrawTo(window);
		for (int i = 0; i < worldObjectCount; i++)
		{
			worldObjects[i]->DrawTo(window);
		}

		player->DrawTo(window);

		window.display();

		
	}

	return 0;
}

GameObject* FindClosestObject(std::vector<GameObject*>& objectList, GameObject* object)
{
	double tempDistance = 0;
	double closestDistance = (float)1e10;

	GameObject* closestObject = nullptr;

	int x1, x2, y1, y2;

	for (int i = 0; i < 4; i++) // TODO CHANGE TO GET WORLD Objects COUNT
	{
		if (objectList[i] == nullptr)
		{
			continue;
		}

		y1 = object->GetYPosition();
		y2 = objectList[i]->GetYPosition();
		x1 = object->GetXPosition();
		x2 = objectList[i]->GetXPosition();

		int distanceX = (x2 - x1) * (x2 - x1);
		int distanceY = (y2 - y1) * (y2 - y1);

		tempDistance = sqrt(distanceX - distanceY);

		if (tempDistance < closestDistance)
		{
			closestDistance = tempDistance;
			closestObject = objectList[i];
		}

	}

	//cout << "closest pos: " << closestObject->GetPosition().x << "player pos: " << object->GetPosition().x << endl;

	return closestObject;
}