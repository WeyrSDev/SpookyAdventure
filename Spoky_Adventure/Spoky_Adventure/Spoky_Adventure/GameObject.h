#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class World;

class GameObject
{
public:
	GameObject(sf::Vector2f size, World& world);

	GameObject();

	void DrawTo(sf::RenderWindow&);

	void Move(sf::Vector2f);

	void SetPosition(sf::Vector2f);

	float GetYPosition();
	float GetXPosition();

	sf::Vector2f GetPosition();

	//bool CheckCollisionWith(sf::FloatRect&);
	int CheckCollisionWith(GameObject&);

	int CheckCollisions();

	sf::FloatRect GetShape();

	void ChangeColour(sf::Color color);

	std::string GetObjectTag();

	sf::Vector2f GetVelocity();

	virtual void Update(float deltaTime);

	~GameObject();

protected:

	bool gravityEnabled;
	bool isGrounded;
	float gravitySpeed;
	sf::Vector2f velocity;

	float delta = 0;

	sf::RectangleShape gameObjectShape;

	std::string objectTag;

	World* world;
};

