#include "GameObject.h"
#include <iostream>
#include "World.h"

GameObject::GameObject(sf::Vector2f size, World& world) // get reference to world when spawned // which instance of world spawned this object
{


	std::cout << "GameObject Constructor called" << std::endl;

	if (!objectTexture.loadFromFile("wood.jpeg"))
		throw std::runtime_error("Could not load fighter jet.png");

	objectSprite.setOrigin(sf::Vector2f(objectSprite.getGlobalBounds().width / 2, objectSprite.getGlobalBounds().top));

	this->world = &world;

	gravityEnabled = false;
	//gravitySpeed = 3.0f;
	gravitySpeed = 70.0f;

	isGrounded = false;

	velocity = sf::Vector2f(0, 0);

	//gameObjectShape.setSize(size);
	objectSprite.setScale(size);
	//objectSprite.setTexture(objectTexture);
	objectSprite.setColor(sf::Color::Green);
	objectTag = "GameObject";
	//gameObjectShape.getGlobalBounds().intersects()
}

GameObject::GameObject()
{
}

int GameObject::CheckCollisionWith(GameObject& other)
{
	int collisioFlag = 0;

	//std::cout << GetPosition().y << " "<< other.GetPosition().y << std::endl;

	//if (GetShape().top <= other.GetPosition().y &&  GetShape().top - GetShape().height >= other.GetPosition().y - other.GetShape().height)
	float otherBottom, otherTop, pBottom, pTop;
	float otherLeft, otherRight, pLeft, pRight;
	float topOffset = 3;
	float sideOffset = 50;

	pTop = GetShape().top - topOffset;
	pBottom = (GetShape().top + GetShape().height) + topOffset;

	otherTop = other.GetShape().top - topOffset;
	otherBottom = (other.GetShape().top + GetShape().height) + topOffset;

	otherLeft = other.GetShape().left - sideOffset;
	otherRight = (other.GetShape().left + other.GetShape().width) + sideOffset;

	pLeft = GetShape().left - topOffset;
	pRight = (GetShape().left + GetShape().width) + topOffset;

	if (pTop <= otherBottom && pTop > otherTop && pLeft >= otherLeft && pRight <= otherRight)
	{
		collisioFlag = 1;
	}
	else if (pBottom >= otherTop && pBottom < otherBottom && pLeft >= otherLeft && pRight <= otherRight)
	{
		collisioFlag = 2; 
	}
	//TODO IMPLEMENT collision from left and right


	return collisioFlag;
}

int GameObject::CheckCollisions()
{
	return false;
}

sf::FloatRect GameObject::GetShape()// should be get bounds object
{
	auto bounds = objectSprite.getGlobalBounds();
	return static_cast<sf::FloatRect>(bounds);
}

void GameObject::ChangeColour(sf::Color color)
{
	objectSprite.setColor(color);
}

std::string GameObject::GetObjectTag()
{
	return objectTag;
}

sf::Vector2f GameObject::GetVelocity()
{
	return velocity;
}

void GameObject::Update(float deltaTime)
{
	delta = deltaTime;

	//APPLY GRAVITY
	if (gravityEnabled)
	{
		if (isGrounded == false)
			velocity.y += (gravitySpeed * delta);
		//if (velocity.y > 8)
		//{
		//	velocity.y = 8;
		//}
	}
	Move(velocity);
	//Move(sf::Vector2f({ 0,5 }));

	//std::cout << "dt is: " << delta << std::endl;
	//std::cout << "velocity is: " << velocity.y << std::endl;

	//GameObject* closestObject = nullptr;

	// Get closest object
 	if (world)
	{
		//closestObject = world->FindClosestObject(this);

		for (int i = 0; i < 3; i++)
		{
			if (i > 0)
			{
				if (world->FindClosestObject(this) != closestObjects[i -1])
				{
					if(world->FindClosestObject(this) != closestObjects[i])
					closestObjects[i] = world->FindClosestObject(this);
				}
			}
			else
			{
				auto object = world->FindClosestObject(this);

				if (object == nullptr) { return; }
				if ( object->GetObjectTag() == "Platform")
				{
					closestObjects[i] = world->FindClosestObject(this);
				}
				else
					break;
			}
				
		}
	}

	// = world->FindClosestObject(worldObjects, world->GetPlayer());

	// for this object check collision with closest world object

	for (int i = 0; i < 3; i++)
	{
		if (closestObjects[i] != nullptr)
		{
			//closestObject->ChangeColour(sf::Color::Magenta);

			if (this->CheckCollisionWith(*closestObjects[i]) == 1)
			{
				//cout << "Colliding at top " << endl;
				if (closestObjects[i]->GetObjectTag() == "Platform")
				{
					//velocity.y += jumpSpeed;
				}
			}

			if (this->CheckCollisionWith(*closestObjects[i]) == 2)
			{
				//std::cout << "Colliding at bottom " << std::endl;
				//if (closestObjects[i]->GetObjectTag() == "Platform")
				//{
				if(gravityEnabled)
				{
					if (velocity.y > 0)
					{
						velocity.y = velocity.y / 2;
					}
					isGrounded = true;
					//closestObjects[0]->ChangeColour(sf::Color::Magenta);
				}
			}
			else
			{
				if (closestObjects[i]->GetObjectTag() == "Platform")
				{
					//closestObjects[i]->ChangeColour(sf::Color::Green);
					isGrounded = false;
				}
			}
		}
	}
	// do approriate action
}

void GameObject::DrawTo(sf::RenderWindow& window)
{
	window.draw(objectSprite);
}

void GameObject::Move(sf::Vector2f distance)
{
	objectSprite.move(distance);
}

void GameObject::SetPosition(sf::Vector2f newPos)
{
	objectSprite.setPosition(newPos);
}

float GameObject::GetYPosition()
{
	return objectSprite.getPosition().y;
}

float GameObject::GetXPosition()
{
	return objectSprite.getPosition().x;
	//return gameObjectShape.getPosition().x;
	//gameObjectShape.getOrigin()
}

sf::Vector2f GameObject::GetPosition()
{
	return objectSprite.getPosition();
}


GameObject::~GameObject()
{
}

