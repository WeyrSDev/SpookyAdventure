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

	float GetYPosition();
	float GetXPosition();

	sf::Vector2f GetPosition();

	//bool CheckCollisionWith(sf::FloatRect&);
	int CheckCollisionWith(GameObject&);

	int CheckCollisions();

	sf::FloatRect GetShape();

	void ChangeColour(sf::Color color);

	~GameObject();

protected:
	sf::RectangleShape gameObjectShape;
};

