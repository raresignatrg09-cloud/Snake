#include "Fruit.h"

Fruit::Fruit()
{
	fruit.setSize(sf::Vector2f(static_cast<float>(config::GRID_CELL_SIZE), static_cast<float>(config::GRID_CELL_SIZE)));
	fruit.setFillColor(sf::Color::Red);
	
	spawn(tempSnake);
}

void Fruit::draw(sf::RenderWindow& window) const
{
	window.draw(fruit);
}

void Fruit::spawn(Snake& snake)
{
	std::uniform_int_distribution<> distribX(0, config::GRID_COLS - 1);
	std::uniform_int_distribution<> distribY(0, config::GRID_ROWS - 1);
	
	while (true)
	{
		int x = distribX(gen);
		int y = distribY(gen);
		position = sf::Vector2i(x, y);
		if (!snake.isOnPosition(position))
		{
			fruit.setPosition(static_cast<float>(position.x * config::GRID_CELL_SIZE),
				static_cast<float>(position.y * config::GRID_CELL_SIZE));
			break;
		}
	}
}
