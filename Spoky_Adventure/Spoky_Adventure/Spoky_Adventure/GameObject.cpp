#include "GameObject.h"
#include <iostream>
#include "World.h"

GameObject::GameObject(sf::Vector2f size, World& world) // get reference to world when spawned // which instance of world spawned this object
{
	std::cout << "GameObject Constructor called" << std::endl;
	this->world = &world;

	gravityEnabled = false;
	gravitySpeed = 3.0f;

	isGrounded = false;

	velocity = sf::Vector2f(0, 0);

	gameObjectShape.setSize(size);
	gameObjectShape.setFillColor(sf::Color::Green);
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

	pTop = GetShape().top;
	pBottom = (GetShape().top + GetShape().height);

	otherTop = other.GetShape().top;
	otherBottom = (other.GetShape().top + GetShape().height);

	otherLeft = other.GetShape().left;
	otherRight = (other.GetShape().left + other.GetShape().width);

	pLeft = GetShape().left;
	pRight = (GetShape().left + GetShape().width);

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
	auto bounds = gameObjectShape.getGlobalBounds();
	return static_cast<sf::FloatRect>(bounds);
}

void GameObject::ChangeColour(sf::Color color)
{
	gameObjectShape.setFillColor(color);
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

	GameObject* closestObject = nullptr;

	// Get closest object
 	if (world)
	{
		closestObject = world->FindClosestObject(this);
	}

	// = world->FindClosestObject(worldObjects, world->GetPlayer());

	// for this object check collision with closest world object


	if (closestObject != nullptr)
	{
		closestObject->ChangeColour(sf::Color::Magenta);

		if (this->CheckCollisionWith(*closestObject) == 1)
		{
			//cout << "Colliding at top " << endl;
			if (closestObject->GetObjectTag() == "Platform")
			{
				//velocity.y += jumpSpeed;
			}
		}

		if (this->CheckCollisionWith(*closestObject) == 2)
		{
			std::cout << "Colliding at bottom " << std::endl;
			if (closestObject->GetObjectTag() == "Platform")
			{
				isGrounded = true;
				velocity.y = 0.0f;
				closestObject->ChangeColour(sf::Color::Magenta);
			}
		}
		else
		{
			closestObject->ChangeColour(sf::Color::Green);
			isGrounded = false;
		}
	}

	// do approriate action
}

void GameObject::DrawTo(sf::RenderWindow& window)
{
	window.draw(gameObjectShape);
}

void GameObject::Move(sf::Vector2f distance)
{
	gameObjectShape.move(distance);
}

void GameObject::SetPosition(sf::Vector2f newPos)
{
	gameObjectShape.setPosition(newPos);
}

float GameObject::GetYPosition()
{
	return gameObjectShape.getPosition().y;
}

float GameObject::GetXPosition()
{
	return gameObjectShape.getPosition().x;
	//gameObjectShape.getOrigin()
}

sf::Vector2f GameObject::GetPosition()
{
	return gameObjectShape.getPosition();
}


GameObject::~GameObject()
{
}

