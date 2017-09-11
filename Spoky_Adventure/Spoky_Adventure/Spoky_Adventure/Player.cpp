#include "Player.h"

Player::Player(sf::Vector2f size, World& world)
{
	GameObject::GameObject(size, world); // call parent constructor 

	this->world = &world;

	std::cout << "Player Constructor called" << std::endl;
	gravityEnabled = true; // Enable object gravity

	isGrounded = false;
	float jumpSpeed = 550;
	float moveSpeed = 0.001f;

	gravitySpeed = 2.0f;

	gameObjectShape.setSize(size);
	gameObjectShape.setFillColor(sf::Color::Red);

	objectTag = "Player";
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime); // Call Base update
	// DO THIS EVERY FRAME
	//std::cout << "PLAYER UPDATE CALLED" << std::endl;

}

void Player::Jump()
{
	if (isGrounded)
	{
		velocity.y = (-jumpSpeed) * delta;
		std::cout << "Player jumped" << std::endl;
	}
}

void Player::MoveRight()
{
	//velocity.x += moveSpeed * delta;
}

void Player::MoveLeft()
{
	//velocity.x = -moveSpeed * delta;
}
