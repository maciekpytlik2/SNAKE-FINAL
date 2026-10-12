#include "Board.h"
#include <algorithm>

Board::Board(int width, int height) : width(width), height(height) {}

int Board::getWidth() const {
    return width;
}

int Board::getHeight() const {
    return height;
}

bool Board::isInside(Position position) const {
    return position.x >= 0 && position.x < width && position.y >= 0 && position.y < height;
}

bool Board::isOccupied(Position position) const {
    return std::ranges::any_of(objects, [position](const auto& object) {
        return object->getPosition() == position;
    });
}

void Board::clearObjects() {
    objects.clear();
}

void Board::addObject(std::unique_ptr<GameObject> object) {
    objects.push_back(std::move(object));
}

GameObject* Board::findObjectAt(Position position) {
    auto it = std::ranges::find_if(objects, [position](const auto& object) {
        return object->getPosition() == position;
    });

    return it == objects.end() ? nullptr : it->get();
}

void Board::removeObjectAt(Position position) {
    std::erase_if(objects, [position](const auto& object) {
        return object->getPosition() == position;
    });
}

const std::vector<std::unique_ptr<GameObject>>& Board::getObjects() const {
    return objects;
}
