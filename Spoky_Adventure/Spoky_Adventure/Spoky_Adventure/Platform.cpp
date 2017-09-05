#include "Platform.h"



Platform::Platform(sf::Vector2f size)
{
	gameObjectShape.setSize(size);
	gameObjectShape.setFillColor(sf::Color::Green);
}


Platform::~Platform()
{
}
