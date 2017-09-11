#include "Player.h"
#include "World.h"

Player::Player(sf::Vector2f size, World& world)
{
	GameObject::GameObject(size, world); // call parent constructor 

	this->world = &world;

	std::cout << "Player Constructor called" << std::endl;
	gravityEnabled = true; // Enable object gravity

	isGrounded = false;
	jumpSpeed = 3.0f;
	moveSpeed = 130.0f;

	gravitySpeed = 3.0f;

	gameObjectShape.setSize(size);
	gameObjectShape.setFillColor(sf::Color::Red);

	objectTag = "Player";
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
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

	GameObject* closestObject = nullptr;

	// Get closest object
	if (world)
	{
		closestObject = world->FindClosestObject(this);
	}


	if (closestObject) // if colliding simple collision
	{
		if (this->CheckCollisionWith(*closestObject) > 0)
		{
			// erase the 6th element
			if (closestObject->GetObjectTag() == "Collectable")
			{
				for (int i = 0; i < world->GetWorldObjectCount(); i++)
				{
					if (world->GetWorldObjectList()[i] == closestObject)
					{
						// PICK UP COLLECTABLE
						std::cout << "pick up" << std::endl;
						world->DestroyObjectAt(i);
					}
				}
			}
		}
	}

}

void Player::Jump()
{
	if (isGrounded)
	{
		//velocity.y = (-jumpSpeed) * delta;
		isGrounded = false;
		//velocity.y = -gravitySpeed *1.5f;
		velocity.y = -jumpSpeed;
		std::cout << "Player jumped" << std::endl;
	}
}

void Player::MoveRight()
{
	std::cout << "Player move right" << std::endl;
	velocity.x = moveSpeed * delta;
}

void Player::MoveLeft()
{
	velocity.x = -moveSpeed * delta;
}
