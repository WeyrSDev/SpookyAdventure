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


		if (world->GetPlayer()->GetXPosition() > view.getCenter().y)
		{
			view.move(sf::Vector2f({ world->GetPlayer()->GetVelocity().x, world->GetPlayer()->GetVelocity().y / 2 }));
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
		window.clear();

		if (world)
		{
			for (int i = 0; i < world->GetWorldObjectCount(); i++)
			{
				world->GetWorldObjectList()[i]->DrawTo(window);
			}
		}

		if (world->GetPlayer() != nullptr)
		{
			world->GetPlayer()->DrawTo(window);
		}
		window.display();



		
	}

	return 0;
}

