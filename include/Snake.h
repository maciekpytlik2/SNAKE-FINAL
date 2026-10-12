#pragma once

#include <deque>
#include "Position.h"
#include "Direction.h"

class Snake {
private:
    std::deque<Position> segments;
    Direction direction{Direction::Right};
    int pendingGrowth{0};

public:
    Snake(Position startPosition, int initialLength = 4);

    void move();
    void grow();
    void setDirection(Direction newDirection);
    Direction getDirection() const;

    const std::deque<Position>& getSegments() const;
    Position getHead() const;

    bool contains(Position position) const;
    bool collidesWithSelf() const;
    void reset(Position startPosition, int initialLength = 4);
};
