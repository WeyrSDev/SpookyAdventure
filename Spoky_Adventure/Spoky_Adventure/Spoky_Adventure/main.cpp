#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <string>
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

	// Declare and load a font
	sf::Font uIFont;
	uIFont.loadFromFile("DigitalSystem.ttf");


	sf::Text PlayerUI;
	PlayerUI.setFont(uIFont);
	PlayerUI.setCharacterSize(42);
	PlayerUI.setStyle(sf::Text::Bold);
	string uiText = "Player Score: 1000";
	PlayerUI.setString(uiText);
	PlayerUI.setFillColor(sf::Color::Magenta);
	

	float viewCentreY = (WINDOW_HEIGHT / 2);
	window.setFramerateLimit(120);
	// Get elapsed time
	//float ElapsedTime = window.GetFrameTime();

	sf::Clock deltaClock;

	World* world = new World();


	while (window.isOpen())
	{
		sf::Event event;


		sf::Time time = deltaClock.getElapsedTime();
		float delta = time.asSeconds();

		world->GetPlayer()->Update(delta);

		for (int i = 1; i < world->GetWorldObjectCount(); i++)
		{
			world->GetWorldObjectList()[i]->Update(delta);
		}


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

		PlayerUI.setPosition(sf::Vector2f({view.getViewport().left + 20,view.getViewport().top + 20 }));



		//window.draw(PlayerUI);


		// MOVE CAMERA
		if (world->GetPlayer()->GetXPosition() > view.getCenter().y)
		{
			view.move(sf::Vector2f({ world->GetPlayer()->GetVelocity().x, world->GetPlayer()->GetVelocity().y / 2 }));
		}




		deltaClock.restart().asSeconds();

		window.setView(view);



		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


			if (world)
			{
				for (int i = 1; i < world->GetWorldObjectCount(); i++)
				{
						world->GetWorldObjectList()[i]->DrawTo(window);
				}

				world->GetPlayer()->DrawTo(window);
			}

			// Set the default view back
			window.setView(window.getDefaultView());


			//DRAW UI
			// Render stuff not affected by the view
			// UPDATE SCORE
			uiText = "Player score: ";// + world->GetScore();
			string scoreTxt = std::to_string(world->GetScore());
			uiText += scoreTxt;
			PlayerUI.setString(uiText);
			window.draw(PlayerUI);

		window.display();
		window.clear();


		
	}

	return 0;
}

