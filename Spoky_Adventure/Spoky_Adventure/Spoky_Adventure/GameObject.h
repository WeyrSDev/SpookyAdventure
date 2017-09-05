#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject(sf::Vector2f);

	GameObject();

	void DrawTo(sf::RenderWindow&);

	void Move(sf::Vector2f);

	void SetPosition(sf::Vector2f);

	int GetYPosition();

	sf::Vector2f GetPosition();

	bool CheckCollisionWith(sf::FloatRect&);
	bool CheckCollisionWith(GameObject&);

	int CheckCollisions();

	sf::FloatRect GetShape();

	~GameObject();

protected:
	sf::RectangleShape gameObjectShape;
};

