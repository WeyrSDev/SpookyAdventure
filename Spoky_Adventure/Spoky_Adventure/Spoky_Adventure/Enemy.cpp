#include "Enemy.h"
#include "World.h"


Enemy::Enemy()
{
}

Enemy::Enemy(sf::Vector2f size, World & world)
{
	GameObject::GameObject(size, world); // call parent constructor 

	this->world = &world;


	if (!objectTexture.loadFromFile("wood.jpeg"))
		throw std::runtime_error("Could not load fighter jet.png");
	//gravityEnabled = true;

	objectSprite.setOrigin(sf::Vector2f(objectSprite.getGlobalBounds().width / 2, objectSprite.getGlobalBounds().top - objectSprite.getGlobalBounds().height));

	isGrounded = false;
	jumpSpeed = 3.0f;
	moveSpeed = 50.0f;

	gravitySpeed = 3.0f;

	objectSprite.setScale(size);
	objectSprite.setTexture(objectTexture);
	objectSprite.setColor(sf::Color::Red);

	objectTag = "Enemy";


	moveRight = true;
}


Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	GameCharacter::Update(deltaTime);

	GameObject* closestObject = nullptr;

	// Get closest object
	if (world)
	{
		closestObject = world->FindClosestObject(this);
	}


	if (closestObject && myPlatform == nullptr) // Set my platform variable at start
	{
		if (this->CheckCollisionWith(*closestObject) > 0)
		{
			if (closestObject->GetObjectTag() == "Platform")
			{
				myPlatform = closestObject;
			}
		}
	}


	if (myPlatform)
	{


		if (GetShape().left + GetShape().width > myPlatform->GetShape().left + myPlatform->GetShape().width)
		{
			moveRight = false;
		}
		else if(GetShape().left <  myPlatform->GetShape().left)
		{
			moveRight = true;
		}

		if (moveRight)
		{
			MoveRight();
		}
		else
		{
			MoveLeft();
		}
	}
	
}
