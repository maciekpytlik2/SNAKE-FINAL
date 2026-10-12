#include "Snake.h"
#include <algorithm>
#include <iterator>
#include <ranges>

Snake::Snake(Position startPosition, int initialLength) {
    reset(startPosition, initialLength);
}

void Snake::reset(Position startPosition, int initialLength) {
    segments.clear();
    direction = Direction::Right;
    pendingGrowth = 0;

    for (int i = 0; i < initialLength; ++i) {
        segments.push_back({startPosition.x - i, startPosition.y});
    }
}

void Snake::move() {
    Position newHead = getHead();

    switch (direction) {
        case Direction::Up:    --newHead.y; break;
        case Direction::Down:  ++newHead.y; break;
        case Direction::Left:  --newHead.x; break;
        case Direction::Right: ++newHead.x; break;
    }

    segments.push_front(newHead);

    if (pendingGrowth > 0) {
        --pendingGrowth;
    } else {
        segments.pop_back();
    }
}

void Snake::grow() {
    ++pendingGrowth;
}

void Snake::setDirection(Direction newDirection) {
    if ((direction == Direction::Up && newDirection == Direction::Down) ||
        (direction == Direction::Down && newDirection == Direction::Up) ||
        (direction == Direction::Left && newDirection == Direction::Right) ||
        (direction == Direction::Right && newDirection == Direction::Left)) {
        return;
    }

    direction = newDirection;
}

Direction Snake::getDirection() const {
    return direction;
}

const std::deque<Position>& Snake::getSegments() const {
    return segments;
}

Position Snake::getHead() const {
    return segments.front();
}

bool Snake::contains(Position position) const {
    return std::ranges::find(segments, position) != segments.end();
}

bool Snake::collidesWithSelf() const {
    Position head = getHead();
    return std::ranges::find(std::next(segments.begin()), segments.end(), head) != segments.end();
}
