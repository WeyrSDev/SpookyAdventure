#pragma once
#include "GameObject.h"
class Collectable : public GameObject
{
public:
	Collectable(sf::Vector2f,World&);
	~Collectable();
};

