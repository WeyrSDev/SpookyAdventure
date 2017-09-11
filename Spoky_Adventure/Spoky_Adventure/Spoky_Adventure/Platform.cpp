#include "Platform.h"



Platform::Platform(sf::Vector2f size)
{
	gravityEnabled = false; // disable gravity

	gameObjectShape.setSize(size);
	gameObjectShape.setFillColor(sf::Color::Green);

	objectTag = "Platform";
}


Platform::~Platform()
{
}
