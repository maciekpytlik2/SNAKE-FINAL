#pragma once

#include <SFML/Graphics.hpp>
#include "Position.h"

class Snake;
class Game;

class GameObject {
protected:
    Position position;

public:
    explicit GameObject(Position startPosition);
    virtual ~GameObject() = default;

    Position getPosition() const;
    void setPosition(Position newPosition);

    virtual void applyEffect(Snake& snake, Game& game) = 0;
    virtual sf::Color getColor() const = 0;
    virtual char getSymbol() const = 0;
};
