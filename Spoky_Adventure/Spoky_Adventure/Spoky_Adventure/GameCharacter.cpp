#include "GameCharacter.h"
#include "World.h"


GameCharacter::GameCharacter()
{
}

GameCharacter::GameCharacter(sf::Vector2f size, World & world)
{
	gravityEnabled = true; // Enable object gravity

	isGrounded = false;
	jumpSpeed = 3.0f;
	moveSpeed = 130.0f;

	gameObjectShape.setSize(size);
	gameObjectShape.setFillColor(sf::Color::Red);

	objectTag = "Player";
}


GameCharacter::~GameCharacter()
{
}

void GameCharacter::Update(float deltaTime)
{
	GameObject::Update(deltaTime); // Call Base update
								   // DO THIS EVERY FRAME
								   //std::cout << "PLAYER UPDATE CALLED" << std::endl;

	if (isGrounded) // apply friction if grounded
	{
		if (velocity.x > 0)
		{
			velocity.x -= 2.07f * delta;
		}

		if (velocity.x < 0)
		{
			velocity.x += 2.07f * delta;
		}
	}

	if (isGrounded == false)
	{
		if (velocity.x > 0)
		{
			velocity.x -= 1.07f * delta;
		}

		if (velocity.x < 0)
		{
			velocity.x += 1.07f * delta;
		}
	}
}

void GameCharacter::Jump()
{
	if (isGrounded)
	{
		//velocity.y = (-jumpSpeed) * delta;
		isGrounded = false;
		//velocity.y = -gravitySpeed *1.5f;
		velocity.y = -jumpSpeed;
		std::cout << "Character jumped" << std::endl;
	}
}

void GameCharacter::MoveRight()
{
	std::cout << "Character move right" << std::endl;
	velocity.x = moveSpeed * delta;
}

void GameCharacter::MoveLeft()
{
	velocity.x = -moveSpeed * delta;
}
