#include "GameObject.h"
#include <iostream>

GameObject::GameObject(sf::Vector2f size)
{
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

