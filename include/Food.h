#pragma once

#include "GameObject.h"

class Food : public GameObject {
public:
    explicit Food(Position position);

    void applyEffect(Snake& snake, Game& game) override;
    sf::Color getColor() const override;
    char getSymbol() const override;
};
