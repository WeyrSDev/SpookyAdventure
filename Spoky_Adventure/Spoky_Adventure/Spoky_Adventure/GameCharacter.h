#pragma once
#include "GameObject.h"


class World;

class GameCharacter : public GameObject
{
public:
	GameCharacter();
	GameCharacter(sf::Vector2f, World& world);
	~GameCharacter();

	float jumpSpeed;
	float moveSpeed;

	void Update(float deltaTime);
	virtual void Jump();
	virtual void MoveRight();
	virtual void MoveLeft();
};

