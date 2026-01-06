#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "Source.hpp"

struct Segment
{
    sf::Vector2i gridPos;
    sf::Vector2f renderPos;
};

class Snake
{
public:
    Snake();

    void move();
    void grow();
    void setDirection(sf::Vector2i dir);

    bool isOnPosition(const sf::Vector2i& pos) const;
    bool checkCollision() const;
    bool checkWinCondition() const;

    void updateRender(float dt);
    void draw(sf::RenderWindow& window) const;

    sf::Vector2i getDirection() const { return direction; }
    sf::Vector2i getPosition() const { return segments.front().gridPos; }
    sf::Vector2i getNewHead() const;

private:
    std::deque<Segment> segments;
    sf::Vector2i direction;
    size_t length;

    float cellSize = static_cast<float>(config::GRID_CELL_SIZE);
    float followSpeed = 12.f;
};
