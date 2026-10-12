#pragma once

#include "GameObject.h"

class BonusFood : public GameObject {
public:
    explicit BonusFood(Position position);

    void applyEffect(Snake& snake, Game& game) override;
    sf::Color getColor() const override;
    char getSymbol() const override;
};
