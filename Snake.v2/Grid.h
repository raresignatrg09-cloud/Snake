#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Grid
{
public:
	Grid(unsigned int rows, unsigned int cols, unsigned int cellSize);
	void draw(sf::RenderWindow& window) const;

	unsigned int getCellSize() const { return cellSize; }
	unsigned int getRows() const { return rows; }
	unsigned int getCols() const { return cols; }

private:
	unsigned int rows;
	unsigned int cols;
	unsigned int cellSize;
	sf::VertexArray cells;
};

