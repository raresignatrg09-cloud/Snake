#include "Grid.h"

Grid::Grid(unsigned int rows, unsigned int cols, unsigned int cellSize)
	: rows(rows), cols(cols), cellSize(cellSize)
{
    cells.setPrimitiveType(sf::Quads);
    cells.resize(rows * cols * 4);
    const float cs = static_cast<float>(cellSize);

    size_t i = 0;
    for (unsigned int y = 0; y < rows; y++)
    {
        for (unsigned int x = 0; x < cols; x++)
        {
            sf::Color color = ((x + y) % 2 == 0)
                ? sf::Color(30, 30, 30)
                : sf::Color(40, 40, 40);

            sf::Vertex* quad = &cells[i];

            quad[0].position = { x * cs, y * cs };
            quad[1].position = { (x + 1) * cs, y * cs };
            quad[2].position = { (x + 1) * cs, (y + 1) * cs };
            quad[3].position = { x * cs, (y + 1) * cs };

            quad[0].color = quad[1].color =
                quad[2].color = quad[3].color = color;

            i += 4;
        }
    }
}

void Grid::draw(sf::RenderWindow& window) const
{
	window.draw(cells);
}