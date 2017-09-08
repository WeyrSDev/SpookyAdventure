#include "Player.h"


Player::Player(sf::Vector2f size)
{
	//GameObject();
	gameObjectShape.setSize(size);
	gameObjectShape.setFillColor(sf::Color::Red);

	objectTag = "Player";
}

Player::~Player()
{
}
