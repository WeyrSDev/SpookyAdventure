#include "Player.h"
#include "World.h"

Player::Player(sf::Vector2f size, World& world)
{
	GameObject::GameObject(size, world); // call parent constructor 

	this->world = &world;


	std::cout << "Player Constructor called" << std::endl;

	if (!objectTexture.loadFromFile("wood.jpeg"))
		throw std::runtime_error("Could not load fighter jet.png");


	gravityEnabled = true; // Enable object gravity

	isGrounded = false;
	//jumpSpeed = 3.0f;
	jumpSpeed = 450.0f;
	moveSpeed = 130.0f;

	//gravitySpeed = 3.0f;
	gravitySpeed = 2.7f;


	objectSprite.setTexture(objectTexture);

	objectSprite.setScale(size);
	objectSprite.setColor(sf::Color::Magenta);

	objectTag = "Player";
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	GameCharacter::Update(deltaTime);



	// Get closest object
	if (world)
	{
		closestObject = world->FindClosestObject(this);
	}


	if (closestObject) // if colliding simple collision
	{
		if (this->CheckCollisionWith(*closestObject) > 0)
		{
			if (closestObject->GetObjectTag() == "Collectable")
			{
				for (int i = 0; i < world->GetWorldObjectCount(); i++)
				{
					if (world->GetWorldObjectList()[i] == closestObject)
					{
						// PICK UP COLLECTABLE
						world->GiveScore(50); // increase game score
						std::cout << "Player Score is: " << world->GetScore() << std::endl;
						world->DestroyObjectAt(i);
					}
				}
			}
		}

		if (this->CheckCollisionWith(*closestObject) == 2)
		{
			if (closestObject->GetObjectTag() == "Enemy")
			{
				for (int i = 0; i < world->GetWorldObjectCount(); i++)
				{
					if (world->GetWorldObjectList()[i] == closestObject)
					{
						// PICK UP COLLECTABLE
						Jump();
						world->GiveScore(100); // increase game score
						std::cout << "Player Score is: " << world->GetScore() << std::endl;
						world->DestroyObjectAt(i);
					}
				}
			}
		}

	}

}

void Player::Jump()
{
	GameCharacter::Jump();
}

void Player::MoveRight()
{
	GameCharacter::MoveRight();
}

void Player::MoveLeft()
{
	GameCharacter::MoveLeft();
}
