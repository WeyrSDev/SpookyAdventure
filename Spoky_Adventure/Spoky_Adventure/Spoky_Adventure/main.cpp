#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Spoky Adventure");
	
	sf::Clock deltaClock;



	bool isGrounded = false;

	const int groundHeight = 500;
	const float gravitySpeed = 0.005f;
	float jumpSpeed = 2.0f;
	float moveSpeed = 0.3f;

	Player player({ 40,40 });
	player.SetPosition({ 30,450 });

	Platform platform01({ 400,40 });
	platform01.SetPosition({ 30,groundHeight+40 });
	//platform01.SetPosition({ 30, 300 });

	sf::Vector2f velocity(sf::Vector2f(0, 0));

	while (window.isOpen())
	{
		sf::Event event;

		//mySprite.Move(velocity * dt.AsSeconds());

		//cout << "player pos : " << player.GetYPosition() << endl;
		//GRAVITY
		if (player.GetYPosition() < groundHeight)
		{
			isGrounded = false;
			velocity.y += gravitySpeed;
			//cout << "gravity applied" << endl;
		}
		//else
		//{
			//isGrounded = true;
			//velocity.y = 0.0f;
		//}


		//INPUTS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if(isGrounded)
			velocity.y = -jumpSpeed;
				//cout << "jump pressed " << endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (isGrounded)
				velocity.x = -moveSpeed;
			//cout << "jump pressed " << endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
				velocity.x = moveSpeed;
			//cout << "jump pressed " << endl;
		}


		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased)
			{
				velocity.x = 0;
			}
		}

		player.Move(velocity);
		//player.CheckCollisionWith(platform01.GetShape());

		if(player.CheckCollisionWith(platform01) == 1)
		{
			cout << "Colliding at top " << endl;

			velocity.y += jumpSpeed;
		}

		if (player.CheckCollisionWith(platform01) == 2)
		{
			cout << "Colliding at bottom " << endl;
			isGrounded = true;
			velocity.y = 0.0f;
			//velocity.y += jumpSpeed;
		}

		//cout << player.CheckCollisions();
		window.clear();
		platform01.DrawTo(window);
		player.DrawTo(window);

		window.display();
	}

	return 0;
}