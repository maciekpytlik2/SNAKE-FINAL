#pragma once

#include "GameObject.h"

class Obstacle : public GameObject {
public:
    explicit Obstacle(Position position);

    void applyEffect(Snake& snake, Game& game) override;
    sf::Color getColor() const override;
    char getSymbol() const override;
};
