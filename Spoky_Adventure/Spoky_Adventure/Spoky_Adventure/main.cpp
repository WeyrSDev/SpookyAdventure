#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Player.h"
#include "Platform.h"
#include "Collectable.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

using namespace std;

int worldObjectCount = 0;

int main()
{


	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Spooky Adventure");
	sf::View view;
	view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

	float viewCentreY = (WINDOW_HEIGHT / 2);
	window.setFramerateLimit(120);

	sf::Clock deltaClock;

	World* world = new World();

	while (window.isOpen())
	{
		sf::Event event;


		sf::Time time = deltaClock.getElapsedTime();
		float delta = time.asSeconds();

		world->GetPlayer()->Update(delta);

		

		//INPUTS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			world->GetPlayer()->Jump();
			//if(world->GetPlayer()->isGrounded)
			//world->GetPlayer()->GetVelocity().y = (-jumpSpeed) * delta; // TODO make update function in gameObject class then call jump on player object
				//cout << "jump pressed " << endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			world->GetPlayer()->MoveLeft();
			//cout << "jump pressed " << endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			world->GetPlayer()->MoveRight();
			//cout << "jump pressed " << endl;
		}

		deltaClock.restart().asSeconds();

		/* 

		//player->Move(velocity);

		GameObject* closestObject = nullptr;// = world->FindClosestObject(worldObjects, world->GetPlayer());


		if (closestObject != nullptr)
		{
			closestObject->ChangeColour(sf::Color::Magenta);

			//if (world->GetPlayer()->CheckCollisionWith(*closestObject) == 1)
			{
				//cout << "Colliding at top " << endl;
				if (closestObject->GetObjectTag() == "Platform")
				{
					//velocity.y += jumpSpeed;
				}



			}

			//if (world->GetPlayer()->CheckCollisionWith(*closestObject) == 2)
			{
				//cout << "Colliding at bottom " << endl;
				if (closestObject->GetObjectTag() == "Platform")
				{
					//isGrounded = true;
					//velocity.y = 0.0f;
				}



			}
			else
			{
				//isGrounded = false;
			}

			//if (world->GetPlayer()->CheckCollisionWith(*closestObject) > 0) // if colliding simple collision
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
		}*/

		//if (world->GetPlayer()->GetXPosition() > view.getCenter().y)
		{
			//view.move(sf::Vector2f({ velocity.x, velocity.y / 2 }));
		}

		window.setView(view);



		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased)
			{
				//velocity.x = 0;
			}
		}

;
		//player.CheckCollisionWith(platform01.GetShape());
	

		//cout << player.CheckCollisions();
		window.clear();
		//platform01.DrawTo(window);
		//for (int i = 0; i < worldObjectCount; i++)
		//{
			//worldObjects[i]->DrawTo(window);
		//}

		if (world->GetPlayer() != nullptr)
		{
			world->GetPlayer()->DrawTo(window);
		}
		window.display();



		
	}

	return 0;
}

