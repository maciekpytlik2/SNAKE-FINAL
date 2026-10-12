#pragma once

#include <memory>
#include <vector>
#include <optional>
#include "Position.h"
#include "GameObject.h"

class Board {
private:
    int width;
    int height;
    std::vector<std::unique_ptr<GameObject>> objects;

public:
    Board(int width, int height);

    int getWidth() const;
    int getHeight() const;

    bool isInside(Position position) const;
    bool isOccupied(Position position) const;

    void clearObjects();
    void addObject(std::unique_ptr<GameObject> object);
    GameObject* findObjectAt(Position position);
    void removeObjectAt(Position position);

    const std::vector<std::unique_ptr<GameObject>>& getObjects() const;
};
