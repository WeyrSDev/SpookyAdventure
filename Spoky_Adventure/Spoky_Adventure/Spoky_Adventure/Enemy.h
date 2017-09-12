#pragma once
#include "GameCharacter.h"
class Enemy :
	public GameCharacter
{
private:
	GameObject* myPlatform = nullptr;
	bool moveRight;

public:
	Enemy();
	Enemy(sf::Vector2f, World& world);
	~Enemy();

	void Update(float deltaTime);
};

