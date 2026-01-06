#include "Snake.h"
#include <algorithm>

Snake::Snake()
{
    length = 3;
    direction = { 1, 0 };

    for (int i = 0; i < (int)length; ++i)
    {
        sf::Vector2i pos = { 5 - i, 10 };
        sf::Vector2f pix(pos.x * cellSize, pos.y * cellSize);
        segments.push_back({ pos, pix });
    }
}

void Snake::move()
{
    sf::Vector2i newHeadGrid = segments.front().gridPos + direction;

    // Start render position at old head GRID position (important!)
    sf::Vector2f startRender =
        sf::Vector2f(
            segments.front().gridPos.x * cellSize,
            segments.front().gridPos.y * cellSize
        );

    segments.push_front({ newHeadGrid, startRender });

    if (segments.size() > length)
        segments.pop_back();
}

void Snake::grow()
{
    ++length;
}

void Snake::setDirection(sf::Vector2i dir)
{
    if (dir + direction != sf::Vector2i{ 0, 0 })
        direction = dir;
}

bool Snake::isOnPosition(const sf::Vector2i& pos) const
{
    for (const auto& s : segments)
        if (s.gridPos == pos)
            return true;
    return false;
}

bool Snake::checkCollision() const
{
    const sf::Vector2i& head = segments.front().gridPos;

    if (head.x < 0 || head.x >= (int)config::GRID_COLS ||
        head.y < 0 || head.y >= (int)config::GRID_ROWS)
        return true;

    for (size_t i = 1; i < segments.size(); ++i)
        if (segments[i].gridPos == head)
            return true;

    return false;
}

bool Snake::checkWinCondition() const
{
    return segments.size() >= config::GRID_ROWS * config::GRID_COLS;
}

sf::Vector2i Snake::getNewHead() const
{
    return segments.front().gridPos + direction;
}

void Snake::updateRender(float dt)
{
    for (auto& s : segments)
    {
        sf::Vector2f target(
            s.gridPos.x * cellSize,
            s.gridPos.y * cellSize
        );

        s.renderPos += (target - s.renderPos) * followSpeed * dt;
    }
}

void Snake::draw(sf::RenderWindow& window) const
{
    sf::RectangleShape rect({ cellSize, cellSize });
    rect.setFillColor(sf::Color::Green);

    for (const auto& s : segments)
    {
        rect.setPosition(s.renderPos);
        window.draw(rect);
    }
}