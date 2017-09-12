#include "Platform.h"



Platform::Platform(sf::Vector2f size, World& world)
{
	GameObject::GameObject(size, world); // call parent constructor 

	if (!objectTexture.loadFromFile("wood.jpeg"))
		throw std::runtime_error("Could not load fighter jet.png");

	objectSprite.setOrigin(sf::Vector2f(objectSprite.getGlobalBounds().width / 2, objectSprite.getGlobalBounds().top));

	gravityEnabled = false; // disable gravity

	objectSprite.setScale(size);
	objectSprite.setTexture(objectTexture);
	objectSprite.setColor(sf::Color::Green);

	objectTag = "Platform";
}


Platform::~Platform()
{
}
