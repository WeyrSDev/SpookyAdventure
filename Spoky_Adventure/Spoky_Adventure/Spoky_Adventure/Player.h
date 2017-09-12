#pragma once
#include "GameCharacter.h"



class Player : public GameCharacter
{
public:
	Player(sf::Vector2f, World& world);
	~Player();

	void Update(float deltaTime);

	void Jump();

	void MoveRight();

	void MoveLeft();

private:

};

