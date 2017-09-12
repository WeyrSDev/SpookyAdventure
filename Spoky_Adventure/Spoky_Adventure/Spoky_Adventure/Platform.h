#pragma once
#include "GameObject.h"

class Platform : public GameObject
{
public:
	Platform(sf::Vector2f, World& world);
	~Platform();
};

