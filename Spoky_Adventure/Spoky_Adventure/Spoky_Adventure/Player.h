#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(sf::Vector2f, World& world);
	~Player();

	float jumpSpeed;
	float moveSpeed;

	void Update(float deltaTime) override;
	void Jump();
	void MoveRight();
	void MoveLeft();

private:

};

