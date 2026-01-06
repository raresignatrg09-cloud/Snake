#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "Source.hpp"
#include "Snake.h"
class Fruit
{
public:
	Fruit();
	void draw(sf::RenderWindow& window) const;
	void spawn(Snake& snake);
	sf::Vector2i getPosition() const { return position; }
private:
	sf::RectangleShape fruit;
	sf::Vector2i position;

	std::random_device rd;              
	std::mt19937 gen{rd()};  
	Snake tempSnake;
};

