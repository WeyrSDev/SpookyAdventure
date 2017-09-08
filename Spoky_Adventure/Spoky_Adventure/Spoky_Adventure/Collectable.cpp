#include "Collectable.h"



Collectable::Collectable(sf::Vector2f size)
{
	gameObjectShape.setSize(size);
	gameObjectShape.setFillColor(sf::Color::Blue);

	objectTag = "Collectable";
}


Collectable::~Collectable()
{
}
