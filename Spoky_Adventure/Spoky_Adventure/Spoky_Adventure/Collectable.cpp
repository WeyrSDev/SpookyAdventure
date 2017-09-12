#include "Collectable.h"



Collectable::Collectable(sf::Vector2f size, World& world)
{
	GameObject::GameObject(size, world); // call parent constructor 

	if (!objectTexture.loadFromFile("wood.jpeg"))
		throw std::runtime_error("Could not load fighter jet.png");

	objectSprite.setScale(size);
	objectSprite.setTexture(objectTexture);
	objectSprite.setColor(sf::Color::Blue);

	objectTag = "Collectable";
}


Collectable::~Collectable()
{
}
