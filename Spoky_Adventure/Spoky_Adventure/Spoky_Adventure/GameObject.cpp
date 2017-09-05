#include "GameObject.h"
#include <iostream>

GameObject::GameObject(sf::Vector2f size)
{
	gameObjectShape.setSize(size);
	gameObjectShape.setFillColor(sf::Color::Green);

	//gameObjectShape.getGlobalBounds().intersects()
}

GameObject::GameObject()
{
}

bool GameObject::CheckCollisionWith(sf::FloatRect& shape)
{
	bool isColliding = false;

	isColliding = gameObjectShape.getGlobalBounds().intersects(shape);

	int collisioFlag = 0;
	if (gameObjectShape.getGlobalBounds().top)
	{
		std::cout << gameObjectShape.getGlobalBounds().top << std::endl;
		collisioFlag = 1;
	}
	else if (gameObjectShape.getGlobalBounds().height)
	{
		collisioFlag = 2;
	}

	return isColliding;
}

bool GameObject::CheckCollisionWith(GameObject& other)
{
	int collisioFlag = 0;

	//std::cout << GetPosition().y << " "<< other.GetPosition().y << std::endl;

	
	if (GetPosition().y <= other.GetPosition().y && GetPosition().y >= other.GetPosition().y - other.GetShape().height)
	{
		collisioFlag = 1;
	}
	if (GetPosition().y >= other.GetPosition().y && GetPosition().y <= other.GetPosition().y + other.GetShape().height)
	{
		collisioFlag = 2; // not working
	}
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

int GameObject::GetYPosition()
{
	return gameObjectShape.getPosition().y;
}

sf::Vector2f GameObject::GetPosition()
{
	return gameObjectShape.getPosition();
}


GameObject::~GameObject()
{
}

